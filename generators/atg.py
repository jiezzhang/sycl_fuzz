#!/usr/bin/python
# Automatic Test Generator for .atg (Automatic Test Grammar) files
# See http://icl.intel.com/wikis/innovation/AutoTestGen for details

# do not forget to search for "TODO"

# .atg grammar syntax was inspired by this paper:
# "An Automatic Generator for Compiler Testing" by
# FRANCO BAZZICHI AND IPPOLITO SPADAFORA

# Naming conventions:
# is  = Boolean
# n   = Number
# s   = String
# l   = List
# d   = Dictionary
# set = [Frozen] Set
# re  = regular expression
# m   = match

# bisect    - to perform binary search in list of adjacent intervals
# itertools - to duplicate space character
import sys, re, random, bisect, itertools
from optparse import OptionParser

version = "1.0"

setKnownPragmas = frozenset([
    # number of letters after which generator will use shortest grammar rules only
    # to finish generated string as soon as possible
    "GEN_LENGTH"
])

# contains nonterminal properties;
# this class is used as values of the dNT dictionary,
# whose keys are nonterminal names
class NT: # nonterminal
    def __init__(self):
        # dictionary of class R values,
        # whose keys are string parameters representation
        self.dR    = {}
        # dictionary of class NegR values,
        # whose keys are string parameters representation
        self.dNegR = {}
        # sum of nPwr of all classes RP in dR dictionary
        # computed by compute_nt_power function
        # used to cache already computed values; not used by GEN_STR function;
        # this value is undefined if equals to zero
        self.nPwrSum = 0

# groups all RP classes with same NT string parameter representation
class R: # Rule
    def __init__(self, lRS):
        # internal representation of NT parameter,
        # described by list of RS classes
        self.lRS   = lRS
        # list of RP classes contained in this R class
        self.lRP   = []
        # length (nLen) of the shortest RP in lRP list
        # computed by find_some_short_rules_in_grammar function;
        # used for caching purposes; not used by GEN_STR function;
        # this value is undefined if equals to sys.maxint
        self.nLen  = sys.maxint
        # dictionary of all group names used in the regexps of lRS list
        self.dsGrp = dict()
        # it is computed just here
        for rs in lRS: self.dsGrp.update(rs.re.groupindex)

# internal representation of NT parameter,
# used to match it in the match_params function
class RS: # Rule Selector
    reGrp = re.compile(r"\(\?P\<([a-zA-Z_]\w*)\>") # named group
    reRef = re.compile(r"\(\?P\=([a-zA-Z_]\w*)\)") # named group reference
    def __init__(self, sRE, sGrpNm = "", sLstSep = "", isNeg = 0):
        # parameter regular expression must match the whole context
        sRE = "^(?:" + sRE + ")$"
        # store original regexp string,
        # that will be used in the match_params function to recompile regexp
        # with unresolved named group references (if lsUnkRef list is not empty)
        self.sRE      = sRE
        # name of the previously (within the same parameter) matched group,
        # that will be used for current (sRE) match instead of the whole context
        # (if it is empty)
        self.sGrpNm   = sGrpNm
        # if this is not empty, then current context (or sGrpNm) is split by it
        # into list of strings and then randomly list items will be matched
        # against sRE until first match or list depletion (that means error)
        self.sLstSep  = sLstSep
        self.isNeg    = isNeg
        # list of names of unresolved group references (computed here)
        self.lsUnkRef = []

        # set of all names of references to named groups
        setRef   = frozenset(self.reRef.findall(sRE))
        # set of all named group names;
        # TODO: handle nested references
        setGroup = frozenset(self.reGrp.findall(sRE))
        # lsUnkRef = setRef - setGroup;
        # TODO: take into account that reference should be after its group?
        for sRef in setRef:
            if sRef not in setGroup:
                self.lsUnkRef.append(sRef)
        # if regular expression is complete then pre-compile it now!
        if not len(self.lsUnkRef):
            try: self.re = re.compile(sRE)
            except: raise "sBAD_LINE", "Can't compile expression"
        # remove all references to named groups;
        # this compiled self.re is still useful because of its groupindex
        else: self.re = re.compile(self.reRef.sub("", sRE))

# this class mainly contains information used to generate string based on the
# rule it represent in a way of RPI class list
class RP: # Rule/Right Part
    def __init__(self, nUsrOrd = sys.maxint, nUsrPwr = 1, isSet = 0,
                 sSetSep = " ", nSetMin = 1, nSetMax = 19, nSetAvg = 10):
        # user-defined user order to resolve ambiguity that can't be resolved
        # automatically by the find_some_short_rules_in_grammar function;
        # value sys.maxint means that no user-defined order is provided
        self.nUsrOrd = nUsrOrd
        # user defined power multiplier that will scale nPwr value;
        # scaling is done in the compute_nt_power function that computes nPwr
        self.nUsrPwr = nUsrPwr
        # when true this rule right part actually determines one set element;
        # set has random power in the following range: [nSetMin, nSetMax];
        # all set elements are joined into one string with sSetSep
        self.isSet   = isSet
        self.sSetSep = sSetSep
        self.nSetMin = nSetMin
        self.nSetMax = nSetMax
        self.nSetAvg = nSetAvg # TODO: it is not currently used
        # list of RPI class items that actually constitute this rule right part
        self.lRPI    = []
        # if defined (not sys.maxint) by find_some_short_rules_in_grammar
        # function, it means the minimal number of characters in this rule;
        # this value is used to detect the the shortest rule if generated string
        # should be finished as soon as possible
        self.nLen    = sys.maxint
        # the weight of the rule that increase its chances to be triggered;
        # weights of all rules that can be triggered are placed as consecutive
        # ranges from zero to sum of all weights and when randomly chosen point
        # in the [0, sum of all ranges) is used to determine the rule to use;
        # value is already scaled by nUsrPwr by the compute_nt_power function
        self.nPwr    = 0

