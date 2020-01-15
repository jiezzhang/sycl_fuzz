S ::= program() # here to specify global program parameters

max-loop-len ::= 64
array-size ::= mul(max-loop-len(), 3)

####################################################################################################
# Just a more convenient generation start point name                                               #
####################################################################################################

program @
  accs    = acc-set(),
  # number of arrays to generate for each array dimension
  fsn     = (randint(0,2), randint(0,5), randint(0,3), randint(0,3)),
  as      = (), # No global array is used
  fs      = shuffle(fun-set(fsn)), # generate function names acording to already genererated numbers
  locals  = var-set(randint(1, 4)), # function main locals
  vars    = union(locals, accs),   # there should be at least one variable
  ivs     = (), # names of variables used for array indices
  # context = (lvals, rvals, arrays, free index variables, functions, return statement, cean expression form, throw statement)
  ctx     = (vars:vars:as:ivs:fs:"void":():0:())  
::= {
  "// This is C++" # This comment is needed for testgen harness, so it can treat this source as C++
  "#if defined(REFRUN)"
  "  #define CEAN_HEADER1(dim0) for (int cean0 = 0; cean0 != (dim0); ++ cean0) {"
  "  #define CEAN_HEADER2(dim0, dim1) for (int cean0 = 0; cean0 != (dim0); ++ cean0) { for (int cean1 = 0; cean1 != (dim1); ++ cean1) {"
  "  #define CEAN_HEADER3(dim0, dim1, dim2) for (int cean0 = 0; cean0 != (dim0); ++ cean0) { for (int cean1 = 0; cean1 != (dim1); ++ cean1) { for (int cean2 = 0; cean2 != (dim2); ++ cean2) {"
  "  #define CI(idx,start,dim,step) start+cean##idx*(step)"
  "  #define CEAN_FOOTER1 }"
  "  #define CEAN_FOOTER2 }}"
  "  #define CEAN_FOOTER3 }}}"
  "#else"
  "  #define CEAN_HEADER1(dim0)"
  "  #define CEAN_HEADER2(dim0, dim1)"
  "  #define CEAN_HEADER3(dim0, dim1, dim2)"
  "  #define CI(idx,start,dim,step) start:dim:step"
  "  #define CEAN_FOOTER1"
  "  #define CEAN_FOOTER2"
  "  #define CEAN_FOOTER3"
  "#endif"
  "#include \"libcpp.h\""
  "#include <CL/sycl.hpp>"
  ""
  list-lines(as, decl-arr)
  list-lines(fs, decl-fun)
  "template <typename T, int dims, cl::sycl::access::mode mode,"
  "        cl::sycl::access::target target, cl::sycl::access::placeholder placeholder>"
  "void kernel(cl::sycl::nd_item<dims> item, cl::sycl::accessor<T, dims, mode, target, placeholder> result)"
  "{"
    declarations(locals, accs)
    statements(ctx)
    for-clause(ctx)
    statements(ctx)
  "}"
  fun-defs(fs, as, fs)
}

fun-defs () _ _ ::= ""
fun-defs f:l as fs @
  (fname:ftype:fsig:_) = f,
  params  = var-set(len(fsig)),
  vars    = params,
  ivs     = (),
  new-ctx = (params:vars:as:ivs:l:ftype:():0:())
::= {
  ftype " " fname "(" named-fun-sig(fsig, params) ") " block(new-ctx)
  fun-defs(l, as, fs) }

named-fun-sig () () ::= ""
named-fun-sig ftype:() param:() @
  (param-var, param-type) = param
::= ftype " " param-var
named-fun-sig ftype:ftypes param:params @
  (param-var, param-type) = param
::= ftype " " param-var ", " named-fun-sig(ftypes, params)

####################################################################################################
# declarations                                                                                     # 
####################################################################################################

declaration x values @ 
  new-ctx = (():values:():():():"void":():0:()),
  (variable, var-type) = x
::= *100 var-type " " variable " = " expr(new-ctx) ";"

