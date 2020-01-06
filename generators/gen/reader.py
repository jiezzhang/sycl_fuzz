"""Grammar syntax lexis parser
"""

import re

class Token:
    """ Class for syntax token """

    tokenIds = [
        'identifier',   # word
        'number',       # usual number
        'string',       # "x\"xx" 'x\'xx' `x\'xx`
        '(', ')',
        '[', ']',
        '{', '}',
        ',',            # ,
        ':',            # :
        '|',            # |
        '@',            # where or @
        '=',            # =
        '::=',          # ::=
        '*',            # *
        '?',            # ?
        '%',            # %
        '$',            # $
        '$(',           # $(
        '`',            # `
        '^',            # ^
        'newline',
        'endoffile' ]

    tokenPats = {
        'identifier'    : r'(?P<value>[-+_a-zA-Z][-+_a-zA-Z0-9]*)',
        'number'        : r'(?P<value>[0-9]+)',
        'string'        : r'"(?P<value>(?:[^"\\]|\\.)*)"',
        '$('            : r'\$\(',
        '`'             : r'`',
        '('             : r'\(',
        ')'             : r'\)',
        '['             : r'\[',
        ']'             : r'\]',
        '{'             : r'{',
        '}'             : r'}',
        ','             : r',',
        ':'             : r':',
        '|'             : r'\|',
        '@'             : r'@',
        '?'             : r'\?',
        '='             : r'=',
        '::='           : r'::=',
        '*'             : r'\*',
        '%'             : r'%',
        '$'             : r'\$',
        '^'             : r'\^',
        'newline'       : r'\n(P<value>\s*)',
        'comment'       : r'#'
    }
    
    tokenRes = {}
    for pat in tokenPats.keys():
        tokenRes[pat] = re.compile(tokenPats[pat])
    
    def __init__(self, id, nline, nchar, value = 'dontcare'):
        self.value = value  # token string
        self.nline = nline+1  # number of line with token
        self.nchar = nchar+1  # number if char with token
        self.id = id    # token id

        if id not in Token.tokenIds: raise ReaderException(
            "Wrong token id `%s' given" % id )

    def checkId(self, id):
        if id not in Token.tokenIds: raise ReaderException(
            "Unrecognized token id `%s' given" % id)
        return self.id == id

    def checkValue(self, value):
        return self.value == value
    
    def __str__(self):
        return ( '("%s" at (%d:%d) of type `%s\')' %
            (self.value, self.nline, self.nchar, self.id))

    def __repr__(self):
        return str(self)

# class Reader
# reads file and convert it to list of tokens
class Reader:
    """ Class for lexical analyzer """
    def __init__(self, filename):
        self.filename = filename
        self.lines = []     # list of all lines in file
        self.tokens = []    # list of all tokens
        self.nline = 0
        self.nchar = 0
        self.cur = ""
        self.indent = ""

    class EndOfFile: pass

    def parseFile(self):
        """ open file, read and split it into different tokens """
        assert len(self.tokens) == 0
        assert len(self.lines) == 0
        assert self.nline == 0
        file = open(self.filename, 'rt')
        # assume file is not that large
        self.lines = file.readlines()
        if len(self.lines) == 0:
            raise (
                "empty file `%s' given, this will be inevitable error "
                "in generation phase" % self.filename )

        self.cur = self.lines[0]
        file.close()

        try:
            while self.nline < len(self.lines):
                self.tokens.append( self.getToken() )
        except self.EndOfFile:
            # push last token -- endoffile
            self.tokens.append(
                Token( 'endoffile', self.nline, self.nchar, '' ) )
            # add empty line accordingly
            self.lines.append("") 

    def cleanLine(self,line):
        """ removes comments and returns tuple
        ( "leading spaces", "other text" ) """
        nspaces = 0
        for sp in line:
            if sp == " " or sp == "\t": nspaces += 1
            else: break
        return ( line[:nspaces], line[nspaces:] )

    def nextLine(self):
        self.nline += 1
        if self.nline >= len(self.lines):
#            spaces, text = "", ""
            raise self.EndOfFile()
        else:
            spaces, text = self.cleanLine(self.lines[self.nline])
        self.nchar = len(spaces)
        self.cur = text.rstrip()
        self.indent = spaces
    
    def matchToken(self,type):
        m = Token.tokenRes[type].match(self.cur)
        # remove match from text, increase nchar
        if m:
            mlen = m.end()
            self.cur = self.cur[mlen:]
            self.nchar += mlen
        return m

    def getToken(self):
        """ return next token """
        # accurately handle leading spaces
        spaces, self.cur = self.cleanLine(self.cur)
        self.nchar += len(spaces)
        nline, nchar = self.nline, self.nchar
        # start determining cycle
        for type in [ 'identifier', 'number' ]:
            m = self.matchToken(type)
            if m: return Token( type, nline, nchar, m.group('value') )
        
        # string
        m = self.matchToken( 'string' )
        if m:
            # replace special symbols
            s = ( m.group('value')
                .replace(r'\"', '"')
                .replace(r'\\', "\\")
                .replace(r'\n', "\n") )
            return Token( 'string', nline, nchar, s )
        
        # speed up process, note that order is important
        for type in [ '(', ')', '[', ']', '{', '}', ',',
                      '::=', '=', '*',
                      '@', '|', ':', '?' ]:
            m = self.matchToken( type )
            if m: return Token( type, nline, nchar, m.group() )
        
        # all what have remained -- newline or wrong sequence
        m = self.matchToken( 'comment' )
        if m or self.cur in ["","\n","\r\n"]:
            self.nextLine()
            return Token('newline', nline, nchar, self.indent )
        # report error
        self.reportError( 'unexpected token' )

    def reportError(self, message):
        raise ReaderException( '%s:%d(%d): error: %s\n'
                               '%s%s\n'
                               '%s^\n' %
                (self.filename, self.nline+1, self.nchar+1, message,
                 ' '*8, self.lines[self.nline].rstrip(),
                 ' '*(8+self.nchar)))
            

# class ReaderException
class ReaderException(Exception):
    def __init__(self,message):
        self.message = message
    def __str__(self):
        return self.message

if __name__ == "__main__":
    import sys
    reader = Reader(sys.argv[1])
    reader.parseFile()
    for token in reader.tokens:
        print token