# this class contains part of the nonterminal name context that can be either
# nonterminal or terminal string;
class RPNI: # Rule/Right Part Name Item
    def __init__(self, sNm, sTrm = ""):
        # if non-empty string this means name of the nonterminal or
        # name of the group reference (it has priority over nonterminal name)
        # obtained during context matching
        self.sNm  = sNm
        # if non-empty string (in this case sNm should be empty) this means raw
        # string value that will be used as terminal
        self.sTrm = sTrm
        # if sNm is non-empty string that means nonterminal name,
        # this list contains RPNI class values that form its context
        self.lRPNI = []

# contains information about individual item of list that represent a rule;
# it can be terminal, nonterminal with optional context parameter and
# special end-of-line (EOL) marker
class RPI(RPNI): # Rule/Right Part Item
    def __init__(self, rpni, nEOL = 0):
        # if non-empty string this means name of the nonterminal or
        # name of the group reference (it has priority over nonterminal name)
        # obtained during context matching
        self.sNm  = rpni.sNm
        # if non-empty string (in this case sNm should be empty) this means raw
        # string value that will be used as terminal
        self.sTrm = rpni.sTrm
        # if sNm is non-empty string that means nonterminal name,
        # this list contains RPNI class values that form its context
        self.lRPNI = rpni.lRPNI
        # if both sNm and sTrm are empty strings, then end-of-line is emitted
        # and then sEOL is emitted, that consists of space characters that will be
        # placed after it (this is, in fact, the indent of the next line)
        self.sEOL = "".join(itertools.repeat(" ", nEOL))

# contains information about negative nonterminal rule that will be used to
# reject string generated by RP rules and cause its regeneration
# (for a limited number of times after which algorithms will be aborted);
# TODO: incorporate this negative (regular) rules into generative rules?
class NegR: # Negative Rule
    # regular expression used to strip regular expression string from
    # "^(?:" ... ")$" wrap
    reWrap = re.compile(r"^\^\(\?\:(?P<RE>.*)\)\$$")

    def __init__(self, lRS, sNegRE):
        # negative regular expression must match the whole NT
        stNegRE = "^(?:" + sNegRE + ")$"
        # internal representation of NT parameter,
        # described by list of RS classes
        self.lRS   = lRS
        # this is "negative" regular expression against which generated string
        # of the current nonterminal will be matched and rejected if matched
        self.reNeg = re.compile(stNegRE)

    # this method merges additional "negative" regular expression to existing
    # "negative" regular expression by "|" operator
    def update(self, sNegRE):
        # of course existing "negative" regular expression should be strip of
        # beginning and ending added in the __init__ method
        m = self.reWrap.match(self.reNeg.pattern)
        if __debug__ and not m: raise AssertionError
        # join with "|" and add beginning and ending to the whole regexp
        self.reNeg = re.compile("^(?:" + m.group("RE") + "|" + sNegRE + ")$")

# count indent (number of space characters in the beginning of the line)
# of the input string; tabulation equals up to 8 spaces
def count_indent(sLn):
    nRes = 0; nChr = 0
    while nChr < len(sLn) and sLn[nChr].isspace():
        if sLn[nChr] == '\t': nRes = nRes + (8 - (nRes % 8))
        else: nRes = nRes + 1
        nChr = nChr + 1
    return nRes

# just prints string in the stderr
def trace(sMsg):
    print>>sys.stderr, sMsg

# just prints string in the stderr and aborts the program
def err(sErr):
    trace(sErr)
    sys.exit(1)

# just return string with skipped match
def skip_match(sLn, m):
    if __debug__ and not m: raise AssertionError
    return sLn[m.end(0):]

# empty line (comments ignored)?
reEmptyLn   = re.compile(r"^\s*(?:\#|$)")
# name or full context (name in the RPNI)
reNm2       = re.compile(r"^\s*(?P<NAME>[a-zA-Z_]\w*|\*)")
# beginning of the RPNI parameter list (lRPNI)
rePrmBegin2 = re.compile(r"^\s*\[")
# end of the parameter
rePrmEnd    = re.compile(r"^\s*\]")
# string of characters in double quotes that can contain double quote
# after backslash (other escape-characters are not supported);
# TODO: add support for other escape-sequences if needed
reTrmStr    = re.compile(r'^\s*"(?P<STR>(?:[^\\"]|\\.)*?)"')

# takes line of characters
# returns 1) parsed RPNI instance (None if it was not parsed)
#         2) line of characters after parsed RPNI instance
def parse_rpni(sLn):
    m = reNm2.match(sLn)
    if not m:
        # parse terminal string
        m = reTrmStr.match(sLn)
        if m:
            sLn = skip_match(sLn, m)
            sSTR = m.group("STR");
            # handle escapes
            sSTR = sSTR\
            	.replace( r'\"', '"' )\
            	.replace( r'\\', '\\' )\
            	.replace( r'\n', '\n' )

            return [RPNI("", sSTR), sLn]
        return [None, sLn]

    sLn = skip_match(sLn, m)
    rpni = RPNI(m.group("NAME"))

    m = rePrmBegin2.match(sLn)
    if not m: return [rpni, sLn]

    if rpni.sNm == "*": raise "sBAD_LINE", "Star (*) can't have params"

    sLn = skip_match(sLn, m)

    isOK = 0 # true if end-of-params was found
    # params can't cross line boundary
    while not reEmptyLn.match(sLn):
        # match name and its parameters, if any
        rpni2, sLn2 = parse_rpni(sLn)
        if rpni2 != None:
            rpni.lRPNI.append(rpni2)
            sLn = sLn2
            continue

        m = rePrmEnd.match(sLn)
        if m:
            sLn  = skip_match(sLn, m)
            isOK = 1
            break
        raise "sBAD_LINE", "Unexpected param's item"
    if not isOK: # we've found end-of-line
        raise "sBAD_LINE", "Can't find param's end"

    return [rpni, sLn]