declarations () _ ::= ""
declarations x:xs values
::= {
  declaration(x, values)
  declarations(xs, (x:values)) }

####################################################################################################
# statements                                                                                       #
####################################################################################################

statement ctx
::=  *100 lv-assign(ctx)
#  | *100 cean-lv-assign(ctx) # until DPD200285292 is fixed
#  | *20  cilk-spawn-lv-assign(ctx) # until DPD200181746 is fixed
#  | *20  cean-if-clause(ctx) # until DPD200285292 is fixed
  | *20  for-clause(ctx)
  | *10  if-clause(ctx)
  | *5   block(ctx)
#  | *5   swap-stmt(ctx)
  | *5   switch-clause(ctx) # until DPD200136238 is fixed (FIXED)
  | *2   break-stmt(ctx)
  | *2   continue-stmt(ctx)
#  | *2   try-catch-stmt(ctx)
#  | *2   throw-stmt(ctx)
  | *1   return-stmt(ctx)

#swap-stmt ctx ? islval(ctx) ::= "swap( " lval(ctx) ", " lval(ctx) " );"
#swap-stmt _ ::= "; /* lvalue swap could be here */"

return-stmt ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(ret, "void") ::= "return " expr(ctx) ";"
return-stmt _ ::= ""

break-stmt ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(ivs), 0) ::= "break;"
break-stmt _ ::= "; /* break statement was omited here */"

continue-stmt ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(ivs), 0) ::= "continue;"
continue-stmt _ ::= "; /* continue statement was omited here */"

try-catch-stmt ctx
 @ (lv:rv:as:ivs:fs:ret:caf:throw:_) = ctx,
   locals = var-set(1),
   (local:_) = locals,
   new-lv = union(lv, locals),
   new-rv = union(rv, locals),
   new-ctx = (new-lv:new-rv:as:ivs:fs:ret:():throw:())
 ? neq(throw, 0) ::= {
  "try {"
    block(ctx)
  "} catch (" type() " " local ") {"
    block(new-ctx)  
  "}" }
| {
  "try {"
    block(ctx)
  "} catch (" type() ") {"
    block(ctx)  
  "}" }

try-catch-stmt _ ::= "; /* try-catch statement was omited here */"

throw-stmt ctx @ (lv:rv:as:ivs:fs:ret:caf:throw:_) = ctx ? neq(throw, 0) ::= "throw " expr(ctx) ";"
throw-stmt _ ::= "; /* throw statement was omited here */"

statements ctx
::=
  *2 statement(ctx)
  | *1 {
  statement(ctx)
  statements(ctx) }

# block
block ctx @
  (lv:rv:as:ivs:fs:ret:_) = ctx,
  locals = diff(var-set(randint(0,4)), rv),
  local-asn = (randint(0,2), randint(0,0), randint(0,0)),
  local-as = diff(arr-set(local-asn), rv),
  new-lv = union(lv, locals),
  new-rv = union(rv, locals),
  new-as = union(as, local-as),
  new-ctx = (new-lv:new-rv:new-as:ivs:fs:ret:():0:()),
  new-ctx-throw = (new-lv:new-rv:new-as:ivs:fs:ret:():1:())
::= *5 {
  "{"
    list-lines(local-as, decl-arr)
    declarations(locals, rv)
    statement(new-ctx)
    statement(new-ctx)
    statements(new-ctx)
    return-stmt(new-ctx)
  "}" }
#| {
#  "try {"
#    declarations(locals, rv)
#    statement(new-ctx-throw)
#    statement(new-ctx-throw)
#    statements(new-ctx-throw)
#    return-stmt(new-ctx-throw)
#  "} catch(...) { "
#    block(ctx)
#  "}" }

# assignment
lv-assign ctx @
  lv = lval(ctx),
  (lv-exp, lv-type) = lv
? islval (ctx)
::= *10 lv-exp " " assign-op() " " expr(ctx) ";"
  | *2  plusplus(ctx) ";"

lv-assign _ ::= "; /* lvalue change could be here */"

