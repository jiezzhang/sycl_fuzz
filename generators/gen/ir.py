""" Intermediate Representation (IR)
    provides building IR and interpretaion of simple objects
"""

import reader
import syntax

##
## TODO:
##  consider if generation should be placed inside IR-class
##  consider using context instead of vars dict
##  consider using Ultra Optimizations!
##  consider move eval() and match() code out of here (to gen?)
## 

# global variable
class counter:
    count = 0
    cur = 0
    fin = None

    def reset(self, count):
        counter.count = count
        counter.cur = 0
        counter.fin = False

class func:
    def __init__(self,f,sn):
        self.__call__ = f.__call__
        self.sn = sn
        self.__class__ = func
func.__class__ = func

# Abstract classes
class IRNode:
    """ IR tree node, base class """

    def __init__(self):
        pass

    def setSyntaxNode(self,sn):
        """ SN shall be set only for nodes for which
            it has mind; for ex: identifiers """
        self.sn = sn
    def checkType(self, type):
        return isinstance(self, type)
    def printNode(self):
        raise "Must be implemented. RLY!"

class Pat:
    """ base class for all patterns """
    def __init__(self):
        pass
    
    def matchType(self, node):
        return self.__class__ == node.__class__

    def match(self,e,vars):
        """ Match current expression with `e'
            returns False if cannot be matched
            adds (Id -> Value) to vars table if variable has
              been matched """
        raise "Must be implemented!"

class Expr:
    """ base class for evaluable expression """
    def __init__(self):
        pass

    def eval(self,vars):
        """ Evaluate value of expression using variable
            table vars: Id -> Value
            returns value of expression
        """
        raise "Must be implemented!"

    def slen():
        raise "Must be implemented"

    def checkLen(self,vars):
#        if counter.cur > counter.count:
#            counter.fin = True
        counter.cur += 1

class Roulette:
    """ roulette base class """
    def __init__(self):
        pass

    def roulette(self,match):
        """ Choose a variants from variants """
        raise "Must be implemented!"

    __call__ = roulette
#
class Id(IRNode, Expr, Pat):
    """ IR for identifier (for variables only, not for rules)
        name -> name of identifier
    """

    def __init__(self, name):
        self.name = name
    def __eq__(self, id):
        return self.name == id.name
    def __hash__(self):
        return hash(self.name) ^ hash(Id)
    def __str__(self):
        return self.name

    def isAnonymous(self):
        return self.name == "_"

    def printNode(self, s="", c=""):
        print "%s(Id: %s )" % (s, self.name)

    def eval(self,vars):
        """ return value of Id in vars """
        self.checkLen(vars)
        # return value of variable in table
        try:
            x = vars[self]
        except KeyError, e:
            raise UndefinedVariableException(
                "undefined variable `%s' used" % self.name,
                self.sn )
        return x

    def slen(self):
        return 2

    def matchType(self,e):
        """ variable is always matched """
        return True
    
    def match(self,e,vars):
        """ variable can be matched in any case,
            so just add new value to table if variable is not _
        """
        if not self.isAnonymous():
            # assign e to current Id
            assert self not in vars
            vars[self] = e
        # variable is always matched
        return True
        
#
class Num(IRNode, Expr,Pat):
    """ IR for constant number value
        value -> value of constant
        use int() to get integer value
    """
    # TODO all values be long
    def __init__(self,value):
        assert isinstance(value,int)
        self.value = value
    def __int__(self):
        return self.value

    def printNode(self, s="", c=""):
        print "%s(Num: %s )" % (s,str(self.value))

    def eval(self,vars):
        """ return the number itself """
        self.checkLen(vars)
        return self.value

    def slen(self):
        return len(str(self.value))

    def matchType(self,e):
        return e.__class__ is int
    
    def match(self,e,vars):
        """ compare numbers if classes are matched """
        return self.matchType(e) and self.value == e