# returns dNT map and dPragmas built from the list of input lines sLn
def parse_grammar(lLn):
    # empty line (comments ignored)?
    rePragmaLn = re.compile(r"^\s*\#\$\s*(?P<NAME>\w+)\s*\=\s*(?P<VAL>.*?)\s*$")
    # beginning of the right part rule
    reEq       = re.compile(r"^\s*\=")
    # name or full context or empty set (name in the RPI)
    reNm       = re.compile(r"^\s*(?P<NAME>[a-zA-Z_]\w*)")
    # name or full context or empty set (name in the RPI)
    reZero     = re.compile(r"^\s*0")
    # right part negative rule
    reNeg      = re.compile(r"^\s*-=\s*\"(?P<SUB>(?:[^\\\"]|\\\")+?)\"")
    # separator of several right part rules
    reOr       = re.compile(r"^\s*\|")
    # in the beginning of each right part rule user-defined order can be placed
    reOrd      = re.compile(r"^\s*\!(?P<ORD>\d+)")
    # also user-defined power can be placed after reOrd
    rePwr      = re.compile(r"^\s*\*(?P<POW>\d+)")
    # beginning of the RS parameter; contains:
    #   ALL  group that matches the whole RS parameter beginning;
    #   NAME group that will go to the RS::sGrpNm;
    #   NEG  group that will go to the RS::isNeg (true if NEG="!");
    #   SEP  group that will go to the RS::sLstSep.
    rePrmBegin = re.compile(r"""^\s*
        (?P<ALL>
            (?:(?P<NAME>[a-zA-Z_]\w*)(?P<NEG1>[=!])\~|(?P<NEG2>!))?
            (?:\?\"(?P<SEP>(?:[^\\\"]|\\\")+?)\"\:)?
        )
        \[""", re.VERBOSE
    )
    # set generator (if matched, then RP::isSet = 1) can be placed after
    # user-defined power (rePwr) groups of this regular expression directly
    # specify the following fields of the RP class:
    #   sSetSep, nSetMin, nSetMax and nSetAvg
    reSet      = re.compile(r"""^\s*\{
        (?:\s*sep\s*\=\s*\"(?P<SEP>(?:[^\\\"]|\\\")+?)\"\s*)? # separator
        (?:(?(SEP)\,|)                                        # minimum
        \s*min\s*\=\s*(?P<MIN>\d+)\s*
        )?
        (?:(?(SEP)\,|(?(MIN)\,|))                             # maximum
        \s*max\s*\=\s*(?P<MAX>\d+)\s*
        )?
        (?:(?(SEP)\,|(?(MIN)\,|(?(MAX)\,|)))                  # average
        \s*avg\s*\=\s*(?P<AVG>\d+)\s*
        )?
        \}""", re.VERBOSE
    )

    nLn = 0  # number of currently analyzed line of the lLn list
    # this will be returned as a result
    dNT = {}; dPragmas = {}

    while nLn < len(lLn):
        # sLn is constantly modified within current loop iteration by deleting
        # matched parts of its beginning (in skip_match function)
        # while sLn2 contains the original line for
        # error reporting purposes in the exception handler;
        # rstrip() removes end-of-line character
        sLn = sLnO = lLn[nLn].rstrip()
        nLn = nLn + 1

        # parse pragma line comment
        m = rePragmaLn.match(sLn)
        if m:
            dPragmas[m.group("NAME")] = m.group("VAL")
            continue

        # skip empty line
        if reEmptyLn.match(sLn): continue

        sBAD_LINE = "sBAD_LINE" # this is exception class string
        try:
            # parse nonterminal name
            m = reNm.match(sLn)
            if not m: raise sBAD_LINE, "Invalid rule name"
            sNT = m.group("NAME")
            sLn = skip_match(sLn, m)

            # add new nonterminal to dNT dictionary
            if sNT in dNT: nt = dNT[sNT]
            else: nt = NT(); dNT[sNT] = nt

            # lRS is internal representation of sRS,
            # which is built by the following loop
            lRS = []; sRS = ""

            # parse rule name parameter
            m = rePrmBegin.match(sLn)
            while m:
                sLn = skip_match(sLn, m)

                # nDepth means the depth of the square [] brackets;
                # nChr means number of currently analyzed character
                nDepth = 0; nChr = 0
                while nChr < len(sLn):
                    if sLn[nChr] == "[": nDepth = nDepth + 1
                    elif sLn[nChr] == "]":
                        # since rePrmBeging already matched the first "[",
                        # we check nDepth for the last closing square bracket
                        # before decrementing it
                        if not nDepth: break
                        nDepth = nDepth - 1
                    elif sLn[nChr] == "\\": nChr = nChr + 1
                    nChr = nChr + 1
                if nChr >= len(sLn): raise sBAD_LINE, "Can't find param's end"

                # keep just matched regular expression w/o surrounding []
                sRE = sLn[:nChr]
                # "manual" skipping of the matched string beginning
                sLn = sLn[nChr+1:]

                # init sGrpNm and sLstSep by mached values if any
                if m.groupdict()["NAME"]: sGrpNm  = m.group("NAME")
                else: sGrpNm  = ""
                if m.groupdict()["SEP"]:  sLstSep = m.group("SEP")
                else: sLstSep = ""

                isNeg = (m.groupdict()["NEG1"] and m.group("NEG1") == "!") or\
                        (m.groupdict()["NEG2"] and m.group("NEG2") == "!")

                lRS.append(RS(sRE, sGrpNm, sLstSep, isNeg))

                # separate RS parts in sRS by space
                if len(sRS): sRS = sRS + " "
                sRS = sRS + m.group("ALL") + "[" + sRE + "]"

                # try to match next RS part
                m = rePrmBegin.match(sLn)

            # in case of no parameters add parameter that match any context
            if not len(lRS): lRS.append(RS(".*")); sRS = "[.*]"

            # parse negative rule
            m = reNeg.match(sLn)
            if m:
                sLn = skip_match(sLn, m)
                if not reEmptyLn.match(sLn):
                    raise sBAD_LINE, "Unexpected rule continuation"
                sNegRE = m.group("SUB")
                if sRS not in nt.dNegR: nt.dNegR[sRS] = NegR(lRS, sNegRE)
                else: nt.dNegR[sRS].update(sNegRE)
                continue

            # parse rule right part begin
            m = reEq.match(sLn)
            if not m: raise sBAD_LINE, "Invalid rule right part begin"
            sLn = skip_match(sLn, m)

            # parse rule right part
            # if is1Ln is true then the first rule line (that contains equals
            # sign) is not empty and rule can be actually composed of several
            # rules with the same left-hand part separated by the "|" sign;

            # if is1Ln is false then there is only one rule ("|" separators are
            # invalid) but it can occupy several lines and each of them (except
            # the last one) triggers generation of EOL terminal; also indent of
            # each line is computed as a positive offset from the the indent of
            # the first line and used in the generation as well;
            # empty line ends the current rule
            is1Ln    = not reEmptyLn.match(sLn)
            # count of lines which belong to the current rule
            nLn2     = 0
            # isNewAlt is true when the new rule just begins (before any of its
            # items is parsed); isNewAlt becomes true after "|" sign if is1Ln
            # is true
            isNewAlt = 1

            # currently parsed rule right part;
            # it is created in each time isNewAlt is true
            rp = None

            while 1: # for each line of the rule
                # read next line except case of the first line of
                # the rule with is1Ln == true
                if not is1Ln or nLn2: # new line should be read
                    if nLn >= len(lLn): break
                    sLn = sLnO = lLn[nLn].rstrip()
                    nLn = nLn + 1

                # found end of rule (empty line) with is1Ln == false
                if reEmptyLn.match(sLn):
                    if is1Ln or not nLn2:
                        raise sBAD_LINE, "Unexpected empty line was found"
                    break

                # compute nLineIndent after the first line of not is1Ln rule
                if not is1Ln: # multi-line
                    if not nLn2: # first multi-line
                        n1stLineIndent = count_indent(sLn)
                    else:
                        nLineIndent = count_indent(sLn) - n1stLineIndent
                        if nLineIndent >= 0:
                            rp.lRPI.append(RPI(RPNI("", ""), nLineIndent))
                        else: raise sBAD_LINE, "Negative line indent detected"

                # there is not use of the nLn2 below,
                # so it can be safely incremented here
                nLn2 = nLn2 + 1

                while not reEmptyLn.match(sLn): # parse line items
                    # this flag became true if "|" was matched and if this was
                    # the last thing that was matched in the string, after this
                    # loop the exterior loop make another iteration to parse
                    # the following line
                    # (isNewAlt flag should enough for now)
                    # isLnCont = 0

                    # parse things that can appear only at the beginning of a
                    # rule right part: user order, user power and set generator;
                    # also make new RP object and add it to the current R object
                    if isNewAlt:
                        # that's right make it false until next "|" character
                        isNewAlt = 0
                        m = reOrd.match(sLn)
                        if m:
                            sLn = skip_match(sLn, m)
                            nUsrOrd = int(m.group("ORD"))
                        else: nUsrOrd = sys.maxint

                        m = rePwr.match(sLn)
                        if m:
                            sLn = skip_match(sLn, m)
                            nUsrPwr = int(m.group("POW"))
                        else: nUsrPwr = 1

                        # parse rule sNm set
                        m = reSet.match(sLn)
                        if m:
                            sLn = skip_match(sLn, m)
                            isSet = 1
                            sSep = m.group("SEP")
                            sMin = m.group("MIN")
                            sMax = m.group("MAX")
                            sAvg = m.group("AVG")
                        else:
                            isSet = 0
                            sSep = sMin = sMax = sAvg = None

                        if not sSep: sSep = " "
                        if sMin:
                            sMin = int(sMin)
                            if sMin < 0: raise sBAD_LINE,\
                                "Invalid rule set min " + str(sMin)
                        else: sMin = 1

                        if sMax:
                            sMax = int(sMax)
                            if sMax < sMin: raise sBAD_LINE,\
                                "Invalid rule set max " + str(sMax)
                        else:
                            sMax = sMin + 19
                            if sMax < 2 * sMin: sMax = 2 * sMin

                        if sAvg:
                            sAvg = int(sAvg)
                            if sAvg < sMin or sMax < sAvg: raise sBAD_LINE,\
                                "Invalid rule set avg " + str(sAvg)
                        else: sAvg = sMin + ((sMax-sMin)>>1)

                        rp = RP(nUsrOrd, nUsrPwr, isSet, sSep, sMin, sMax, sAvg)
                        if sRS in nt.dR: r = nt.dR[sRS]
                        else: r = R(lRS); nt.dR[sRS] = r
                        r.lRP.append(rp)

                    # match zero (empty set)
                    m = reZero.match(sLn)
                    if m:
                        sLn = skip_match(sLn, m)
                        rp.lRPI.append(RPI(RPNI("0")))
                        isNewAlt = 0
                        continue

                    # match name and its parameters, if any
                    rpni, sLn2 = parse_rpni(sLn)
                    if rpni != None:
                        # ignores empty line
                        if len(rpni.sNm) or len(rpni.sTrm): rp.lRPI.append(rpni)
                        sLn = sLn2
                        isNewAlt = 0
                        continue

                    # for "single-line", parse "|" possibility
                    if is1Ln:
                        m = reOr.match(sLn)
                        if m:
                            sLn = skip_match(sLn, m)
                            if not len(rp.lRPI):
                                raise sBAD_LINE, "Empty rule makes no sense"
                            if __debug__: rp = None
                            # (isNewAlt flag should enough for now)
                            #isLnCont = 1
                            isNewAlt = 1
                            continue

                    raise sBAD_LINE, "Unexpected rule item"

                # despite the fact that isLnCont is initialized only in the
                # previous loop which body can be not executed at all it is
                # initialized always for is1Ln == true rule because loop body
                # always execute at least once in this case, since in fact,
                # is1Ln = not reEmptyLn.match(sLn) and sLn is not changed till
                # the loop test while not reEmptyLn.match(sLn)
                # (isNewAlt flag should be enough for now)
                if is1Ln and not isNewAlt: break

            if not len(rp.lRPI): raise sBAD_LINE, "Empty rule makes no sense"

        except sBAD_LINE, s:
            err("!!! " + s + " in line #" + str(nLn) + ":\n" +
                sLnO + "\n" + "!!! when parsing this:\n" + sLn)

    for pragma in dPragmas.keys():
        if pragma not in setKnownPragmas: trace("Unknown pragma: " + pragma)

    if "GEN_LENGTH" not in dPragmas: dPragmas["GEN_LENGTH"] = 10000
    else: dPragmas["GEN_LENGTH"] = int(dPragmas["GEN_LENGTH"])
    return dNT, dPragmas