islval ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx
::= or(neq(len(lv), 0), and(neq(len(as),0), and(neq(len(ivs), 0), eq(ret, "void"))))

lval ctx ? not(islval(ctx)) ::= "ERROR!!!"

lval ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(lv), 0)
::= *4 lval1(ctx)
  |    lval2(ctx)
lval ctx ::= lval2(ctx)

lval1 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ::= *4 any(lv)

lval2 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? and(neq(len(as),0), and(neq(len(ivs), 0), eq(ret, "void")))
::= lval3(ctx)
lval2 ctx ::= lval1(ctx)
lval3 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx,
  new-arr = any(as),
  (arr-name, arr-type) = new-arr
::= (ivs-val(arr-name, ctx), arr-type)

plusplus ctx ? not(islval(ctx)) ::= "ERROR!!!"

plusplus ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx 
::= anyVarTypes(lv, scalar_type_sets()) "++"
  | "++" anyVarTypes(lv, scalar_type_sets())

# CEAN

isarr ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx
::= neq(len(as), 0)

cean-lv-assign ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? and(isarr(ctx), eq(ret, "void"))
::= cean-lv-assign2(ctx)

cean-lv-assign _ ::= "; /* CEAN lvalue change could be here */"

cean-lv-assign2 ctx
 @ (lv:rv:as:ivs:fs:ret:old-caf:throw:_) = ctx,
   ca = anyVar(as),
   (aname:adim:_) = ca,
   caf = cean-form(randint(1, adim)),
   new-as = diff(as,(ca:())),
   new-lval-ctx = (lv:rv:new-as:ivs:fs:ret:(caf:()):throw:()),
   cean-lval = cean-val(ca, new-lval-ctx),
   new-ctx = (lv:rv:new-as:ivs:fs:ret:(caf,cean-lval):throw:())
 ? eq(len(old-caf), 0) # assert 
::= {
  "CEAN_HEADER" len(caf) "(" cean-ref-header(caf) ")"
    cean-lval " " assign-op() " " expr(new-ctx) ";"
  "CEAN_FOOTER" len(caf) }

cean-ref-header adim:() ::= adim
cean-ref-header caf @ (adim:_) = caf ::= adim ", " cean-ref-header(tail(caf))

# generate CEAN Array Form
cean-form 0 ::= ()
cean-form adim ::= cean-form2() : cean-form(sub(adim, 1))
cean-form2 ::= randint(1, array-size()) | *5 array-size()

# select arrays with form suitable for current CAF
cean-get-new-as ctx @ (lv:rv:as:ivs:fs:ret:caf2:_) = ctx ? neq(len(caf2), 0)
::= cean-get-new-as2(as, get(caf2,0))

cean-get-new-as ctx ::= () 

cean-get-new-as2 () caf ::= ()
cean-get-new-as2 as caf @ (a:_) = as, (aname:adim:_) = a ? ge(adim, len(caf))
::= a : cean-get-new-as2(tail(as), caf)

cean-get-new-as2 as caf ::= cean-get-new-as2(tail(as), caf)

cean-get-pre-as ctx @ (lv:rv:as:ivs:fs:ret:caf2:_) = ctx ::= tail(caf2)

# CEAN IF

cean-if-clause ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? and(isarr(ctx), neq(ret, 1))
::= cean-if-clause2(ctx)

cean-if-clause _ ::= "; /* CEAN if could be here */"

cean-if-clause2 ctx
 @ (lv:rv:as:ivs:fs:ret:old-caf:throw:_) = ctx,
   ca = anyVar(as),
   (aname:adim:_) = ca,
   caf = cean-form(randint(1, adim)),
   (cas, cvals) = cean-vals(ca, caf, ctx),
   new-as = diff(as, cas),
   new-caf = push-front(cvals, caf),
   new-ctx = (lv:rv:new-as:ivs:fs:ret:new-caf:throw:())
 ? eq(len(old-caf), 0) # assert 