#
class Str(IRNode, Expr,Pat):
    """ IR for constant string value
        value -> string itself

        use str() to get string value
    """

    def __init__(self,value):
        assert isinstance(value, str)
        self.value = value
    def __str__(self):
        return self.value
    def printNode(self, s="", c=""):
        print "%s(Str: %s )" % (s,self.value.replace("\n",r'\n'))

    def eval(self,vars):
        """ return the string itself """
        self.checkLen(vars)
        return self.value

    def slen(self):
        return len(self.value)

    def matchType(self,e):
        return e.__class__ is str;
        # OR alternatively
        return e.__class__ is self.value.__class__
    
    def match(self,e,vars):
        """ compare strings if classes are matched """
        return self.matchType(e) and self.value == e
        
class Newline(IRNode, Expr):
    """ IR for newline
        value = spaces
    """

    indent = 0
    def __init__(self,value,prefix="\n"):
        assert value.__class__ is int
        self.value = value
        self.prefix = prefix
        
    def __str__(self):
        return "\n" + self.value
    def printNode(self, s="", c=""):
        print "%s(Newline: %s'%s' )" % (s,self.prefix.replace("\n",r'\n'),self.value)

    def resetIndent(self):
        Newline.indent = 0

    def unindent(self,value):
        self.value -= value

    def eval(self,vars):
        """ increase Newline.indent and
            returns indent as string """
        self.checkLen(vars)
        Newline.indent += self.value
        return self.prefix+(' '*Newline.indent)

    def slen(self):
        return 0

#
class List(IRNode, Expr, Pat):
    """ IR for list of values
        values -> list of contained values
    """
    
    def __init__(self,values=None):
        if values is None: values = []
        self.values = values
    
    def addValue(self, value):
        self.values.append(value)

    def printNode(self, s="", c=""):
        print "%s(List)" % s
        if len(self.values):
            for e in self.values[:-1]:
                e.printNode( c + "|--", c + "|  " )
            self.values[-1].printNode( c + "`--", c + "   ")

    def eval(self,vars):
        """ returns a list with values """
        self.checkLen(vars)
        return [v.eval(vars) for v in self.values]

    def slen(self):
        return sum( [v.slen() for v in self.values] )
        # OR equally
        #return sum( v.slen() for v in variants )

    def matchType(self,e):
        return e.__class__ is list

    def match(self,e,vars):
        """ List have special mean:
            we should match all elements of list
            to have whole list matched """
        if not self.matchType(e):
            return False
        # if lists have different length then not matched
        if len(e) != len(self.values):
            return False
        for (av,ae) in zip(self.values,e):
            if not av.match(ae,vars):
                return False
        # otherwise we have all list matched
        return True
#
class Cons(IRNode, Expr, Pat):
    """ IR for operation "head:tail"
        head -> head of the list
        tail -> tail of the list
    """

    def __init__(self, head, tail):
        self.head = head
        self.tail = tail

    def printNode(self, s="", c=""):
        print "%s(Cons)" % (s,)
        self.head.printNode( c + "|--", c + "|  " )
        self.tail.printNode( c + "`--", c + "   ")

    def eval(self,vars):
        """ returns list with `head' as first element
            and a `tail' as a tail; whatever, see below """
        self.checkLen(vars)
        head = [self.head.eval(vars)]
        tail = self.tail.eval(vars)
        if tail.__class__ is not list:
            raise TypeException(
                "second argument of `:' operator should always "
                "be a list, but have `%s'" %str(tail), self.sn )
        return head + tail

    def slen(self):
        return self.head.slen() + self.tail.slen()
    
    def matchType(self,e):
        return e.__class__ is list

    def match(self,e,vars):
        """ to match Cons we should have list
            with head and tail matched """
        # it is required for list to have at least one element
        if not ( self.matchType(e) and len(e) > 0):
            return False

        if not ( self.head.match(e[0],vars)
          and self.tail.match(e[1:],vars) ):
            return False
        return True
#
class Func(IRNode, Expr):
    """ IR for function object
    """
    def __init__(self,f,sn):
        self.func = func(f,sn)
        self.setSyntaxNode(sn)

    def printNode(self, s="", c=""):
        print "%s(Func)" % s

    def eval(self,vars):
        """ returns function object
        """
        self.checkLen(vars)
        return self.func

    def slen(self):
        return 0
