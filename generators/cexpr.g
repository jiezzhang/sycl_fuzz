# Runnable expression-oriented grammar intened to test first level pointers.

# Test area.
S ::= program() # join(", ", global-identifiers(4))

# Parameters.
statement-list-size ::= randint(1,16)
variables-list-size ::= *4 1 | *3 2 | *2 3 | *1 4
arrays-list-size ::= randint(0,4)
maximum-folding-level ::= 4
maximum-struct-size ::= 4
function-v-size ::= randint(0,4)
function-p-size ::= *4 0 | *2 1 | *1 2
array-size ::= randint(2,11)

# This is the program generation rule. This one shall be called for generation.
program
@
    functions = function-set( function-identifiers(randint(0,8)) ),

    structs = struct-type-set( struct-type-identifiers(4) ),
    sglobals = struct-set( global-struct-identifiers(variables-list-size()), structs ),
    slocals = struct-set( local-struct-identifiers(variables-list-size()), structs ),

    aglobals = array-set( global-array-identifiers(arrays-list-size()) ),
    alocals = array-set( local-array-identifiers(arrays-list-size()) ),

    vglobals = scalar-set( global-identifiers(variables-list-size()) ),             # global variables
    gscalars = cat( flatten(map(values-of, sglobals)), flatten(map(values-of, aglobals)), vglobals ),

    pglobals = pointer-set( global-pointer-identifiers(variables-list-size()), gscalars ), # global pointers
    globals = (vglobals, sglobals, aglobals, pglobals),                                    # global variables & pointers

    vlocals = scalar-set( local-identifiers(variables-list-size()) ),               # local variables
    lscalars = cat( flatten(map(values-of, slocals)), flatten( map(values-of, alocals)), vlocals ),
    plocals = pointer-set( local-pointer-identifiers(variables-list-size()), lscalars ),  # local pointers
    locals = (vlocals, slocals, alocals, plocals),                                        # local variables & pointers

    folding = maximum-folding-level(),                                              # folding level

    locals+globals = cat( vlocals, plocals, slocals, alocals, vglobals, pglobals, sglobals, aglobals ),

    environment = +environment(),
    context = +context( locals+globals, locals+globals, structs, functions, environment, folding ),

    globals+ = cat(vglobals, sglobals, aglobals, pglobals),
    functions-context = +context( globals+, globals+, structs, functions, environment, folding )

::= {
    "#include <stdio.h>"
    "/* */"
    function-declaration-list( functions )
    "/* struct declarations */"
    struct-declaration-list( structs )
    "/* struct initializers */"
    struct-init-list( sglobals, () )
    "/* arrays declaration */"
    array-init-list( aglobals, () )
    "/* global scalar variables */"
    scalar-init-list( vglobals, () )
    "/* global pointers */"
    pointer-init-list( pglobals )
    "int main()"
    "{"
        scalar-init-list( vlocals, cat(vglobals, pglobals, sglobals) )
        struct-init-list( slocals, cat(vglobals, pglobals, sglobals, vlocals) )
        array-init-list( alocals, cat(vglobals, pglobals, sglobals, vlocals, slocals ) )
        pointer-init-list( plocals )

        statement-list( 10, context )

        "/* print all global and local variables */"
        print-list( vlocals )
        print-list( plocals )
        print-list( slocals )
        print-list( alocals )
        print-list( vglobals )
        print-list( pglobals )
        print-list( sglobals )
        print-list( sglobals )
        "return 0;"
    "}"

    "/* functions definition */"
    function-definition-list( functions, functions-context )
}

# Operations on context.
+context l-values r-values structs functions environment folding ::=
    ( l-values, r-values, structs, functions, environment, folding )

# Operational environment.
+environment ::= ()
push-environment-descriptor environment descriptor ::= descriptor : environment
check-environment-descriptor environment descriptor ::= in(descriptor,environment)

# Environment-relative functions:
put-return-statement environment values ? check-environment-descriptor(environment,"function") ::= {
    "return " expression(values) ";" }
put-return-statement _ _ ::= ""

# Initializer for scalar variables.
scalar-init s values ::=
    declaration-of(s) " = " expression(values)

scalar-init-list () _ ::= ""
scalar-init-list s:scalars values ::= {
    scalar-init(s, values) ";"
    scalar-init-list(scalars, values) }