::= {
  "CEAN_HEADER" len(caf) "(" cean-ref-header(caf) ")"
    "if (" cean-cond(new-ctx) ")" cean-if-block(new-ctx)
  "CEAN_FOOTER" len(caf) }
 | {
  "CEAN_HEADER" len(caf) "(" cean-ref-header(caf) ")"
    "if (" cean-cond(new-ctx) ")" cean-if-block(new-ctx) " else " cean-if-block(new-ctx)
  "CEAN_FOOTER" len(caf) }

cean-cond ctx
::= *16 any(cean-get-pre-as(ctx))
  | *1 cean-cond(ctx) " " logical-op() " " cean-cond(ctx)
  | *1 "(" cean-cond(ctx) ")"
  | *1 expr(ctx) " " relation-op() " " expr(ctx)

cean-if-block ctx ::= {
  "{"
    cean-if-block-stmt(ctx)
    cean-if-block-stmts(ctx)
  "}" }

cean-if-block-stmt ctx ::= any(cean-get-pre-as(ctx)) " " assign-op() " " expr(ctx) ";"

cean-if-block-stmts ctx ::= *2 cean-if-block-stmt(ctx) | ""

# returns (list of arrays : list of their cean values)
cean-vals ca caf ctx
 @ (lv:rv:as:ivs:fs:ret:old-caf:throw:_) = ctx,
   new-as = diff(as,(ca:())),
   new-val-ctx = (lv:rv:new-as:ivs:fs:ret:(caf:()):throw:()),
   cval = cean-val(ca, new-val-ctx),
   next-val-ctx = (lv:rv:new-as:ivs:fs:ret:(caf,cval):throw:()),
   (next-cas, next-cean-vals) = cean-vals2(next-val-ctx)
 ? eq(len(old-caf), 0) # assert
::= push-front(next-cas, ca), push-front(next-cean-vals, cval)

cean-vals2 ctx ? neq(len(cean-get-new-as(ctx)), 0)
::= (), () | cean-vals3(ctx)

cean-vals2 ctx ::= (), ()

cean-vals3 ctx
 @ (lv:rv:as:ivs:fs:ret:caf2:throw:_) = ctx,
   ca = any(cean-get-new-as(ctx)),
   new-as = diff(as,(ca:())),
   new-val-ctx = (lv:rv:new-as:ivs:fs:ret:caf2:throw:()),
   cval = cean-val(ca, new-val-ctx),
   next-val-ctx = (lv:rv:new-as:ivs:fs:ret:push-back(caf2,cval):throw:()),
   (next-cas, next-cean-vals) = cean-vals2(next-val-ctx)
::= push-front(next-cas, ca), push-front(next-cean-vals, cval)

# generate CEAN value

cean-val a ctx @ (aname:adim:_) = a, (lv:rv:as:ivs:fs:ret:caf2:_) = ctx, (caf:_) = caf2 
::= aname cean-val2(sub(adim, len(caf)), len(caf), caf, ctx)

cean-val2 0 len-caf () ctx ::= ""
cean-val2 free-dim len-caf () ctx
::= "[" safe-arr-idx(ctx) "]" cean-val2(sub(free-dim, 1), len-caf, (), ctx)

cean-val2 0 len-caf caf ctx @ (adim:_) = caf
::= "[" cean-val3(adim, sub(len-caf, len(caf)), ctx) "]" cean-val2(0, len-caf, tail(caf), ctx)

cean-val2 free-dim len-caf caf ctx @ (adim:_) = caf
::= "[" safe-arr-idx(ctx) "]" cean-val2(sub(free-dim, 1), len-caf, caf, ctx)
  | "[" cean-val3(adim, sub(len-caf, len(caf)), ctx) "]" cean-val2(free-dim, len-caf, tail(caf), ctx)

cean-val3 adim idx ctx ::= "CI(" idx ", " cean-val4(adim, ctx) ")"

cean-val4 adim ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx,
                     step = randint(1, div(array-size(), adim))
::= cean-dim(randint(0, sub(array-size(), mul(step, adim))), adim, step)
  | cean-dim(sub(randint(mul(step, adim), array-size()),1), adim, neg(step))