#
class Cat(IRNode, Expr):
    """ IR for catenate (a b c d)
        values -> list of catenated values
    """
    def __init__(self, values = None):
        if values is None: values = []
        self.values = values

    def addValue(self, value):
        self.values.append(value)

    def printNode(self, s="", c=""):
        print "%s(Cat)" % s
        if len(self.values):
            for e in self.values[:-1]:
                e.printNode( c + "|--", c + "|  " )
            self.values[-1].printNode( c + "`--", c + "   ")

    def eval(self,vars):
        """ catenate values and return them as one string
            here we go with IMPORTANT NOTICE:
            only atoms could be really catenated
            raise runtime error if we have list on our way
            in fact any of these runtime exceptions could only
            be caused by `syntax error', so just throw
            syntax exception.
        """
        self.checkLen(vars)
        atoms = []
        pairs = [(atom, atom.eval(vars)) for atom in self.values]
        for (a, e) in pairs[::-1]:
            if e.__class__ is func:
                try: (argsAtom, args) = atoms.pop()
                except IndexError, ie:
                    atoms.append( (a, e) )
                    continue
                if args.__class__ is not list:
                    raise TypeException(
                        "list of arguments excepted instead of "
                        "sole value", argsAtom.sn )
                try: atoms.append( (a, e(args)) )
                except RuntimeError, re:
                    raise IRException( str(re), a.sn )
            else:
                atoms.append( (a, e) )

        if len(atoms) > 1:
            cat = ""
            for (a, e) in atoms[::-1]:
                if e.__class__ not in [str,int]:
                    raise TypeException(
                        "non-str value `%s' is being catenated" %str(e),
                        a.sn )
                cat += str(e)
        else:
            cat = atoms[0][1]
        return cat

    def slen(self):
        return sum( [ v.slen() for v in self.values ] )
# 
class Apply(IRNode, Expr):
    """ IR for rule apply, not for rule itself
        name -> name of rule (as str object)
        args -> list of Expr objects for rule call
    """
    def __init__(self, name, args):
        self.name = name
        self.rule = None    # should be defined during linking phase
        self.args = args

    def printNode(self, s="", c=""):
        print "%s(Apply: %s )" % (s, self.name)
        if len(self.args):
            for e in self.args[:-1]:
                e.printNode( c + "|--", c + "|  " )
            self.args[-1].printNode( c + "`--", c + "   ")
    
    def link(self,rule):
        """ link apply to a rule or to builtin """
        self.rule = rule.__call__
    
    def eval(self,vars):
        """ evaluate args and call appliance for a rule """
        self.checkLen(vars)
        assert self.rule is not None
        # evaluate args
        args = [e.eval(vars) for e in self.args]
        # and apply rule via __call__
        try: return self.rule(args)
        except NoMatchException, ge:
            raise IRException( str(ge), self.sn )
        except BuiltinException, be:
            raise IRException( str(be), self.sn )
        except RuntimeError, re:
            raise IRException( str(re), self.sn )

    def slen(self):
        return 1000000000 # 1G

class Rule(IRNode):
    """ Ah, this is the most important class out there
        IR for Rule itself
        name -> name Id
        matches -> list of Match objects
    """
    def __init__(self, name):
        self.name = name
        self.matches = []

    def addMatch(self, match):
        self.matches.append( match )

    def printNode(self, s="", c=""):
        print "%s(Rule: %s )" % (s, self.name)
        if len(self.matches):
            for e in self.matches[:-1]:
                e.printNode( c + "|--", c + "|  " )
            self.matches[-1].printNode( c + "`--", c + "   ")

    def apply(self,args):
        """ apply rule to args:
            match arguments and return result
            first matched match should be choosed
        """
        assert len(self.matches) > 0
        matched = None
        for m in self.matches:
            # prepare variables table
            vars = {}
            # choose first matched
            if m.match(args,vars):
                # stop process
                matched = m
                break
        else:   # no match, do runtime exception
            raise NoMatchException(
                "No match for rule `%s' with such arguments: %s\n" %
                    (str(self.name),str(args)) )
        # matched and have vars
        return matched.eval(vars)
    
    # must define __call__
    __call__ = apply
        

