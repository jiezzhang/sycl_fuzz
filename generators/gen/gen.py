""" Generator class
shall define roulette algorithm and perform generation
"""

import random
from ir import BuiltinException
from ir import func

##
## TODO:
##   done
##

class Builtins:
    """ Builtin functions namespace """
    def __init__(self):
        self.builtins = {
            'head'      : self.head,
            'tail'      : self.tail,
            'any'       : self.any,
            'anyTypes'  : self.anyTypes,
            'join'      : self.join,
            'split'     : self.split,
            'len'       : self.length,
            'get'       : self.access,
            'in'        : self.contains,
            'uniq'      : self.unique,
            'union'     : self.union,
            'diff'      : self.diff,
            'push-back' : self.pushBack,
            'push-front': self.pushFront,
            'back'      : self.back,
            'front'     : self.front,
            'insert'    : self.insert,
            'delete'    : self.delete,
            'cat'       : self.concat,
            'set'       : self.set,
            'setarg'    : self.setarg,
            'setargs'   : self.setargs,
            'foreach'   : self.map,
            'map'       : self.map,
            'matchmap'  : self.matchmap,
            'filter'    : self.filter,
            'zip'       : self.zip,
            'sort'      : self.sort,
            'reverse'   : self.reverse,
            'range'     : self.range,
            'shuffle'   : self.shuffle,
            'str'       : self.toString,
            'num'       : self.toNumber,
            'add'       : self.add,
            'sub'       : self.sub,
            'mul'       : self.mul,
            'div'       : self.div,
            'eq'        : self.eq,
            'neq'       : self.neq,
            'gt'        : self.greaterThan,
            'lt'        : self.lessThan,
            'ge'        : self.greaterOrEqual,
            'le'        : self.lessOrEqual,
            'and'       : self.logicalAnd,
            'or'        : self.logicalOr,
            'not'       : self.logicalNot,
            'is-list'   : self.isList,
            'is-int'    : self.isInt,
            'is-str'    : self.isStr,
            'is-bool'   : self.isBool,
            'is-prefix' : self.isPrefix,
            'is-suffix' : self.isSuffix,
            'true'      : self.true,
            'false'     : self.false,
            'randint'   : self.randint
        }

    def get(self,name):
        return self.builtins[name]

    def names(self):
        return self.builtins.keys()

    def runtimeError(self,message):
        raise BuiltinException(
            "runtime error: %s" % message )

    def check(self,name,args,n=-1,types=None):
        """ check function arity and arguments' types """
        if n < 0:
            if n == -1: return
            else: self.runtimeError(
                    "internal error: incorrect negative arity." )
        else:
            if len(args) != n:
                self.runtimeError(
                    "Incorrect arity `%d' for `%s' builtin (expected %d)"
                        %(len(args),name,n))

        if types is not None:
            assert len(types) == n
            for (a,t,i) in zip(args,types,range(1,n+1)):
                if t.__class__ is list:
                    if a.__class__ not in t:
                        self.runtimeError(
                            "Incorrect type `%s' for %d argument of `%s' "
                            "builtin (expected one of %s)"
                                %( a.__class__.__name__,
                                i, name, [tt.__name__ for tt in t] ))

                elif t is not None and a.__class__ is not t:
                    self.runtimeError(
                        "Incorrect type `%s' for %d argument of `%s' "
                        "builtin (expected %s)"
                            %( a.__class__.__name__,
                            i, name, t.__name__ ))
                            
    def checkListOfSameType(self,name,args,n,type):
        """ check all arguments to be of the same type """
        if len(args) < n:
            self.runtimeError(
                "Incorrect arity `%d' for `%s' builtin (expected at least %d)"
                    %(len(args),name,n))
            
        for (a,i) in zip(args,range(1,len(args)+1)):
            if a.__class__ is not type:
                self.runtimeError(
                    "Incorrect type `%s' for %d argument of `%s' "
                    "builtin (expected %s)"
                        %( a.__class__.__name__,
                        i, name, type.__name__ ))

    # builtins definition
    def head(self,args):
        """ returns first element of a list:
            head(x:list) = x
            head(()) = error
        """
        # read: one argument of list type
        self.check(self.head.func_name,args,1,[list])
        arg = args[0]
        if not len(arg):
            self.runtimeError("`head' called for an emply list")
        return arg[0]
        
    def tail(self,args):
        """ returns tail of a list:
            tail(x:xs) = xs
            tail(()) = ()
        """
        self.check(self.tail.func_name,args,1,[list])
        arg = args[0]
        return arg[1:]
        
    def any(self,args):
        """ return any element of a list """
        self.check(self.any.func_name,args,1,[list])
        try: return random.choice(args[0])
        except IndexError, ie:
            self.runtimeError(
                "any called upon an empty list" )

    def anyTypes(self, args):
        """ return any element of a list """
        self.checkListOfSameType(self.anyTypes.func_name,args,2,list)
        try: 
            ctx_vars = args[0]
            permit_vars = []
            types = args[1]
            for v in ctx_vars:
                if v[1] in types:
                    permit_vars.append(v)
            if len(permit_vars) == 0:
                self.runtimeError("No permitted variable is passed in")
            var = random.choice(permit_vars)
            return var
        except IndexError, ie:
            self.runtimeError(
                "any called upon an empty list" )

    def join(self,args):
        """ join values of a list of atoms to single atom
            with a specified delimeter:
            join(atom,list)
            join(str,list)
            join("a",("1","2","3")) = 1a2a3
        """
        self.check(self.join.func_name,args,2,[str,list])
        a, l = args[0], args[1]
        # verify that args is a list of atoms
        for e in l:
            if e.__class__ is not str:
                self.runtimeError(
                    "second argument of join builtin should be list "
                    "of atoms: got `%s'" % str(l) )
        return a.join(l)
        
    def split(self,args):
        """ split atom to list of atoms by delimiter
            split(s,d)
            split("x-x-x","-") = ("x","x","x")
        """
        self.check(self.split.func_name,args,2,[str,str])
        s, d = args[0], args[1]
        return s.split(d)
    
    def length(self,args):
        """ returns length of a list:
            len((1,2,3),)
        """
        self.check(self.length.func_name,args,1,[list])
        l = args[0]
        return len(l)
    
    def access(self,args):
        """ returns n-th element:
            get((1,2,3),1) = 2
        """
        self.check(self.access.func_name,args,2,[list,int])
        l, i = args[0], args[1]
        try:
            return args[0][args[1]]
        except IndexError, ie:
            self.runtimeError( "list index out of range" )

    def contains(self,args):
        """ returns True if elements contained in list
            in('x', l)
        """
        self.check(self.contains.func_name,args,2,[None,list])
        return args[0] in args[1]

    def unique(self,args):
        """ remove duplicates from a list with preserving of order
            uniq(("a","b","c"),) = ("a","b","c")
            uniq(("a","a","c"),) = ("a","c")
        """
        self.check(self.unique.func_name,args,1,[list])
        l1 = args[0]
        # create set of elements
        l = []
        for e in l1:
            if e not in l:
                l.append(e)
        return l

    def union(self,args):
        """ merge two lists with removing of duplicates
            union(list,...,list)
            union(("1"),("1","2")) = ("1","2")
        """
        #self.check(self.union.func_name,args,,[list,list])
        self.checkListOfSameType(self.union.func_name,args,2,list)
        l = []; ls = []
        for l1 in args: ls.extend(l1)
        for e in ls:
            if e not in l:
                l.append(e)
        return l

    def map(self,args):
        """ apply rule from first argument to all
            elements in a list
        """
        self.check(self.map.func_name,args,2,[func,list])
        f, l = args[0], args[1]
        assert f.__class__ is func
        return [ f([e]) for e in l ] 

    def matchmap(self,args):
        """ apply rule from first argument to all
            elements in a list
        """
        self.check(self.matchmap.func_name,args,2,[func,list])
        f, l = args[0], args[1]
        return [ f(e) for e in l ] 

    def filter(self,args):
        """ filter elements of a list with boolean function
        """
        self.check(self.filter.func_name,args,2,[func,list])
        f, l = args
        result = []
        for e in l:
            value = f([e])
            if value.__class__ is not bool:
                self.runtimeError(
                    "filtering function should return only bool values" )
            if value:
                result.append( value )
        return result

    def zip(self,args):
        """ zip(seq1 [, seq2 [...]]) -> ((seq1[0], seq2[0] ...), (...))
        """
        self.checkListOfSameType(self.zip.func_name,args,2,list)
        return zip( *args )

    def concat(self,args):
        """ concatenate two lists
            cat(list,...,list)
            cat(("1"),("1","2")) = ("1","1","2")
        """
        self.checkListOfSameType(self.concat.func_name,args,2,list)
        l = []
        for e in args:
            l.extend( e )
        return l

    def set(self,args):
        """ generate a set using generator function
            let g yields 1, 1, 2, 2, 3, 3, 4, ...
            set(g, 4) = [1, 2, 3, 4]
        """
        self.check(self.set.func_name,args,2,[func,int])
        powerLevel = 9001
        g, n = args
        l = []
        while len(l) < n and powerLevel > 0:
            # Decrease power level: when it became 0 process will be
            # forcefully stopped and exception raised.
            powerLevel -= 1
            try:
                e = g([])
            except TypeError, te: 
                self.runtimeError(
                    "generator function shan't require arguments" )
            # If the elements already contained in l, continue.
            if e in l:
                continue
            l.append( e )
        
        if powerLevel == 0:
            self.runtimeError(
                "generation was unsuccessfully performed over 9000 times, "
                "it is suggested to be grammar mistake; otherwise tell "
                "author of the program to add more flexible constraint" )

        return l

    def setarg(self,args):
        """ generate a set using generator function
            let g(1) yields 1, 1, 2, 2, 3, 3, 4, ...
            setarg(g, 4, 1) = [1, 2, 3, 4]
        """
        self.check(self.setarg.func_name,args,3,[func,int,None])
        powerLevel = 9001
        g, n, a = args
        l = []
        while len(l) < n and powerLevel > 0:
            # Decrease power level: when it became 0 process will be
            # forcefully stopped and exception raised.
            powerLevel -= 1
            try:
                e = g([a])
            except TypeError, te: 
                self.runtimeError(
                    "incorrect arguments given to generator function, "
                    "check it out" )
            # If the elements already contained in l, continue.
            if e in l:
                continue
            l.append( e )
        
        if powerLevel == 0:
            self.runtimeError(
                "generation was unsuccessfully performed over 9000 times, "
                "it is suggested to be grammar mistake; otherwise tell "
                "author of the program to add more flexible constraint" )

        return l

    def setargs(self,args):
        """ generate a set using generator function
            let g(x) yields x
            set(g, 4, [1, 2, 3, 4]) = [1, 2, 3, 4]
        """
        self.check(self.setargs.func_name,args,3,[func,int,list])
        powerLevel = 9001
        g, n, arguments = args
        l = []

        # if empty set is good enough return it.
        if n == 0:
            return l

        if len(arguments) != n:
            self.runtimeError(
                "number of arguments in third argument shall be "
                "equal to number of elements in set being requested" )

        argumentsIndex = 0
        while len(l) < n and powerLevel > 0:
            # Decrease power level: when it became 0 process will be
            # forcefully stopped and exception raised.
            powerLevel -= 1
            try:
                e = g([arguments[argumentsIndex]])
            except TypeError, te: 
                self.runtimeError(
                    "generator function shan't require arguments" )
            # If the elements already contained in l, continue.
            if e in l:
                continue

            l.append( e )
            argumentsIndex += 1
        
        if powerLevel == 0:
            self.runtimeError(
                "generation was unsuccessfully performed over 9000 times, "
                "it is suggested to be grammar mistake; otherwise tell "
                "author of the program to add more flexible constraint" )

        return l

    def pushBack(self,args):
        """ add one element to end of list
        """
        self.check(self.pushBack.func_name,args,2,[list,None])
        return args[0] + [args[1]]

    def pushFront(self,args):
        """ add one element to begin of list
        """
        self.check(self.pushFront.func_name,args,2,[list,None])
        return [args[1]] + args[0]

    def back(self,args):
        """ return last element of a list
        """
        self.check(self.back.func_name,args,1,[list])
        if not len(arg):
            self.runtimeError("`back' called for an emply list")
        return args[0][-1]

    def front(self,args):
        """ return first element of a list
        """
        self.check(self.front.func_name,args,1,[list])
        if not len(args):
            self.runtimeError("`front' called for an emply list")
        return args[0][0]

    def insert(self,args):
        """ insert an element before i-th
        """
        self.check(self.insert.func_name,args,3,[list,int,None])
        l, i, x = args[0][:], args[1], args[2]
        try:
            l.insert(args[1], args[2])
        except IndexError, ie:
            self.runtimeError( "list index out of range" )
        return l

    def delete(self,args):
        """ insert an element before i-th
        """
        self.check(self.insert.func_name,args,2,[list,int])
        l, i = args[0][:], args[1]
        try:
            l.pop(args[1])
        except IndexError, ie:
            self.runtimeError( "list index out of range" )
        return l

    def diff(self,args):
        """ returns difference between first and other lists:
            diff((1,2,3,4),(2,3)) = (1,4)
            diff(x,y,z) = (x\y)\z
        """
        self.checkListOfSameType(self.diff.func_name,args,2,list)
        l = []; ls = []
        for l1 in args[1:]: ls.extend(l1)
        for e in args[0]:
            if e not in ls:
                l.append(e)
        return l
    
    def sort(self,args):
        """ sort elements of a list:
            sort((3,2,1,4),) = (1,2,3,4)
        """
        self.check(self.sort.func_name,args,1,[list])
        l = args[0][:]
        l.sort()
        return l

    def reverse(self,args):
        """ reverse elements of a list:
            reverse((1,2,3,4),) = (4,3,2,1)
        """
        self.check(self.reverse.func_name,args,1,[list])
        l = args[0][:]
        l.reverse()
        return l

    def range(self,args):
        """ range elements of a list:
            range(1,3) = (1,2)
        """
        self.checkListOfSameType(self.range.func_name,args,2,int)
        if len(args) > 3:
            self.runtimeError( 'there could be 2 or 3 arguments' )
        if len(args) == 2:
            return range(args[0], args[1])
        return range(args[0], args[1], args[2])

    def shuffle(self,args):
        """ shuffle elements of a list:
            shuffle((1,2,3,4),) = (4,3,2,1)
        """
        self.check(self.shuffle.func_name,args,1,[list])
        l = args[0][:]
        random.shuffle(l)
        return l
        
    def toString(self,args):
        """ convert number to string:
            str(1) = "1"
        """
        self.check(self.toString.func_name,args,1,[int])
        return str(args[0])
    
    def toNumber(self,args):
        """ convert string to number:
            num("123") = 123
        """
        self.check(self.toNumber.func_name,args,1,[str])
        try:
            x = int(args[0])
        except ValueError, ve:
            self.runtimeError(
                "unable to convert `%s' to number" % str(ve) )
        return x
        
    # arithmetics
    def add(self,args):
        """ arithmetic plus operator:
            add(1,2) = 3
        """
        self.check(self.add.func_name,args,2,[int,int])
        return args[0] + args[1]
        
    def sub(self,args):
        """ substract:
            sub(3,1) = 2
        """
        self.check(self.sub.func_name,args,2,[int,int])
        return args[0] - args[1]
        
    def mul(self,args):
        """ multiply:
            mul(2,2) = 4
        """
        self.check(self.mul.func_name,args,2,[int,int])
        return args[0]*args[1]
        
    def div(self,args):
        """ divide:
            div(3,2) = 1
        """
        self.check(self.div.func_name,args,2,[int,int])
        return args[0]//args[1]
    
    # relations
    def eq(self,args):  
        """ ==:
        """
        self.check(self.eq.func_name,args,2,[None,None])
        return args[0] == args[1]

    def neq(self,args):  
        """ !=:
        """
        self.check(self.neq.func_name,args,2,[None,None])
        return args[0] != args[1]

    def greaterThan(self,args):  
        """ >:
        """
        self.check(self.greaterThan.func_name,args,2,[int,int])
        return args[0] > args[1]

    def greaterOrEqual(self,args):  
        """ >=:
        """
        self.check(self.greaterOrEqual.func_name,args,2,[int,int])
        return args[0] >= args[1]

    def lessThan(self,args):  
        """ <:
        """
        self.check(self.lessThan.func_name,args,2,[int,int])
        return args[0] < args[1]

    def lessOrEqual(self,args):  
        """ <=:
        """
        self.check(self.lessOrEqual.func_name,args,2,[int,int])
        return args[0] <= args[1]

    # logical operators
    def logicalAnd(self,args):
        """ logical AND
        """
        self.check(self.logicalAnd.func_name,args,2,[bool,bool])
        return args[0] and args[1]

    def logicalOr(self,args):
        """ logical OR
        """
        self.check(self.logicalOr.func_name,args,2,[bool,bool])
        return args[0] or args[1]

    def logicalNot(self,args):
        """ logical NOT """
        self.check(self.logicalNot.func_name,args,1,[bool])
        return not args[0]

    # predicates
    def isList(self,args):
        """ returns True if argument is a list:
            is-list(l)
        """
        self.check(self.isList.func_name,args,1,None)
        return args[0].__class__ is list

    def isInt(self,args):
        """ returns True if argument is a int:
            is-list(l)
        """
        self.check(self.isInt.func_name,args,1,None)
        return args[0].__class__ is int

    def isStr(self,args):
        """ returns True if argument is a int:
            is-list(l)
        """
        self.check(self.isStr.func_name,args,1,None)
        return args[0].__class__ is str

    def isBool(self,args):
        """ returns True if argument is a int:
            is-list(l)
        """
        self.check(self.isStr.func_name,args,1,None)
        return args[0].__class__ is bool

    def isPrefix(self,args):
        """ returns True if fisrt argument is a prefix for second:
            is-prefix(a,s)
        """
        self.check(self.isPrefix.func_name,args,2,[str,str])
        return args[0].startswith(args[1])

    def isSuffix(self,args):
        """ returns True if fisrt argument is a prefix for second:
            is-suffix(a,s)
        """
        self.check(self.isSuffix.func_name,args,2,[str,str])
        return args[0].endswith(args[1])

    def true(self,args):
        """ true() = true
        """
        self.check(self.true.func_name,args,0,[])
        return True

    def false(self,args):
        """ false() = false
        """
        self.check(self.false.func_name,args,0,[])
        return False

    # random functions
    def randint(self,args):
        """ returns random integer from x...y range:
            randint(x,y)
        """
        self.check(self.randint.func_name,args,2,[int,int])
        return random.randint(args[0],args[1])

    # symbol table


class Gen:
    """ Generator class """

    def __init__(self):
        self.builtins = Builtins()
        self.randomChoice = random.choice
        self.randomInt = random.randint