# here we place checks that is convenient to check after the whole grammar
# is parsed by parse_grammar function (checking for "Pointless zero string
# found" is just little more convenient here);
# actually in future actual referenced can be computed here, so this function
# is called link_grammar, to accelerate GEN_STR function (see TODO in GEN_STR)
def link_grammar(dNT): # check grammar links
    for nt in dNT.values():
        for r in nt.dR.values():
            for rp in r.lRP:
                for rpi in rp.lRPI:
                    sNm = rpi.sNm
                    if not len(sNm): continue
                    if sNm != "0":
                        if sNm != "*" and sNm not in r.dsGrp and sNm not in dNT:
                            err("Undefined name: " + sNm)
                    elif len(rp.lRPI) != 1: err("Pointless zero string found")
                    for rpni in rpi.lRPNI:
                        sNm2 = rpni.sNm
                        if len(sNm2) and sNm2 != "0" and sNm2 != "*" and\
                           sNm2 not in r.dsGrp and sNm2 not in dNT:
                            err("Undefined name: " + sNm2)

# for each R/RP nLen contains the number of steps in the shortest derivation of
# a sentence starting with that nonterminal; algorithm computes only partial
# results that should be supplemented by hand provided "!<num>" hints; rules
# with "*", parameter names and ambiguously defined nonterminal name
# (with several different context parameters) block propagation (is2BIG = 1)