# this class is not IRNode itself
class Match(Expr, Pat):
    """ Auxilary class for Rule representation
        pattern -> match pattern
        vars -> variables, which may be used in matched sentence
        defs -> definitions, which should be calculated before
            variants and variables for those defs should be
            placed into vars
        variants -> list of variants for the match
    """
    
    def __init__(self, pattern,
      vars=None, defs=None, conds=None, variants=None):
        if vars is None: vars = {}
        if defs is None: defs = []
        if conds is None: conds = []
        if variants is None: variants = []
        self.pattern = pattern  # pattern of the match
        self.vars = vars        # dict: Id -> None
        self.defs = defs        # list of Def in preserved order
        self.conds = conds      # lsit of Cond
        self.roulette = None
        self.variants = variants# list of Variant
        self.shortest = None
        self.resolveShortest()
    
    def resolveShortest(self):
        sv = []
        slens = [ v.slen() for v in self.variants ]

        m = min( slens )
        if m >= 1000000000: # FIX: better check
            sv.append(self.variants[0])
        else:
            for (v, l) in zip(self.variants, slens):
                if l == m:
                    sv.append(v)
            if len(sv) == 0:
                raise NoShortestRuleException(
                    "unable to determine the shortest rule",
                    self.variants[0] )
        self.shortest = sv

    # printing routines
    def printPattern(self,s="",c=""):
        self.pattern.printNode(s,c)
    
    def printDefs(self,s="",c=""):
        print "%s(Definitions)" % (s,)
        if len(self.defs):
            for e in self.defs[:-1]:
                e.printNode( c + "|--", c + "|  " )
            self.defs[-1].printNode( c + "`--", c + "   ")
    
    def printVariants(self,s="",c=""):
        print "%s(Variants)" % (s,)
        if len(self.variants):
            for e in self.variants[:-1]:
                e.printNode( c + "|--", c + "|  " )
            self.variants[-1].printNode( c + "`--", c + "   ")

    def printShortest(self,s="",c=""):
        print "%s(Shortest)" % (s,)
        if len(self.shortest):
            for e in self.shortest[:-1]:
                e.printNode( c + "|--", c + "|  " )
            self.shortest[-1].printNode( c + "`--", c + "   ")
    
    def printNode(self, s="", c=""):
        print "%s(Match)" % (s,)
        self.printPattern( c + "|--", c + "|  " )
        self.printDefs( c + "|--", c + "|  " )
        self.printShortest( c + "|--", c + "|  " )
        self.printVariants( c + "`--", c + "   " )

    def link(self,roulette):
        """ returns a luckyest variant of variants """
        assert isinstance(roulette,Roulette)
        self.roulette = roulette
    
    def eval(self,vars):
        """ we have vars from matching;
            now vars should be extended with defs
            after that return evaluated right part
        """
        self.checkLen(vars)
        # choose variant
        v = self.roulette(self)
        # evaluate right part
        return v.eval(vars)
    
    def match(self,args,vars):
        """ match args:
            it's simple -- just call pattern.match(args)
            also check conds to satisfiable
        """
        assert vars.__class__ is dict
        assert len(vars) == 0
        if not self.pattern.match(args,vars):
            return False
        # enrich vars with defs if matched
        for d in self.defs:
            if not d.match(vars):
                return False
        if len(self.conds) > 0:
            for cond in self.conds:
                if not cond.satisfied(vars):
                    return False
        return True

class Pattern(IRNode, Pat):
    """ Pattern representation for Match class """
    def __init__(self, pats):
        self.pats = pats

    def printNode(self,s="",c=""):
        print "%s(Pattern)" % (s,)
        if len(self.pats):
            for e in self.pats[:-1]:
                e.printNode( c + "|--", c + "|  " )
            self.pats[-1].printNode( c + "`--", c + "   ")

    def match(self,e,vars):
        """ for each pattern of self.pats matches it
            to given list of arguments e """
        # it is required for e to be list of arguments
        assert e.__class__ is list
        # number of arguments should be the same as in pattern
        if len(e) != len(self.pats):
            return False
        # it is also required for vars to be empty dict()
        assert isinstance(vars,dict)
        assert len(vars) == 0
        # match each pattern
        for (pat,atom) in zip(self.pats,e):
            if not pat.match(atom,vars):
                vars.clear()
                return False
        return True

