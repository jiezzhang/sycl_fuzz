""" This module kindly translate the syntax of grammar files 
    to syntax tree
"""

import reader

#
class SynNode:
    """ node of a syntax tree """

    nodeIds = [
        'grammar',
        'identifier',
        'number',
        'string',
        'newline',
        'literal',
        'pattern',
        'patlist',
        'patatom',
        'consop',       # `:' in patterns
        'listop',       # `,' in patterns
        'listset',
        'listsetmin',
        'listsetmax',
        'emptylist',
        'expression',
        'exprlist',
        'expr',
        'atom',
        'rule',
        'variants',
        'variant',
        'power',
        'variant',
        'simplevariant',
        'multilinevariant',
        'sentence',
        'deflist',
        'definition',
        'condlist' ]
    
    def __init__(self, id, token):
        self.id = id            # identifier from nodeIds
        self.token = token      # reference to a Token object
        self.children = []      # list of children nodes
        self.match = token.value
        assert id in SynNode.nodeIds

    def addChild(self, child):
        """ add child to node, order is important """
        self.children.append(child)
        # debug purposes
        if len(self.children) == 1:
            self.match = child.match
        else:
            self.match += " " + child.match

    def checkId(self,id):
        """ check id of a node """
        assert id in SynNode.nodeIds
        return self.id == id

    def getChild(self,i = 0):
        """ get a child by an index """
        return self.children[i]

    def printNode(self, s = "", c = ""):
        print "%s( %s | %s )" % (s, self.match, self.id)
        if len(self.children):
            for child in self.children[:-1]:
                child.printNode( c + "|--", c + "|  " )
            self.children[-1].printNode( c + "`--", c + "   ")