# algorithm (phase one of Purdom's algorithm) was adopted from this paper:
#   "An Interpretation of Purdom's Algorithm for
#   Automatic Generation of Test Cases" by
#   Brian A. Malloy and James F. Power

def find_some_short_rules_in_grammar(dNT):
    is1More = 1 # should we make another pass through dNT dictionary?
    while is1More:
        is1More = 0
        for nt in dNT.values():
            for r in nt.dR.values():
                for rp in r.lRP:
                    # accumulate nSum of all terminal string lengths and
                    # nSum of already computed nonterminals,
                    # if possible (is2BIG = 0)
                    nSum = 0; is2BIG = 0
                    for rpi in rp.lRPI:
                        sNm = rpi.sNm
                        if len(sNm):
                            if sNm != "0":
                                # context dependent name or nonterminal name
                                # that has several matching context (or at
                                # least with different string representation)
                                if sNm == "*" or sNm in r.dsGrp or\
                                   len(dNT[sNm].dR) > 1:
                                    is2BIG = 1
                                    break
                                if __debug__ and len(dNT[sNm].dR) != 1:
                                    raise AssertionError
                                nLen = dNT[sNm].dR.values()[0].nLen
                                if nLen != sys.maxint: nSum += nLen
                                else: is2BIG = 1; break

                        # even if rpi is not terminal string length of the
                        # rpi.sTrm will be zero and will not affect nSum
                        else: nSum += len(rpi.sTrm)

                    # if nSum is computed and smaller than before then update
                    if not is2BIG and nSum < rp.nLen:
                        rp.nLen = nSum
                        # update R class and require another pass through dNT
                        if nSum < r.nLen: r.nLen = nSum; is1More = 1