class Def(IRNode, Pat):
    """ Definition class
        name -> defined Id
        expr -> expression used for definition
    """
    def __init__(self, pattern, expr):
        self.pattern = pattern
        self.expr = expr

    def printNode(self,s="",c=""):
        print "%s(Def:)"%s
        self.pattern.printNode( c + "|--", c + "   " )
        self.expr.printNode( c + "`--", c + "   " )

    def match(self,vars):
        """ define all definition using vars variable
            after that ADD these values to VARS under its names
            returns nothing
        """
        # evaluate expression and add it to vars
        return self.pattern.match(self.expr.eval(vars),vars)

class Cond(IRNode):
    """ Condition class
          expr -> expression to be satisfied
    """
    def __init__(self, expr):
        self.expr = expr

    def printNode(self,s="",c=""):
        print "%s(Cond)" % (s)
        self.expr.printNode( c + "`--", c + "   " )

    def satisfied(self,vars):
        """ check if condition is satisfied
        """
        e = self.expr.eval(vars)
        if e.__class__ is not bool:
            raise IRException(
                "incorrect type of condition expression, "
                "should be boolean",
                self.sn )
        return e

class Variant(IRNode, Expr):
    """ class for variant
        power -> number, power of a variant
        expr -> Expr object describing a variant
    """
    def __init__(self, power, expr):
        self.power = power
        self.expr = expr
        assert self.power.__class__ is int

    def printNode(self,s="",c=""):
        print ( "%s(Variant: power=%d, slen=%d)"
            % (s,self.power,self.slen()) )
        self.expr.printNode( c + "`--", c + "   " )

    def eval(self,vars):
        """ simple: evaluate expr
            thinking of it: such expressions are primary targets
            for the Optimizer from the Future, which will spread
            glory and ultra speedup to generation
            (will be available as soon as it'll be done)
        """
        self.checkLen(vars)
        return self.expr.eval(vars)
        # huh, this was really simple

    def slen(self):
        """ calculate length """
        return self.expr.slen()

class LimitedRoulette(Roulette):
    """ Concrete example of roulette algorithm """
    def __init__(self,counter,choice,randint):
        self.counter = counter
        self.choice = choice
        self.randint = randint

    def roulette(self,match):
        """ choose variant """
        variants = match.variants
        # fin effect
        if self.counter.fin:
            # return any of shortest
            return self.choice(match.shortest)
        # rule power effect
        overall = sum([v.power for v in variants])
        r = self.randint(1,overall)
        for v in variants:
            if r > v.power:
                r -= v.power
            else:
                break

        # MUSTFIX: order power effect
        return v

    __call__ = roulette