neg step ::= sub(sub(step, step), step)
cean-dim start dim step ::= start ", " dim ", " step

safe-arr-idx ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(ivs), 0)
::= *10 ivs-val3(ctx)
  | randint(0, sub(array-size(), 1))
safe-arr-idx ctx ::= randint(0, sub(array-size(), 1))

# Cilk+ spawn/sync

# assignment
cilk-spawn-lv-assign ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? and(islval (ctx), neq(len(fs), 0))
::= cilk-spawn-lv-assign1(ctx)
  | cilk-spawn-lv-assign2(ctx)
  | cilk-spawn-lv-assign3(ctx) 

cilk-spawn-lv-assign _ ::= "; /* cilk-spawn could be here */"

cilk-spawn-lv-assign1 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(lv), 0)
::= {
  lval1(ctx) " = _Cilk_spawn "  fun-call(any(fs), ctx) ";"
  "_Cilk_sync;" }

cilk-spawn-lv-assign1 ctx
::= cilk-spawn-lv-assign3b(ctx)

cilk-spawn-lv-assign2 ctx @ (lv:rv:as:ivs:fs:ret:caf:_) = ctx ? neq(len(lv), 0)
::= cilk-spawn-lv-assign2b(ctx)

cilk-spawn-lv-assign2 ctx
::= cilk-spawn-lv-assign3b(ctx)

cilk-spawn-lv-assign2b ctx
  @ (lv:rv:as:ivs:fs:ret:caf:throw:_) = ctx,
    i=anyVar(lv),
    new-ctx = (diff(lv,(i,)):diff(rv,(i,)):as:ivs:fs:ret:caf:throw:())
::= {
  i " = _Cilk_spawn "  fun-call(any(fs), ctx) ";"
  statement(new-ctx)
  "_Cilk_sync;" }

cilk-spawn-lv-assign3 ctx @ (lv:rv:as:ivs:fs:ret:caf:_) = ctx ? and(isarr(ctx), and(neq(len(ivs), 0), eq(ret, "void"))) 
::= cilk-spawn-lv-assign3b ctx

cilk-spawn-lv-assign3 ctx ::= cilk-spawn-lv-assign2(ctx) 

cilk-spawn-lv-assign3b ctx
  @ (lv:rv:as:ivs:fs:ret:caf:throw:_) = ctx,
    a = anyVar(as),
    new-ctx = (lv:rv:diff(as,(a,)):ivs:fs:ret:caf:throw:())
::= {
  ivs-val(a, ctx) " = _Cilk_spawn "  fun-call(any(fs), ctx) ";"
  statement(new-ctx)
  "_Cilk_sync;" }



# for cycle

min-lim     ::= 0
max-lim     ::= sub(max-loop-len(), 1)
mid-lim     ::= div(max-loop-len(), 2)
low-lim ()  ::= min-lim() | randint(min-lim(), mid-lim())
big-lim ()  ::= max-lim() | randint(mid-lim(), max-lim())
low-lim ivs ::= anyVar(ivs) | min-lim() | randint(min-lim(), mid-lim())
big-lim ivs ::= anyVar(ivs) | max-lim() | randint(mid-lim(), max-lim())
step-pos i  ::= i " += " randint(1,8) | *4 i "++" | *4 "++" i
step-neg1 i ::= i "--" | "--" i
step-neg i  ::= i " -= " randint(1,8) | *8 step-neg1(i)

for-clause (():_) ::= "; /* for-cycle skipped due to no free lvals variables */"

for-clause ctx @
  (lv:rv:as:ivs:fs:ret:old_caf:throw:_) = ctx,
  i       = anyVar(lv),
  new-lv  = diff(lv,(i,)),
  new-ivs = (i:ivs),
  new-ctx = (new-lv:rv:as:new-ivs:fs:ret:():throw:())
  ? le(len(new-ivs), 3)