# Initializer for pointer variables.
pointer-init p ::=
    declaration-of(p) " = &" identifier-of(scalar-of(p))

pointer-init-list () ::= ""
pointer-init-list p:pointers ::= {
    pointer-init(p) ";"
    pointer-init-list(pointers) }

# Struct declaration.
struct-declaration-list () ::= ""
struct-declaration-list struct:structs ::= {
    declaration-of( struct ) ";"
    struct-declaration-list( structs ) }

# Struct initialization.
list-initializer 0 _ ::= ()
list-initializer n values ::= "(" expression(values) ")" : list-initializer( sub(n,1), values )
struct-init struct values ::=
    declaration-of(struct) " = { " join( ", ", list-initializer(len(fields-of(struct)), values) ) " };"

struct-init-list () _ ::= ""
struct-init-list struct:structs values ::= {
    struct-init( struct, values )
    struct-init-list( structs, values ) }

# Array initialization.
array-init-list () _ ::= ""
array-init-list array:arrays values ::= {
    declaration-of(array) " = { " join( ", ", list-initializer(array-size-of(array), values) ) " };"
    array-init-list( arrays, values ) }

# Function declaration.
function-declaration-list () ::= ""
function-declaration-list function:functions ::= {
    declaration-of( function ) ";"
    function-declaration-list( functions ) }

function-definition function context
@
    (l-values:r-values:structs:functions:environment:folding:_) = context,
    arguments = arguments-of( function ),
    # Build new context with function arguments.
    new-environment = push-environment-descriptor( environment, "function" ),
    new-context = +context( unique-names(cat(arguments,l-values)), unique-names(cat(arguments,r-values)), structs, functions, new-environment, folding )
::= {
    declaration-of(function)
    compound-statement( new-context ) }

function-definition-list () _ ::= ""
function-definition-list functions context
@
    (function:fs) = functions,
    (r-values:l-values:structs:funcs:environment:folding:_) = context,
    new-context = +context(r-values, l-values, structs, diff(funcs, functions), environment, folding)
::= {
    function-definition( function, new-context )
    function-definition-list( fs, context ) }

### Statements ###

# Statement.
# In case of zero folding level.
statement context @ (r-values:l-values:structs:funcs:environment:0:_) = context ::=
      *10 assignment( context )
    | *2 xxxcrement()( any(l-values), )
    | print( any( r-values ) )

statement context @ (r-values:l-values:structs:funcs:environment:folding:_) = context ::=
      *12 assignment( context )
    | *2 xxxcrement()( any(l-values), )
    | *4 print( any( r-values ) )
    | *6 conditional-statement( context )
    | *1 compound-statement( context )

# List of n statements.
statement-list 0 _ ::= ""
statement-list n context ::= {
      statement(context)
      statement-list(sub(n,1), context) }


# Condifional statement (if).
conditional-statement context
@
    (l-values:r-values:_) = context
::= {
    "if ( " expression(r-values) " )"
    compound-statement(context) }

# Compound statement.
compound-statement context
@
    (l-values:r-values:structs:functions:environment:folding:_) = context,                    # folding > 0
    vlocals = scalar-set( local-identifiers(variables-list-size()) ),               # local variables
    slocals = struct-set( local-struct-identifiers(variables-list-size()), structs ), # local structs
    alocals = array-set( local-array-identifiers(arrays-list-size()) ),            # local arrays

    scalars = cat( flatten(map(values-of, slocals)), flatten(map(values-of, alocals)), vlocals ),
    plocals = pointer-set( local-pointer-identifiers(variables-list-size()), scalars ), # local pointers
    
    locals = cat(vlocals, slocals, alocals, plocals),
    new-l-values = unique-names(cat(locals, l-values)),
    new-r-values = unique-names(cat(locals, r-values)),
    new-context = +context( new-l-values, new-r-values, structs, functions, environment, sub(folding,1) )
::= {
    "{"
        scalar-init-list( vlocals, exclude-names(names-list(vlocals),r-values) )
        struct-init-list( slocals, unique-names(cat(vlocals, exclude-names(names-list(slocals),r-values))) )
        array-init-list( alocals, unique-names(cat(vlocals, slocals, exclude-names(names-list(alocals),r-values))) )
        pointer-init-list( plocals )

        statement-list( statement-list-size(), new-context )  put-return-statement(environment,new-r-values)
    "}" }