# this function performs computation of the nPwr of all nonterminal rules,
# not only ones that are directly reachable from the starting nonterminal
def compute_grammar_rule_powers(dNT):

    for sNT in dNT:
        if __debug__ and dNT[sNT].nPwrSum: raise AssertionError
        #print "!!!"+sNT+"\n"
        dNT[sNT].nPwrSum = compute_nt_power(dNT, sNT, dict())
    # this division by Maximum Common Divisor must be done in the second pass
    # because in the other case this division will influence other nonterminals
    # powers that can be computed from powers divided by different divisors
    # (currently I do not see any point in that division since current GEN_STR
    # algorithm is immune to magnitude of these powers)
    #for nt in dNT.values():
    #    # handle special case of one dividend
    #    if len(nt.dR) == 1 and len(nt.dR.values()[0].lRP) == 1:
    #        nt.nPwrSum = nt.dR.values()[0].lRP[0].nPwrSum = 1
    #        continue
    #    nDivisor = 2
    #    is1More  = 1
    #    while is1More:
    #        isAllDivided = 1
    #        for rs in nt.dR.values():
    #            for rp in rs.lRP:
    #                if rp.nPwr < nDivisor:
    #                    is1More = 0
    #                    isAllDivided = 0
    #                    break
    #                if rp.nPwr % nDivisor:
    #                    isAllDivided = 0
    #                    break
    #            if not isAllDivided: break
    #        if isAllDivided:
    #            nt.nPwrSum = nt.nPwrSum / nDivisor
    #            for rs in nt.dR.values():
    #                for rp in rs.lRP:
    #                    rp.nPwr = rp.nPwr / nDivisor
    #        else: nDivisor = nDivisor + 1

# this recursive function is called from the compute_grammar_rule_powers
# function to return the sum all rule powers for the give nonterminal sNm
# in the dNT dictionary; other dictionary dsNm stores already considered
# nonterminal names to avoid infinite recursion;
# rule power is a product of its nonterminal power sums
def compute_nt_power(dNT, sNm, dsNm):
    nt = dNT[sNm]
    if nt.nPwrSum: return nt.nPwrSum
    if sNm in dsNm: return 1
    dsNm[sNm] = 1
    nPwrSum = 0
    for r in nt.dR.values():
        for rp in r.lRP:
            nPwr = 1
            #for rpi in rp.lRPI:
            #    sNm2 = rpi.sNm
            #    # consider only nonterminal names...
            #    if len(sNm2) and sNm2 != "0" and sNm2 != "*" and\
            #       sNm2 not in r.dsGrp:
            #        nPwr = nPwr * compute_nt_power(dNT, sNm2, dsNm)
            #        print "!!!!! "+sNm+" "+sNm2+" "+str(nPwr)
            nPwr = nPwr * rp.nUsrPwr
            rp.nPwr = nPwr
            nPwrSum = nPwrSum + nPwr
    del dsNm[sNm]
    return nPwrSum

# print components of the given dNT dictionary (for debugging purposes)
def print_grammar(dNT, grammar_file):
    lsNT = dNT.keys()
    lsNT.sort()
    for sNT in lsNT:
        nt = dNT[sNT]
        print>>grammar_file, sNT + ", power_sum = " + str(nt.nPwrSum)
        lsRS = nt.dR.keys()
        lsRS.sort()
        for sRS in lsRS:
            r = nt.dR[sRS]
            print>>grammar_file, "\t" + "\"" + sRS + "\": len = " + str(r.nLen)
            for rp in r.lRP:
                print>>grammar_file, 2 * "\t" +\
                    "rule user_power = " + str(rp.nUsrPwr) +\
                    ", power = " + str(rp.nPwr) +\
                    ", len = " + str(rp.nLen)
                for rpi in rp.lRPI:
                    if len(rpi.sNm):
                        print>>grammar_file, 3 * "\t" + rpi.sNm
                        for rpni in rpi.lRPNI:
                            if len(rpni.sNm):
                                print>>grammar_file, 4 * "\t" + rpni.sNm
                            else: print>>grammar_file, 4 * "\t" +\
                                "\"" + rpni.sTrm + "\""

                    elif len(rpi.sTrm): print>>grammar_file, 3 * "\t" +\
                        "\"" + rpi.sTrm + "\""
                    else: print>>grammar_file, 3 * "\t" +\
                        "EOL + \"" + rpi.sEOL + "\""

        lsSubR = nt.dNegR.keys()
        lsSubR.sort()
        for sSubR in lsSubR:
            r = nt.dNegR[sSubR]
            print>>grammar_file, "\t" +\
                "-\"" + sSubR + "\": \"" + r.reNeg.pattern + "\""
        print>>grammar_file

################################################################################
################################################################################
################################################################################
#
# BEGIN OF GRAMMAR STRING GENERATION ALGORITHM
#