::= *10 "for (" i "=" low-lim(ivs) "; " i " <= " big-lim(ivs) "; " step-pos(i)  ") " block(new-ctx)
  | *2  "for (" i "=" big-lim(ivs) "; " i " > "  low-lim(ivs) "; " step-neg1(i) ") " block(new-ctx)
  | *1  "for (" i "=" big-lim(ivs) "; " i " <= " max-lim()    "; " step-neg(i)  ") " block(new-ctx)

for-clause ctx ::= "; /* for-cycle skipped due to nesting limit */"

# if condition
if-clause ctx
::= "if (" cond(ctx) ") " block(ctx)
  | "if (" cond(ctx) ") " block(ctx) " else " block(ctx)

switch-clause ctx
::= {
    "switch (" expr(ctx) ") {"
      switch-cases(int-set(randint(1,5)), ctx)
    "}" }
  | {
    "switch (" expr(ctx) ") {"
      switch-cases(int-set(randint(1,5)), ctx)
      "default: "
        statements(ctx)
    "}" }

switch-cases () ctx ::= ""

switch-cases (n:l) ctx
::= {
  switch-case(n, ctx)
  switch-cases(l, ctx) }

switch-case n ctx @
  (n-val, n-type) = n
::= {
    "case " n-val ": "
      statements(ctx) }
  | {
    "case " n-val ": "
      statements(ctx)
      "break;" }


####################################################################################################
# expressions                                                                                      #
####################################################################################################

# condition
cond ctx
::= *16 rvalint(ctx)
  | *1 cond(ctx) " " logical-op() " " cond(ctx)
  | *1 "(" cond(ctx) ")"
  | *1 expr(ctx) " " relation-op() " " expr(ctx)

expr ctx ::= expr-term(ctx) expr-T(ctx)

expr-T ctx
::= *1 " " binary-op() " " expr-term(ctx) expr-T(ctx)
  | *3 ""

expr-term ctx
::= *24 int()
  | *24 rvalint(ctx)
  | *2 unary-op() " " expr-term(ctx)
  | *24 try-fun-call(ctx)
  | *1 "(" expr(ctx) ")"
  | *1 "(" expr(ctx) ", " expr(ctx) ")"
  | *1 "(" cond(ctx) " ? " expr(ctx) " : " expr(ctx) ")"
  | *1 div-expr(ctx)

div-expr ctx @ rv = rvalint(ctx)
::= "(" rv "? (" expr(ctx) ") % " rv " : (" expr(ctx) "))"
  | "(" rv "? (" expr(ctx) ") / " rv " : (" expr(ctx) "))"

isrval ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx
::= or(or(or(neq(len(rv), 0), neq(len(ivs), 0)), neq(len(cean-get-new-as(ctx)), 0)), neq(len(cean-get-pre-as(ctx)), 0))

rvalint ctx ? not(isrval(ctx)) ::= int()
rvalint ctx ::= rval(ctx)

rval ctx ? not(isrval(ctx)) ::= "ERROR!!!"

rval ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(rv), 0)
::= *100 rval1(ctx)
  | *20  rval2(ctx)
  | *20  rval3(ctx)
  | *20  rval4(ctx)
rval ctx ::= rval2(ctx)

rval1 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx
::= *100 anyVar(rv)
  | "copy(" anyVar(rv) ")"

rval2 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? and(neq(len(as),0), neq(len(ivs), 0))
::= *20 ivs-val(anyVar(as), ctx) 
  | "copy(" ivs-val(anyVar(as), ctx) ")"
rval2 ctx ::= rval3(ctx)

rval3 ctx @ cas = cean-get-new-as(ctx) ? neq(len(cas), 0)
::= cean-val(any(cas), ctx) 
rval3 ctx ::= rval4(ctx)

rval4 ctx @ cas = cean-get-pre-as(ctx) ? neq(len(cas), 0)
::= any(cas)
rval4 ctx ::= rval1(ctx)


# C operators
unary-op
::= "-" | "+" | "!" | "~"
  | "(" type() ")" # cast

binary-op
::= *20 "+"
  | *8  "-"
  | *6  "*"