# SynNode tree -> IR tree converter
class IR:
    """ Converts SynNode tree to IR tree """

    def __init__(self, syn, gen):
        self.filename = syn.filename
        self.tokens = syn.tokens
        self.lines = syn.lines
        self.builtins = gen.builtins
        self.builtinNames = gen.builtins.builtins
        self.roulette = LimitedRoulette(
            counter, gen.randomChoice, gen.randomInt
        )
        self.ruleNames = syn.rules
        self.rules = {}     # dict Id -> Rule
        self.syntree = syn.tree
        self.reservedWords = ['_'] + gen.builtins.names()

    def printGrammar(self):
        print ">>> Grammar dump:"
        for r in self.rules:
            self.rules[r].printNode()

    def evalRule(self,name,args=None,count=0):
        if args is None: args = []
        
        counter.cur = 0
        counter.count = count
        counter.fin = False
        Newline.indent = 0

        id = Id(name)
        try: r = self.rules[id]
        # catch error if there no such rule
        except KeyError, ke:
            raise IRException( "No such rule `%s'" %(name) )
        # catch runtime errors
        try: result = r(args)
        except IRException, ie:
            try: sn = ie.sn
            except AttributeError:
                raise ie
            self.reportError( ie.sn, str(ie) )
        if result.__class__ is not str:
            self.reportError( None,
                "initial rule `%s' should be evaluated to type str"
                    %str(r.name) )
        return result

    def isReservedWord(self, word):
        return word in self.reservedWords
    
    def pushMatch(self, id, match):
        # rule object created in parseGrammar()
        assert id in self.rules
        self.rules[id].addMatch(match)
    
    def reportError(self, sn, message):
        """ raise exception with message derived from data
        about current token"""
        if sn is None:
            raise IRException( "error: %s" % message )
        e = sn.token
        raise IRException( "%s:%d(%d): on token `%s': error: %s\n"
                               "%s%s\n" 
                               "%s^" %
            ( self.filename, e.nline, e.nchar, e.value, message,
              ' '*8, self.lines[e.nline-1].rstrip(),
              ' '*(8 + e.nchar-1)) )

    def internalError(self, sn, message):
        """ raise internal error exception
        possible cause: internal logic failure """
        e = sn.token
        raise IRException(
            "!!! %s:%d(%d): on token `%s': internal error: %s\n"
            "%s%s\n" 
            "%s^" %
            ( self.filename, e.nline, e.nchar, e.value, message,
              ' '*8, self.lines[e.nline-1].rstrip(),
              ' '*(8 + e.nchar-1)) )

    def parseGrammar(self):
        sn = self.syntree
        assert sn.checkId('grammar')
        # create all rule nodes (need for linking)
        for n in self.ruleNames:
            name = Id(n)
            assert name not in self.rules
            self.rules[name] = Rule(name)
        # fill up self.rules table
        for r in sn.children:
            self.parseRule(r)

    def parseIdentifier(self, sn):
        assert sn.checkId('identifier')
        id = Id(sn.token.value)
        id.setSyntaxNode(sn)
        return id

    def parseNumber(self, sn):
        assert sn.checkId('number')
        return Num(int(sn.token.value))
        
    def parseString(self, sn):
        assert sn.checkId('string')
        return Str(sn.token.value)

    def parseNewline(self, sn):
        assert sn.checkId('newline')
        # WAS: return Str('\n' + sn.token.value)
        return Newline(len(sn.token.value.lstrip("\n")))

    def parseLiteral(self, sn):
        assert sn.checkId('literal')
        node = None
        if sn.checkId('literal'):
            c0 = sn.children[0]
            if c0.checkId('number'):
                node = self.parseNumber( c0 )
            elif c0.checkId('string'):
                node = self.parseString( c0 )
            else:
                self.internalError( c0, "number or string expected" )
        return node

    def parsePattern(self, sn, vars):
        assert sn.checkId('pattern')
        """ Pattern is a list of expr """
        patlist = []      # empty list operator
        node = None
        for pl in sn.children:
            patlist.append( self.parsePatlist(pl, vars) )
        return Pattern( patlist )

    def parsePatlist(self, sn, vars):
        assert sn.checkId('patlist')
        node = None
        c0 = sn.children[0]     # operator or atom
        if c0.checkId('consop'):
            node = Cons(
              self.parsePatatom( sn.children[1], vars ),
              self.parsePatlist( sn.children[2], vars ) )
            node.setSyntaxNode(c0)
        elif c0.checkId('listop'):
            node = List()
            node.setSyntaxNode(c0)
            for atom in sn.children[1:]:
                node.addValue( self.parsePatatom( atom, vars ) )
        else:   # atom
            node = self.parsePatatom( c0, vars )
        return node

    def parsePatatom(self, sn, vars):
        assert sn.checkId('patatom')
        node = None
        c0 = sn.children[0]
        if c0.checkId('identifier'):
            node = self.parseIdentifier( c0 )
            if node in vars:
                self.reportError( c0,
                    "variable `%s' has been already defined before"
                        %str(node) )
            if not node.isAnonymous():
                vars.append(node)
        elif c0.checkId('literal'):
            node = self.parseLiteral( c0 )
        elif c0.checkId('emptylist'):
            node = List()
        elif c0.checkId('patlist'):
            node = self.parsePatlist( c0, vars )
        else:
            self.internalError( c0,
                "identifier, literal, emptylist expected")
        return node

    def parseExpression(self, sn):
        assert sn.checkId('expression')
        node = None
        c0 = sn.children[0]
        if c0.checkId('consop'):
            head = self.parseExpr( sn.children[1] )
            tail = self.parseExpression( sn.children[2] )
            node = Cons( head, tail )
            node.setSyntaxNode(c0)
        elif c0.checkId('listop'):
            node = List()
            node.setSyntaxNode(c0)
            for c in sn.children[1:]:
                node.addValue( self.parseExpr( c ) )
        elif c0.checkId('expr'):   # an expressioN
            node = self.parseExpr( c0 )
        else:
            self.internalError( "cons, list of expr expected" )
        return node
    
    def parseExpr(self,sn):
        assert sn.checkId('expr')
        atoms = []
        # parse this in reverse order
        for c in sn.children[::-1]:
            a = self.parseAtom(c)
            # check if this is a rule appliance
            if ( a.checkType(Id)
                and ( str(a) in self.ruleNames
                    or str(a) in self.builtinNames )):
                name = str(a)
                # get last atom as an argument for rule
                try: args = atoms.pop()
                except IndexError, ie:
                    if name in self.ruleNames:
                        f = self.rules[a]
                    elif name in self.builtinNames:
                        f = self.builtins.get(name)
                    atoms.append( Func(f,c) )
                    continue