### Expressions ###

# C unary operators for scalar argument.
unary-operator ::=
      *4 "-"
    | *1 "~"
    | *8 "!"

# C binary operators for scalar arguments.
binary-operator ::=
      *24  "+"
    | *20  "-"
    | *12  "*"
    | *4  "&"
    | *4  "|"
    | *3  "^"
    | *5  "&&"
    | *5  "||"
    | *8  "=="
    | *8  "!="
    | *8  "<"
    | *8  "<="
    | *8  ">"
    | *8  ">="

assignment-operator ::=
      *16 "="
    | *8 "+="
    | *8 "-="
    | *4 "*="
    | "|="
    | "&="
    | "^="

# Print statement. TODO consider printing expressions.

# Print structure contents.
print r-value ? is-struct(r-value) ::= print-list( values-of( r-value ) )
print r-value ? is-array(r-value)  ::= print-list( all-values-of( r-value ) )
# Print any other value.
print r-value ::= "printf( " "\"" printf-spec(type-of(r-value)) "\", "  value-of(r-value) " );"

printf-spec "unsigned int"           ::= "%u"
printf-spec "unsigned char"          ::= "%u"
printf-spec "unsigned short int"     ::= "%u"
printf-spec "unsigned long int"      ::= "%lu"
printf-spec "unsigned long long int" ::= "%llu"

# Print whole list of values.
print-list () ::= ""
print-list r:r-values ::= {
    print( r )
    print-list( r-values ) }

# Assignment statement. May be assignment to expression or function call.

# if we have functions
assignment context
@   (r-values:l-values:structs:functions:_)  = context,
    (_:_) = functions
::=   assignment-expression( any(l-values), r-values )
    | assignment-function-call( any(l-values), any(functions), r-values )

assignment context @ (r-values:l-values:structs:functions:_)  = context ::= 
    assignment-expression( any(l-values), r-values )

assignment-expression l-value values ::=
    value-of(l-value) " " assignment-operator() " " expression(values) ";"
assignment-function-call l-value function arguments ::=
    "/* " value-of(l-value) " " assignment-operator() " */" " " value-of( function, arguments ) ";"

# Pre/Post-increment/decrement statements.
postincrement value ::=     value-of(value) "++" ";"
postdecrement value ::=     value-of(value) "--" ";"
preincrement value ::= "++" value-of(value)      ";"
predecrement value ::= "--" value-of(value)      ";"
xxxcrement ::= postincrement | postdecrement | preincrement | predecrement 

# C expression. Each value of values shall have value-of function defined for it.
expression () ::= integer-constant()
expression values ::= term-expression(values) T-expression(values)
T-expression values ::= " " binary-operator() " " term-expression(values) T-expression(values) | *2 ""
term-expression values ::= *4 atom-expression(values) | unary-operator() " " term-expression(values)
atom-expression values ::=
      *120 expression-value-of(any(values), values)
    | *100 integer-constant()
    | *20  "(" expression(values) ")"
    # Ternary operator goes here.
    | *8   "( " expression(values) " ? " expression(values) " : " expression(values) " )"

expression-value-of value _ ? is-scalar(value) ::= value-of(value)
expression-value-of value _ ? is-pointer(value) ::= value-of(value)
expression-value-of value _ ? is-struct(value) ::= value-of(value)
expression-value-of value _ ? is-array(value) ::= value-of(value)

# C types. They are only unsigned integer for now: this helps with overflow problem
# and with bitwise operators.
base-type ::=
      *16 "unsigned int"
    | *4  "unsigned char"
    | *1  "unsigned short int"
    | *2  "unsigned long int"
    | *3  "unsigned long long int"

# Language indentifiers. They are all have prefices simply to prevent name clashing.
# Integer variable, declared this way: type name ;
+scalar type name ::= ("scalar", type, name)
is-scalar tag:_ ::= eq(tag,"scalar")
identifier-of ("scalar", _, name) ::= name
type-of ("scalar", type, _) ::= type
declaration-of ("scalar", type, name) ::= type " " name
value-of ("scalar", _, n) ::= n