#  |     "|"
#  |     "&"
  |     "^"
  |     relation-op()
  |     logical-op()

relation-op
::= "=="
  | "!="
  | "<="
  | ">="
  | "<"
  | ">"

logical-op
::= "&&"
  | "||"

assign-op
::= *2 "="
  |    "+="
  |    "-="
  |    "*="
#  |    "&="
#  |    "|="
#  |    "^="

#disable most binary operators

####################################################################################################
# manipulations with arrays and functions                                                          # 
####################################################################################################

list-lines () foo ::= ""
list-lines i:l foo
::= {
  foo(i,) # ASK TOLIK: why "foo(i,)" and not "foo(i)"?
  list-lines(l, foo) }

ivs-val a ctx @ (aname:adim:_) = a ::= aname ivs-val2(adim, ctx)
ivs-val2 0 _ ::= ""
ivs-val2 adim ctx ::= "[" "(size_t)(" ivs-val3(ctx) ")]" ivs-val2(sub(adim, 1), ctx)
ivs-val3 ctx @ (lv:rv:as:ivs:fs:ret:caf:_) = ctx
::= *20 anyVar(ivs)
  | anyVar(ivs) "+" randint(1, mul(max-loop-len(), 2))
  | randint(max-loop-len(), sub(array-size(), 1)) "-" anyVar(ivs)
  | anyVar(ivs) "+" anyVar(ivs)
  | randint(max-loop-len(), mul(max-loop-len(), 2)) "+" anyVar(ivs) "-" anyVar(ivs)
  | "2*" anyVar(ivs)
  | "2*" anyVar(ivs) "+" anyVar(ivs)
  | max-loop-len() "+2*" anyVar(ivs) "-" anyVar(ivs)
  | "3*" anyVar(ivs)
  | randint(mul(max-loop-len(), 2), sub(array-size(), 1)) "-2*" anyVar(ivs)
  | sub(array-size(), 1) "-3*" anyVar(ivs)
# nexted expressions can't have CEAN form
  | "((unsigned int)(" expr((lv:rv:as:ivs:fs:ret:():0:())) "))%" array-size()

decl-arr a @ 
  (array,array-type) = a,
  (aname, adim) = array
::= array-type " " aname decl-arr2(adim) ";"
decl-arr2 0 ::= ""
decl-arr2 adim ::= "[" array-size() "]" decl-arr2(sub(adim, 1))

try-fun-call ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(fs), 0) ::= fun-call(any(fs), ctx)
try-fun-call _ ::= int()
fun-call f ctx @ (fname:_:():_) = f ::= fname "()"
fun-call f ctx @ (fname:_:fsig:_) = f, (i:l) = fsig
::= fname "(" expr(ctx) fun-call2(l, ctx)  ")"
fun-call2 () _ ::= ""
fun-call2 i:l ctx ::= ", " expr(ctx) fun-call2(l, ctx)

decl-fun f @ (fname:ftype:fsig:_) = f ::= ftype " " fname "(" join(", ", fsig) ");"

####################################################################################################
# sets                                                                                             #
#################################################################################################### 
acc-set            ::= set-gen(acc, global_acc_type, (), 1)
var-set n          ::= set-gen(var, type, (), n)
int-set n          ::= set-gen(int, integer_type, (), n)
arr-set l          ::= arr-set2(l, 1)
arr-set2 () _      ::= ()
arr-set2 n:l dim   ::= cat(arr-set-gen(dim, n), arr-set2(l, add(dim, 1)))

fun-set l          ::= fun-set2(l, 0)
fun-set2 () _      ::= ()
fun-set2 n:l arity ::= cat(fun-set-gen(arity, n), fun-set2(l, add(arity, 1)))

set-gen _ _ _ 0 ::= ()
set-gen genf type_foo genf_in n @
  l = set-gen(genf, type_foo, genf_in, sub(n, 1)),
  i = set-uniq(genf(genf_in,), type_foo, l, genf, genf_in)