#                   if without function support                    
#                    self.reportError(
#                        "no arguments provided for rule `%s'"
#                        %name )
                # if it's a List, then consider it as a list of
                # arguments, otherwise it's a single argument
                if args.checkType(List):
                    args = args.values
                else:
                    args = [args]
                # create an Apply here
                app = Apply(a,args)
                app.setSyntaxNode(c)
                atoms.append( app )

                # MOST IMPORTANTLY: link Apply
                # no one expect this to be done here
                if name in self.ruleNames:
                    app.link( self.rules[a] )
                elif name in self.builtinNames:
                    app.link( self.builtins.get(name) )
            else:
                atoms.append(a)
        if len(atoms) > 1:
            # reverse list of atoms since it is reversed
            atoms.reverse()
            node = Cat(atoms)
        else:
            node = atoms[0]
        return node           

    def parseAtom(self, sn):
        assert sn.checkId('atom')
        # TODO features: [,]-feat, [|]-feat
        node = None
        c0 = sn.children[0]
        if c0.checkId('identifier'):
            node = self.parseIdentifier( c0 )
        elif c0.checkId('literal'):
            node = self.parseLiteral( c0 )
        elif c0.checkId('emptylist'):
            node = List()
            node.setSyntaxNode(c0)
        elif c0.checkId('expression'):
            node = self.parseExpression( c0 )
        else:
            self.internalError( c0,
                "identifier, literal, emptylist expected")
        return node

    def parseRule(self, sn):
        assert sn.checkId('rule')
        node = None
        patternVars = []
        deflistVars = []
        defs = []
        conds = []
        # syntax rule means only one match,
        # one match should be read there and put into rule
        name = self.parseIdentifier( sn.children[0] )
        name.setSyntaxNode( sn.children[0] )
        if str(name) in self.reservedWords:
            self.reportError( sn,
                "could not use reserved word `%s' as a rule name"
                % str(name) )
        pattern = self.parsePattern( sn.children[1], patternVars )
        cn = 2
        c = sn.children[cn]
        if c.checkId('deflist'):
            defs = self.parseDeflist( c, patternVars )
            cn += 1
            c = sn.children[cn]
        if c.checkId('condlist'):
            conds = self.parseCondlist( c )
            cn += 1
            c = sn.children[cn]
        if c.checkId('variants'):
            variants = self.parseVariants( c )
        elif c.checkId('deflist'):
            self.reportError( c,
              "variants section expected" )
        else:
            self.internalError( c, "What was that??" )
        try: # there may be error with shortest variant
            match = Match(pattern, {}, defs, conds, variants)
        except IRException, e:
            self.reportError( c, str(e) )
        # add variables from defs to vars
        for v in patternVars:
            if str(v) in self.reservedWords:
                self.reportError( v.sn,
                    "could not use reserved word `%s' as "
                    "a variable name in a pattern" % str(v) )
            if v in self.rules:
                self.reportError( v.sn,
                  "all names in pattern definition "
                  "should be unique, "
                  "but `%s' has been already used "
                  "as a rule name" % str(v) )
        match.link(self.roulette)
        self.pushMatch(name, match)
        return IRException("do not use this result")

    def parseVariants(self, sn):
        assert sn.checkId('variants')
        node = []
        for c in sn.children:
            node.append( self.parseVariant( c ) )
        return node

    def parseVariant(self, sn):
        assert sn.checkId('variant')
        node = None
        c0 = sn.children[0]
        c1 = None
        if c0.checkId('power'):
            power = int(c0.token.value)
            c1 = sn.children[1]
        else:
            power = 1
            c1 = c0
        if c1.checkId('simplevariant'):
            expr = self.parseSimpleVariant( c1 )
        elif c1.checkId('multilinevariant'):
            expr = self.parseMultilineVariant( c1 )
        return Variant(power, expr)

    def parseSimpleVariant(self, sn):
        assert sn.checkId('simplevariant')
        return self.parseSentence( sn.children[0] )

    def parseMultilineVariant(self, sn):
        assert sn.checkId('multilinevariant')
        node = None
        if len(sn.children) == 1:
            c0 = sn.children[0]
            if c0.checkId('newline'):
                node = self.parseNewline( c0 )
            elif c0.checkId('sentence'):
                node = self.parseSentence( c0 )
        else:
            node = Cat()
            node.setSyntaxNode(sn)
            haveNewlines = False
            firstOneIsNewline = sn.children[0].checkId('newline')
            for c in sn.children:
                if c.checkId('newline'):
                    nl = self.parseNewline( c )
                    if not haveNewlines:
                        gap = nl.value
                        previous = gap
                        haveNewlines = True
                    elif nl.value < gap:
                        nl.value = gap
                    prev = previous
                    previous = nl.value
                    nl.unindent( prev )
                    if firstOneIsNewline:
                        firstOneIsNewline = False
                    else:
                        node.addValue( nl )
                elif c.checkId('sentence'):
                    node.addValue( self.parseSentence( c ) )
                else:
                    self.internalError( c,
                      "it should be either newline or sentence")
            if previous != gap:
                node.addValue( Newline(-previous+gap,"") )
        return node

    def parseSentence(self, sn):
        assert sn.checkId('sentence')
        return self.parseExpression( sn.children[0] )

    def parseDeflist(self, sn, vars):
        assert sn.checkId('deflist')
        # returns list of Def
        defs = []
        for d in sn.children:
            defs.append( self.parseDefinition( d, vars ) )
        return defs

    def parseDefinition(self, sn, vars):
        assert sn.checkId('definition')
        pattern = self.parsePatatom( sn.children[0], vars )
        expr = self.parseExpr( sn.children[1] )
        return Def(pattern, expr)

    def parseCondlist(self,sn):
        assert sn.checkId('condlist')
        conds = []
        for c in sn.children:
            cond = Cond(self.parseExpr( c )) 
            cond.setSyntaxNode(c)
            conds.append( cond )
        return conds

# exception class
class IRException(Exception):
    def __init__(self,message,sn=None):
        self._message = message
        self.sn = sn
    def __str__(self):
        return self._message

# Runtime exceptions
class UndefinedVariableException(IRException): pass
class NoMatchException(IRException): pass
class TypeException(IRException): pass
class BuiltinException(IRException): pass
class NoShortestRuleException(IRException) : pass

if __name__ == "__main__":
    import sys
    filename = sys.argv[1]
    reader = reader.Reader(filename)
    reader.parseFile()
    syn = syntax.Syn(reader)
    syn.parseGrammar()
    gen = Gen()
    ir = IR(syn,gen)
    ir.parseGrammar()
    ir.printGrammar()