# this important function takes context string (sCtxt) and matches it with given
# list of RS classes, returning dictionary of named groups mapped to the
# matched values (not matched groups are matched to the empty strings anyway)
# if the match was successful and None if not;
# was successful match all RS list items should be matched;
# each list item is matched with the whole context or one of the named group
# matched by one of the previous RS list items;
# RS list item can be a "list match": in this case matched string is separated
# by the separator string to list of strings and the first random string match
# from that list is used (if no list item can be matched, the function returns
# None)
def match_params(sCtxt, lRS):
    dGrp = dict()
    for rs in lRS: # for each consecutive RS list item...
        # match the whole context string or already matched named group?
        # string to be matched is placed to the variable "s"
        if len(rs.sGrpNm):
            if rs.sGrpNm not in dGrp: err("Undef group name: " + rs.sGrpNm)
            s = dGrp[rs.sGrpNm]
        else: s = sCtxt

        # is our match a "list match"?
        # if yes, use separator string to form a list "l" and randomly shuffle
        # it (later list items will be consecutively checked for match);
        # if no, form a fake list from one element
        if len(rs.sLstSep):
            l = s.split(rs.sLstSep)
            random.shuffle(l)
        else: l = [s]

        # determine wherever we need to compile regular expression if it
        # contains unresolved named group references that values became
        # (hopefully :) known only now
        if len(rs.lsUnkRef):
            sRE = rs.sRE
            # for each unresolved group name referenced discovered during
            # construction of the RS class object...
            for sUnkRef in rs.lsUnkRef:
                if sUnkRef not in dGrp:
                    err("Undef group name: " + sUnkRef)
                sRE = re.sub(
                    r"\(\?P\=" + sUnkRef + r"\)", re.escape(dGrp[sUnkRef]), sRE, 1
                )
            reMatch = re.compile(sRE)
        
        else: reMatch = rs.re # nothing should be recompiled, cool!

        for s in l: # try to match list items until the first match or list end
            m = reMatch.match(s)
            if (m and not rs.isNeg) or (rs.isNeg and not m): break

        if (not m): 
            if (rs.isNeg): continue
            return None
        else:
            if (rs.isNeg): return None
        
        # dGrp is union of all matched group names
        # later match of the same name overrides its previous one
        dGrp.update(m.groupdict())
        # register not matched groups as empty anyway
        for sGrpNm in reMatch.groupindex:
            if sGrpNm not in dGrp: dGrp[sGrpNm] = ""

    return dGrp

# helper class used to simply store detected match characteristics, such as
# number of match in some external list (nMatch), number of rule context
# (R class) for that match (nR) and number of selected rule (RP class) for that
# match (nRP)
class Pwr2:
    def __init__(self, nMatch, nR, nRP):
        self.nMatch = nMatch
        self.nR     = nR
        self.nRP    = nRP

# some context information used during string generation in the GEN_STR
# function, such as number (nChr) of already generated characters (to know where
# to begin the stopping process by choosing only the shortest rules), string
# sIndent that stores the current line indent
class GenStats:
    def __init__(self, old_gs = None, nChr = 0, sIndent = ""):
        if old_gs == None: self.nChr = 0
        else: self.nChr = old_gs.nChr + nChr
        self.sIndent = sIndent


def gen_rpni_ctxt(rpni, dGrp, dsGrp, dNT, dPragmas, sCtxt):
    sCtxt2 = ""
    for rpni2 in rpni.lRPNI:
        sNm = rpni2.sNm
        if len(sNm):
            if sNm == "*":            sCtxt2 = sCtxt2 + sCtxt
            elif sNm in dsGrp:
                if dGrp[sNm] != None: sCtxt2 = sCtxt2 + dGrp[sNm]
            else: sCtxt2 = sCtxt2 + GEN_STR(dNT, dPragmas, sNm,
                gen_rpni_ctxt(rpni2, dGrp, dsGrp, dNT, dPragmas, sCtxt)
            )
        else: sCtxt2 = sCtxt2 + rpni2.sTrm
    return sCtxt2