#
class Syn:
    """ syntax analyzer, constructed from list of tokens """
    # for all operators prefix form is used
    
    def __init__(self, reader):
        self.filename = reader.filename
        self.tokens = reader.tokens
        self.lines = reader.lines
        self.rules = {}     # dictionary of all rules, should be filled
        self.ncur = 0       # index of the very first token
        self.cur = self.tokens[self.ncur]
        self.tree = None

    def nextToken(self):
        """ change state to next token """
        self.ncur += 1
        assert self.ncur < len(self.tokens)
        self.cur = self.tokens[self.ncur]
    
    def reportError(self, message):
        """ raise exception with message derived from data
        about current token"""
        e = self.cur
        raise SyntaxException( "%s:%d(%d): on token `%s' error: %s\n"
                               "%s%s\n" 
                               "%s^" %
            ( self.filename, e.nline, e.nchar, e.value, message,
              ' '*8, self.lines[e.nline-1].rstrip(),
              ' '*(8 + e.nchar-1)) )

    def newNode(self, id):
        return SynNode(id, self.cur)
    
    def checkTokenId(self, id):
        return self.cur.checkId(id)

    def checkTokenIdsOr(self, *ids):
        for id in ids:
            if self.checkTokenId(id):
                return True
        return False

    def checkTokenValue(self, value):
        return self.cur.checkValue(value)

    def checkTokenIdValue(self, id, value):
        return self.cur.checkId(id) and self.cur.checkValue(value)
    
    # debug print -- prints whole tree
    def printGrammar(self):
        self.tree.printNode()

    # parse* functions are all return trees
    def parseGrammar(self):
        node = self.newNode('grammar')
        self.tree = node
        # skip leading newlines
        self.skipNewlines()
        while not self.checkTokenId('endoffile'):
            node.addChild( self.parseRule() )

    def parseIdentifier(self):
        if not self.checkTokenId('identifier'):
            self.reportError("identifier expected")
        node = self.newNode('identifier')
        self.nextToken()
        return node

    def parseNumber(self):
        if not self.checkTokenId('number'):
            self.reportError("number expected")
        node = self.newNode('number')
        self.nextToken()
        return node

    def parseString(self):
        if not self.checkTokenId('string'):
            self.reportError("string expected")
        node = self.newNode('string')
        self.nextToken()
        return node

    def parseNewline(self):
        if not self.checkTokenId('newline'):
            self.reportError("newline expected")
        node = self.newNode('newline')
        self.nextToken()
        return node

    def skipNewlines(self):
        while self.checkTokenId("newline"):
            self.nextToken()

    def parseLiteral(self):
        node = self.newNode('literal')
        if self.checkTokenId('string'):
            node.addChild( self.parseString() )
        elif self.checkTokenId('number'):
            node.addChild( self.parseNumber() )
        else:
            self.reportError("string or number expected")
        return node

    def parsePattern(self):
        node = self.newNode('pattern')
        while self.checkTokenIdsOr(
          'identifier', 'string', 'number', '('):
            node.addChild( self.parsePatlist() )
        return node
        
    def parsePatlist(self):
        # form nodes in prefix form:
        #   `:' case: [ consop patatom patlist ]
        #   `,' case: [ listop patatom ... patatom ]
        node = self.newNode('patlist')
        a1 = self.parsePatatom()
        if self.checkTokenId(':'):
            node.addChild( self.newNode('consop') )
            self.nextToken()
            node.addChild( a1 )
            node.addChild( self.parsePatlist() )
        elif self.checkTokenId(','):
            node.addChild( self.newNode('listop') )
            node.addChild( a1 )
            while self.checkTokenId(','):
                self.nextToken()
                if self.checkTokenIdsOr(
                  'identifier', 'string', 'number', '('):
                    node.addChild( self.parsePatatom() )
        else:
            node.addChild( a1 )
        return node

    def parsePatatom(self):
        node = self.newNode('patatom')
        if self.checkTokenId('identifier'):
            node.addChild( self.parseIdentifier() )
        elif self.checkTokenIdsOr('string', 'number'):
            node.addChild( self.parseLiteral() )
        elif self.checkTokenId('('):
            self.nextToken()
            if self.checkTokenId(')'):  # empty list
                node.addChild( self.newNode('emptylist') )
            else:   # pattern in parentheses
                node.addChild( self.parsePatlist() )
                if not self.checkTokenId(')'):
                    self.reportError( "`)' expected" )
            # anyway we already checked one token `)'
            self.nextToken()
        else:
            self.reportError(
                "indentifier, literal or `(' expected" )
        return node

    def parseExpression(self):
        # form prefix form of expression
        node = self.newNode('expression')
        e1 = self.parseExpr()
        if self.checkTokenId(','):
            # list operator
            node.addChild( self.newNode('listop') )
            node.addChild( e1 )
            while self.checkTokenId(','):
                self.nextToken()
                if self.checkTokenIdsOr(
                  'identifier', 'number', 'string', '(', '[' ):
                    node.addChild( self.parseExpr() )
        elif self.checkTokenId(':'):
            # cons operator
            node.addChild( self.newNode('consop') )
            node.addChild( e1 )
            self.nextToken()
            node.addChild( self.parseExpression() )
        else:
            node.addChild( e1 )
        return node

    def parseExpr(self):
        node = self.newNode('expr')
        if self.checkTokenIdsOr(
          'identifier', 'number', 'string', '(', '['):
            node.addChild( self.parseAtom() )
        else:
            self.reportError(
              "identifier, number, string, `(' or `[' expected")
        while self.checkTokenIdsOr(
          'identifier', 'number', 'string', '(', '['):
            node.addChild( self.parseAtom() )
        return node

    def parseAtom(self):
        node = self.newNode('atom')
        if self.checkTokenId('identifier'):
            node.addChild( self.parseIdentifier() )
        elif self.checkTokenIdsOr('number', 'string'):
            node.addChild( self.parseLiteral() )
        elif self.checkTokenId('('):
            self.nextToken()
            if self.checkTokenId(')'):
                node.addChild( self.newNode('emptylist') )
            else:
                node.addChild( self.parseExpression() )
                if not self.checkTokenId(')'):
                    self.reportError("`)' expected")
            # skip `)'
            self.nextToken()
        elif self.checkTokenId('['):
            self.reportError(
              "please, use parentheses instead of brackets. "
              "Brackets have no actual mean now and disabled." )
        else:
            self.reportError(
              "identifier, string, number, `(' or `[' expected")
        return node

    def parseRule(self):
        node = self.newNode('rule')
        node.addChild( self.parseIdentifier() )
        node.addChild( self.parsePattern() )
        
        self.skipNewlines()
        if self.checkTokenId('@'):
            self.nextToken()
            node.addChild( self.parseDeflist() )
        self.skipNewlines()
        if self.checkTokenId('?'):
            self.nextToken()
            node.addChild( self.parseCondlist() )
        self.skipNewlines()
        if self.checkTokenId('::='):
            self.nextToken()
            self.skipNewlines()
            node.addChild( self.parseVariants() )
        else:
            self.reportError("`::=' expected")
        # record this rule to the rules dictionary
        name = node.children[0].token.value
        if not self.rules.has_key(name):
            self.rules[name] = node
        return node

    def parseVariants(self):
        node = self.newNode('variants')
        while self.checkTokenId('newline'):
            self.nextToken()
        node.addChild( self.parseVariant() )
        while self.checkTokenIdsOr('newline', '|'):
            self.skipNewlines()
            if self.checkTokenId('|'):
                self.nextToken()
                self.skipNewlines()
                node.addChild( self.parseVariant() )
        return node

    def parseVariant(self):
        node = self.newNode('variant')
        # if power is given add power node with value
        if self.checkTokenId('*'):
            self.nextToken()
            if self.checkTokenId('number'):
                node.addChild( self.newNode('power') )
                self.nextToken()
            else:
                self.reportError('number expected')
        if self.checkTokenId('{'):
            node.addChild( self.parseMultilineVariant() )
        else:
            node.addChild( self.parseSimpleVariant() )
        return node

    def parseSimpleVariant(self):
        node = self.newNode('simplevariant')
        node.addChild( self.parseSentence() )
        return node

    def parseMultilineVariant(self):
        node = self.newNode('multilinevariant')
        if self.checkTokenId('{'):
            self.nextToken()
            while self.checkTokenIdsOr(
              'identifier', 'string', 'number',
              '(', 'newline' ):
                if self.checkTokenId('newline'):
                    node.addChild( self.newNode('newline') )
                    self.nextToken()
                else:
                    node.addChild( self.parseSentence() )
            if self.checkTokenId('}'):
                self.nextToken()
            else:
                self.reportError("`}' expected")
        else:
            self.reportError("`{' expected")
        return node

    def parseSentence(self):
        node = self.newNode('sentence')
        node.addChild( self.parseExpression() )
        return node

    def parseDeflist(self):
        node = self.newNode('deflist')
        self.skipNewlines()
        node.addChild( self.parseDefinition() )
        while self.checkTokenId(','):
            self.nextToken()
            self.skipNewlines()
            node.addChild( self.parseDefinition() )
        return node

    def parseDefinition(self):
        node = self.newNode('definition')
        node.addChild( self.parsePatatom() )
        if self.checkTokenId('='):
            self.nextToken()
            node.addChild( self.parseExpr() )
        else:
            self.reportError("`=' expected in definition")
        return node

    def parseCondlist(self):
        node = self.newNode('condlist')
        node.addChild( self.parseExpr() )
        if self.checkTokenId(','):
            self.nextToken()
            self.skipNewlines()
            node.addChild( self.parseExpr() )
        return node
#
class SyntaxException(Exception):
    def __init__(self,message):
        self.message = message
    def __str__(self):
        return self.message

# testmain
import sys
if __name__ == "__main__":
    filename = sys.argv[1]
    reader = reader.Reader(sys.argv[1])
    reader.parseFile()
    syn = Syn(reader)
    syn.parseGrammar()
    syn.printGrammar()