::= i:l
set-uniq i type_foo l genf genf_in ? in(i, l) ::= set-uniq(genf(genf_in,), type_foo, l, genf, genf_in)
set-uniq i type_foo _ _ _ @
  var-type = type_foo()
::= (i, var-type)

# WTF? genf(genf_in,) converts list into a string???
arr-set-gen _ 0 ::= ()
arr-set-gen dim n @
  l = arr-set-gen(dim, sub(n, 1)),
  i = arr-set-uniq(arr(dim), l, dim)
::= i:l
arr-set-uniq i l dim ? in(i, l) ::= arr-set-uniq(arr(dim), l, dim)
arr-set-uniq i _ _ @
  arr-type = type()
::= (i, arr-type)

fun-set-gen _ 0 ::= ()
fun-set-gen arity n @
  l = fun-set-gen(arity, sub(n, 1)),
  i = fun-set-uniq(fun(arity), l, arity)
::= i:l
fun-set-uniq i l arity ? in(fun-name(i), fun-names(l)) ::= fun-set-uniq(fun(arity), l, arity)
fun-set-uniq i _ _ ::= i

fun-name f @ (fname:_) = f ::= fname
fun-names () ::= ()
fun-names f:l @ (fname:_) = f ::= fname:fun-names(l)

getn 0 _ ::= ()
getn l s ? neq(len(s),0) ::= get(s, 0) : getn(sub(l,1), tail(s))
getn l _ ::= ()

####################################################################################################
# some basic stuff                                                                                 #  
####################################################################################################
acc _      ::= "result[item.get_global_linear_id()]"
var _      ::= "v_" int() | *1000 "v_" identifier()
int _      ::= int()
arr dim    ::= "a" dim "_" int(), dim | *1000 "a" dim "_" identifier(), dim
fun arity  ::= "f" arity "_" int(), type(), fun-sig(arity)
             | *1000 "f" arity "_" identifier(), type(), fun-sig(arity)
fun-sig 0 ::= ()
fun-sig arity ::= type() : fun-sig(sub(arity, 1))

int ::= str(randint(1,max-int()))
max-int ::= 100

type
::= *100 scalar_type()
#  | *50  vec_type()

scalar_type
::= integer_type()
  | float_type()

integer_type
::= cpp_type()
  | unsigned_cpp_type()
  | cl_type()
  | unsigned_cl_type()

cpp_type
::= *24 "int"
  | *4  "long"
  | *2  "long long"
  | *1  "short"
  | *2  "char"

unsigned_cpp_type
::= "unsigned " cpp_type()

cl_type
::= *24 "cl::sycl::cl_char"
  | *2  "cl::sycl::cl_short"
  | *2  "cl::sycl::cl_int"
  | *2  "cl::sycl::cl_long"


unsigned_cl_type
::= *24 "cl::sycl::cl_uchar"
  | *2  "cl::sycl::cl_ushort"
  | *2  "cl::sycl::cl_uint"
  | *2  "cl::sycl::cl_ulong"

float_type
::= "float"
  | "double"
  | "cl::sycl::cl_double"
  | "cl::sycl::cl_half"
  | "cl::sycl::cl_float"

global_acc_type
::= "unsigned long"

identifier ::= letter() letters()
letters ::= *4 letter() letters() | *2 ""
letter
::= "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j"
  | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t"
  | "u" | "v" | "w" | "x" | "y" | "z"

####################################################################################################
# some type sets                                                                                   #  
####################################################################################################
float-type-set ::= "float","double","cl::sycl::cl_double","cl::sycl::cl_half","cl::sycl::cl_float"
integer-type-set ::= "int","long","long long","short","char","unsigned int","unsigned long","unsigned long long","unsigned short","unsigned char"
cl-integer-type-set ::= "cl::sycl::cl_char","cl::sycl::cl_short","cl::sycl::cl_int","cl::sycl::cl_long","cl::sycl::cl_uchar","cl::sycl::cl_ushort","cl::sycl::cl_uint","cl::sycl::cl_ulong"
scalar_type_sets ::= cat(float-type-set(), cat(integer-type-set(),cl-integer-type-set()))