# this is really the main (recursive) function that generate random string of
# the language specified by the parameterized context free grammar dNT;
# actually string is generated for the sNT grammar nonterminal name;
# sCtxt is context of the sNT nonterminal;
# lsTr (trace) is used for grammar debugging purposes (so it is needed not only
# when __debug__ == 1) when there is a need to display stack of the nonterminals
# and their context used;
# gs is object of the GenStats class which describe additional context
# information such as number of characters in the already generated string or
# current indent
def GEN_STR(dNT, dPragmas, sNT, sCtxt = "", lsTr = None, gs = None):
    # create initial values of these objects...
    if lsTr == None: lsTr = []
    if gs == None: gs = GenStats()

    # build generation trace (just for grammar debugging)
    lsTr.append(sNT + " [" + sCtxt + "]")

    # TODO: replace this search in the dictionary by some kind of reference
    # that will be created in the link_grammar function
    nt = dNT[sNT]

    dsGrp = None

    # this condition produces rp and dGrp
    if gs.nChr > dPragmas["GEN_LENGTH"]:
        # use the "shortest" rule to finish generated string as soon as possible
        rp  = None
        # number matched rules (if greater than one, error "fail to select the
        # shortest rule" will be triggered if all matched rules do not have
        # used-selected order and no automatically-computed minimal lengths)
        nRP = 0
        for r in nt.dR.values():
            dGrp2 = match_params(sCtxt, r.lRS)
            if dGrp2 == None: continue
            for rp2 in r.lRP:
                nRP = nRP + 1
                # record rp and dGrp for the first match or the user-defined
                # order is better or at last if automatically-computed minimal
                # rule length is better
                if not rp or rp.nUsrOrd > rp2.nUsrOrd or rp.nLen > rp2.nLen:
                    rp    = rp2
                    dGrp  = dGrp2
                    dsGrp = r.dsGrp
        if not rp: err("Can't match nonterminal context:\n" + "\n".join(lsTr))
        if nRP > 1 and rp.nUsrOrd == sys.maxint and rp.nLen == sys.maxint:
            err("Can't select the shortest rule (use #<order>):\n" +
                "\n".join(lsTr))

    else: # use randomly chosen rule
        ldGrp    = [] # list of matches dictionaries with group names
        lnPwrSum = [] # number list that form ranges: [0..l(1)) [l(1)..l(2))...
        lPwr2    = [] # list of Pwr2 classes that record found matches
        nPwrSum  = 0  # sum of powers of all matches rules
        nR       = 0  # number of current rule context (class R)
        for r in nt.dR.values():
            dGrp = match_params(sCtxt, r.lRS)
            if dGrp != None:
                nRP = 0 # number of current rule (class RP)
                for rp in r.lRP:
                    nPwrSum = nPwrSum + rp.nPwr
                    lnPwrSum.append(nPwrSum)
                    # record item within ldGrp and how to find this rule
                    # afterwards
                    lPwr2.append(Pwr2(len(ldGrp), nR, nRP))
                    nRP = nRP + 1
                ldGrp.append(dGrp)
            nR = nR + 1
        if not nPwrSum:
            err("Can't match nonterminal context:\n" + "\n".join(lsTr))
        # just random number in the range  of [0, nPwrSum-1]
        nRnd  = random.randint(0, nPwrSum-1)
        # select the range in the lnPwrSum that contains this random point
        nPos  = bisect.bisect(lnPwrSum, nRnd)
        # that range gives us rp and sGrp of the corresponding match
        pwr2  = lPwr2[nPos]
        r     = nt.dR.values()[pwr2.nR]
        rp    = r.lRP[pwr2.nRP]
        dGrp  = ldGrp[pwr2.nMatch]
        dsGrp = r.dsGrp

    # if selected rule contains set generator then randomly define the number
    # of set items to generate (nSetItemCount) or generate only the single item
    if rp.isSet: nSetItemCount = random.randint(rp.nSetMin, rp.nSetMax)
    else: nSetItemCount = 1

    sRes = ""      # this string contains the currently generated string;
    dsSet = dict() # this dictionary contains set items of generated string,
                   # used for set generator

    # external loop for each set item that need to be generated
    for nSetItem in range(nSetItemCount):
        # in case we've generated string that is already in the dsSet or it
        # does not satisfy the negative rules (if any) this counter is used to
        # abort the generation algorithm after a big number of tries to avoid
        # its freeze (that can easily happen because of incorrect grammar)
        nTry = 0
        while 1:
            nTry = nTry + 1
            if nTry == 100:
                trace("100 generation attempts detected:\n" + "\n".join(lsTr))
            if nTry > 1000000:
                err("Too many generation attempts failed:\n" + "\n".join(lsTr))

            sRes2 = "" # this is generated string for current set item
            sIndent = gs.sIndent # inherit previous line indent
            for rpi in rp.lRPI: # traverse all rp items
                if len(rpi.sNm):
                    # generate name (nonterminal or parameter (named group))
                    sNm = rpi.sNm
                    if sNm   == "0": pass # do nothing
                    elif sNm == "*": sRes2 = sRes2 + sCtxt # append all context
                    # append named group value
                    elif sNm in dsGrp:
                        if dGrp[sNm] != None: sRes2 = sRes2 + dGrp[sNm]
                    else: sRes2 = sRes2 + GEN_STR(
                        dNT, dPragmas, sNm,
                        gen_rpni_ctxt(rpi, dGrp, dsGrp, dNT, dPragmas, sCtxt),
                        lsTr, GenStats(gs, len(sRes2), sIndent)
                    )

                # generate terminal string
                elif len(rpi.sTrm): sRes2 = sRes2 + rpi.sTrm

                else: # generate end-of-string, update indent for the next lines
                    sIndent = gs.sIndent + rpi.sEOL
                    sRes2 = sRes2 + "\n" + sIndent

            # if this item was already generated, then it can't be added to set
            if sRes2 in dsSet: continue

            # reject generated string if it does satisfy negative match
            isRejected = 0
            
            for r in nt.dNegR.values():
                if r.reNeg.match(sRes2):
                    isRejected = 1
                    break
                dGrp = match_params(sCtxt, r.lRS)
                if not dGrp: continue
            if isRejected: continue

            break # sRes2 was not rejected so it can be appended to sRes!

        # record already produced sRes2 for its uniqueness in the sRes
        dsSet[sRes2] = 1
        # if we've already generated some items then use separator between
        # sRes2 strings in the sRes string
        if nSetItem: sRes = sRes + rp.sSetSep
        sRes = sRes + sRes2

    lsTr.pop()
    return sRes

#
# END OF GRAMMAR STRING GENERATION ALGORITHM
#
################################################################################
################################################################################
################################################################################

# entry point for getting grammar (dNT) from the list of strings
def get_grammar(sLn):
    dNT, dPragmas = parse_grammar(sLn)
    link_grammar(dNT)
    find_some_short_rules_in_grammar(dNT)
    compute_grammar_rule_powers(dNT)
    return dNT, dPragmas

parser = OptionParser(
    usage="%prog [options] <input_grammar_file >output_program_file",
    version="%prog" + version
)
parser.add_option(
    "-g", "--write_parsed_grammar_file", dest="grammar_filename",
    help="write parsed grammar to file (for debugging purposes)",
    metavar="FILE"
)
(options, args) = parser.parse_args()

# this is where this program starts
dNT, dPragmas = get_grammar(sys.stdin.readlines())
if options.grammar_filename != None:
    print_grammar(dNT, file(options.grammar_filename, "w"))

sys.setrecursionlimit(10000);
print GEN_STR(dNT, dPragmas, "S")