# Pointer to integer type variable, declared this way: type *name;
+pointer scalar name ::= ("pointer", scalar, name)
is-pointer tag:_ ::= eq(tag,"pointer")
identifier-of ("pointer", _, name) ::= name
type-of ("pointer", scalar, _) ::= type-of(scalar)
declaration-of ("pointer", scalar, name) ::= type-of(scalar) "* " name
value-of ("pointer", _, n) ::= "(*" n ")"      # dereferencing
scalar-of ("pointer", scalar, _) ::= scalar

# Struct descriptor.
+struct-descriptor fields name ::= ("struct-d", fields, name)
is-struct-descriptor tag:_ ::= eq(tag, "struct-d")
identifier-of ("struct-d", _, name) ::= name
type-of ("struct-d", _, name) ::= "struct " name
declaration-of ("struct-d", fields, name) ::= {
    "struct " name
    "{"
        struct-field-declaration-list( fields )
    "}" }
fields-of ("struct-d", fields, _) ::= fields

struct-field-declaration-list () ::= ""
struct-field-declaration-list field:fields ::= {
    declaration-of( field ) ";"
    struct-field-declaration-list( fields ) }

# Struct of integers. Made of name and scalar fields.
+struct type name ::= ("struct", type, name)
is-struct tag:_ ::= eq(tag,"struct")
identifier-of ("struct", _, name) ::= name
fields-of ("struct", type, _) ::= fields-of(type)
type-of ("struct", type, _) ::= type-of(type)
declaration-of ("struct", struct, name) ::= type-of(struct) " " name
value-of ("struct", type, name) ::= 
    name "." value-of(any(fields-of(type)))        # get any element of structure

values-of ("struct", type, name) ::= expand-struct-field-names( name, fields-of(type) )
expand-struct-field-names _ () ::= ()
expand-struct-field-names name field:fields ::=
    +scalar( type-of(field), name "." identifier-of(field) ) : expand-struct-field-names( name, fields )

# Function descriptor: type name( arguments )
+function arguments type name ::= ("function", arguments, type, name)
is-function tag:_ ::= eq(tag,"function")
identifier-of ("function", _, _, name) ::= name
arguments-of ("function", arguments, _, _) ::= arguments
declaration-of ("function", arguments, type, name) ::= type " " name "( " join( ", ", map( declaration-of, arguments ) ) " )"

value-of ("function", arguments, _, name) values ::= name "( " join( ", ", function-call-list( arguments, values ) ) " )"

# Form function call list. List of arguments designates number of positional arguments and its types.
function-call-list () _ ::= ()
function-call-list argument:arguments values ? is-scalar(argument) ::=
    push-back( function-call-list( arguments, values ), expression(values) )
function-call-list argument:arguments values ? is-pointer(argument) ::=
    push-back( function-call-list( arguments, values ), function-call-pointer-argument(any( values )) )

function-call-pointer-argument value ? is-pointer(value) ::= identifier-of(value)
function-call-pointer-argument value ? is-scalar(value) ::= "&" identifier-of(value)
function-call-pointer-argument value ? is-struct(value) ::= "&" value-of(value)

function-prototype-generator nvariables ::= scalar-set( function-local-identifiers( nvariables ) )

# Array (one dimensional):
+array type size name ::= ("array", type, size, name)
is-array tag:_ ::= eq(tag,"array")
identifier-of ("array", _, _, name) ::= name
type-of ("array", type, _, _) ::= type
array-size-of ("array", _, size, _) ::= size
declaration-of ("array", type, size, name) ::= type " " name "[" size "]"
value-of ("array", _, size, name) ::= name "[" randint(0,sub(size,1)) "]"
values-of array @ ("array", _, size, _) = array ::= uniq( expand-array( array, randint(1,size) ) )
all-values-of array @ ("array", _, size, _) = array ::= reverse( expand-array-full( array, size ) )

expand-array _ 0 ::= ()
expand-array array n ::= +scalar( type-of(array), value-of(array) ) : expand-array( array, sub(n,1) )

expand-array-full _ 0 ::= ()
expand-array-full array n ::= +scalar( type-of(array), identifier-of(array) "[" sub(n,1) "]" ) : expand-array-full( array, sub(n,1) )

# Label, which specified with: name, folding. TODO: make use of it.
+label folding name ::= ("label", name, folding)
is-label tag:_ ::= eq(tag,"label")
identifier-of ("label", n, _) ::= n

# Identifier generators: for simple local variables, for global variables, for
# pointers, for labels.
scalar-variable-g id ::=
    +scalar( base-type(), id )
pointer-variable-g (id, scalars) ::=
    +pointer( any( scalars ), id )
struct-type-g id ::=
    +struct-descriptor( scalar-set( local-identifiers( randint(1,maximum-struct-size()) )), id )
struct-g (id, structs) ::=
    +struct( any( structs ), id )
function-g id ::=
    +function( function-prototype-generator( function-v-size() ), base-type(), id )
array-g id ::=
    +array( base-type(), array-size(), id )
label-g id ::=
    +label( randint(0,maximum-folding-level()), id )

scalar-set ids ::= map( scalar-variable-g, ids )
pointer-set ids scalars ::= map( pointer-variable-g, wrap-with( ids, scalars ) )
struct-type-set ids ::= map( struct-type-g, ids )
struct-set ids structs ::= map( struct-g, wrap-with( ids, structs ) )
function-set ids ::= map( function-g, ids )
array-set ids ::= map( array-g, ids )
label-set ids ::= map( label-g, ids )

local-identifier ::= "l_" letters()
function-local-identifier ::= "fl_" letters()
global-identifier ::= "g_" letters()
local-pointer-identifier ::= "p_" letters()
global-pointer-identifier ::= "pg_" letters()
struct-type-identifier ::= "S_" letters() 
global-struct-identifier ::= "gs_" letters()
local-struct-identifier ::= "s_" letters()
global-array-identifier ::= "ga_" letters()
local-array-identifier ::= "a_" letters()
function-identifier ::= "f_" letters()
label-identifier ::= "m_" letters()

# Sets. Last letter `s' stands for `set'.
local-identifiers n ::= set( local-identifier, n )
function-local-identifiers n ::= set( function-local-identifier, n )
global-identifiers n ::= set( global-identifier, n )
local-pointer-identifiers n ::= set( local-pointer-identifier, n )
global-pointer-identifiers n ::= set( global-pointer-identifier, n )
struct-type-identifiers n ::= set( struct-type-identifier, n )
global-struct-identifiers n ::= set( global-struct-identifier, n )
local-struct-identifiers n ::= set( local-struct-identifier, n )
global-array-identifiers n ::= set( global-array-identifier, n )
local-array-identifiers n ::= set( local-array-identifier, n )
function-identifiers n ::= set( function-identifier, n )
label-identifiers n ::= set( label-identifier, n )

# Basic definition: letters. By the way, this program better read downside up.
# letter ::= any(( "a", "b", "c", "d", "e", "f", "g", "h", "i", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "x", "y", "z" ),)
letter ::= "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "x" | "y" | "z"
letters ::=  letter() "" | *2 letter() letters()

integer-constant "unsigned int" ::= randint(0,100) ""
integer-constant "unsigned char" ::= randint(0,100) ""
integer-constant "unsigned short int" ::= randint(0,100) ""
integer-constant "unsigned long int" ::= randint(0,100) "ul"
integer-constant "unsigned long long int" ::= randint(0,100) "ull"

integer-constant @ value = randint(0,100) ::=
      *8 value ""
    | *10 value "u"
    | *2 value "ul"
    | *1 value "ull"

TBD ::= "to be determined"

### Tools: utility functions ###

wrap-with () _ ::= ()
wrap-with x:xs y ::= (x, y):wrap-with( xs, y )

strlcatwith _ () ::= ()
strlcatwith y x:xs ::= (y x):strlcatwith(y, xs)

names-list () ::= ()
names-list value:values ::= identifier-of(value) : names-list(values)
unique-names values ::= reverse(unique-names( reverse(names-list(values)), reverse(values) ))
unique-names _ () ::= ()
unique-names name:names   _  :values ? in(name,names) ::= unique-names(names, values)
unique-names  _  :names value:values ::= value : unique-names(names, values)

exclude-names _ () ::= ()
exclude-names names value:values ? in(identifier-of(value),names) ::= exclude-names( names, values )
exclude-names names value:values ::= value : exclude-names( names, values )

flatten () ::= ()
flatten x:xs ::= cat(x, flatten(xs))

