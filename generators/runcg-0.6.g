S ::= program() # here to specify global program parameters

max-loop-len ::= 64
array-size ::= mul(max-loop-len(), 3)

####################################################################################################
# Just a more convenient generation start point name                                               #
####################################################################################################

program @
  accs    = acc-set(),
  structs = struct-set(randint(1, 3)),
  # number of arrays to generate for each array dimension
  fsn     = (randint(0,2), randint(0,5), randint(0,3), randint(0,3)),
  fs      = shuffle(fun-set(fsn)), # generate function names acording to already genererated numbers
  locals  = var-set(randint(1, 4)), # function main locals
  bufs    = buf-set(randint(2, 5)), # buffer main locals
  buf-accs= buf-acc-set(bufs), # acc main locals
  buf-accs1 = output(buf-accs),
  vars    = union(locals, accs),   # there should be at least one variable
  as      = buf-accs,
  ivs     = (), # names of variables used for array indices
  #TODO:PASS SELFDEFINED TYPE BY CTX
  #TODO:RECORD GLOBAL TYPE IN PYTHON ARGUMENTS??
  # context = (lvals, rvals, arrays, free index variables, functions, return statement, cean expression form, throw statement)
  ctx     = (vars:vars:as:ivs:fs:"void":():0:())
::= {
  "#include \"libcpp.h\""
  "#include \"type_cast.hpp\""
  "#include <CL/sycl.hpp>"
  "using namespace sycl;"
  ""
  list-lines(structs, decl-struct)
  list-lines(fs, decl-fun)
  "void kernel_fun(queue &queue, range<1> global_range,"
  "                range<1> local_range,"
  "                buffer<ulong, 1> &buf) {"
     declarations(bufs, accs)
  "  queue.submit([&](handler &cgh) {"
  "    auto result = buf.template get_access<access::mode::read_write>(cgh);"
       declarations-acc(bufs,buf-accs)
  "    cgh.parallel_for<class fuzz_kernel>("
  "      nd_range<1>(global_range, local_range),"
  "      [=](nd_item<1> item) { "
          declarations(locals, accs)
          statements(ctx)
          for-clause(ctx)
          statements(ctx)
  "    });"
  "  });"
  "}"
  fun-defs(fs, (), fs)
}

fun-defs () _ _ ::= ""
fun-defs f:l as fs @
  (fname:ftype:fsig:_) = f,
  params  = fun-var-set(fsig),
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
? is-str(var-type)
::= *100 var-type " " variable " = " expr(new-ctx, var-type) ";"

declaration x values @
  new-ctx = (():values:():():():"void":():0:()),
  (variable, var-type) = x
? in("buffer", var-type)
::= declaration-buf(x, values)

declaration x values ::= "; //incorrect declaration"

declaration-buf x values @
  new-ctx = (():values:():():():"void":():0:()),
  (variable, var-type) = x,
  (_, real-type) = var-type
::= {
real-type " " variable "_ptr[" array-size() "] = {" const(real-type) "};"
"buffer<" real-type "> " variable  " (" variable "_ptr, range(" array-size() "));"
}

#TODO: Apply other mode
declaration-acc buff buf-acc @
  (buf-name, buf-type) = buff,
  (buf-acc-detail, buf-acc-type) = buf-acc,
  buf-acc-real-type = constsub(buf-acc-type),
  (buf-acc-name, buf-acc-dim) = buf-acc-detail
? in("const", buf-acc-type)
::= "accessor <" buf-acc-real-type ", 1, access::mode::read> " buf-acc-name "(" buf-name ", cgh);"
  | "accessor <" buf-acc-real-type ", 1, access::mode::read, access::target::constant_buffer> " buf-acc-name "(" buf-name ", cgh);"


declaration-acc buff buf-acc @
  (buf-name, buf-type) = buff,
  (buf-acc-detail, buf-acc-type) = buf-acc,
  (buf-acc-name, buf-acc-dim) =buf-acc-detail
#::= "auto " buf-acc-name " = " buf-name ".template get_access<access::mode::read_write>(cgh);"
::= "accessor <" buf-acc-type ", 1, access::mode::read_write> " buf-acc-name "(" buf-name ", cgh);"

declarations () _ ::= ""
declarations x:xs values
::= {
  declaration(x, values)
  declarations(xs, (x:values)) }

declarations-acc () () ::= ""
declarations-acc buff:bufs buf-acc:buf-accs
::= {
  declaration-acc(buff, buf-acc)
  declarations-acc(bufs, buf-accs)
}

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

return-stmt ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(ret, "void") ::= "return " expr(ctx, ret) ";"
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

#
throw-stmt ctx @ (lv:rv:as:ivs:fs:ret:caf:throw:_) = ctx ? neq(throw, 0) ::= "throw " expr(ctx, "int") ";"
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
  locals = diff_axis(var-set(randint(0,4)), rv, 0),
  local-asn = (randint(0,2), randint(0,0), randint(0,0)),
  local-as = diff_axis(arr-set(local-asn), as, 0),
  new-lv = union(lv, locals),
  new-rv = union(rv, locals),
  new-as = union(as, local-as),
  new-ctx = (new-lv:new-rv:new-as:ivs:fs:ret:():0:()),
  new-ctx-throw = (new-lv:new-rv:new-as:ivs:fs:ret:():1:())
::= *5 {
  "{"
#TODO: initialize array!!!
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
? and(islval (ctx), not(in("const", lv-type)))
::= *10 lv-exp " " assign-op() " " expr(ctx, lv-type) ";"
  | *2  plusplus(ctx) ";"

lv-assign _ ::= "; /* lvalue change could be here */"

islval ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx
::= or(neq(len(lv), 0), and(neq(len(as),0), and(neq(len(ivs), 0), eq(ret, "void"))))

lval ctx ? not(islval(ctx)) ::= "lval ERROR!!!"

lval ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(lv), 0)
::= *4 lval1(ctx)
  |    lval2(ctx)
lval ctx ::= lval2(ctx)

lval1 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ::= *4 scal-val(any(lv))

lval2 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx ? and(neq(len(as),0), and(neq(len(ivs), 0), eq(ret, "void")))
::= lval3(ctx)
lval2 ctx ::= lval1(ctx)
lval3 ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx,
  new-arr = any(as),
  (arr-name, arr-type) = new-arr
::= (ivs-val(arr-name, ctx), arr-type)

plusplus ctx ? not(islval(ctx)) ::= "pp ERROR!!!"

plusplus ctx @
  (lv:rv:as:ivs:fs:ret:_) = ctx,
  type-sets = basic-type-sets()
::= anyVarTypes(lv, type-sets) "++"
  | "++" anyVarTypes(lv, type-sets)

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
low-lim ivs @
  type-sets = scalar-type-sets()
::= anyVarTypes(ivs, type-sets) | min-lim() | randint(min-lim(), mid-lim())
big-lim ivs @
  type-sets = scalar-type-sets()
::= anyVarTypes(ivs, type-sets) | max-lim() | randint(mid-lim(), max-lim())
step-pos i  ::= i " += " randint(1,8) | *4 i "++" | *4 "++" i
step-neg1 i ::= i "--" | "--" i
step-neg i  ::= i " -= " randint(1,8) | *8 step-neg1(i)

for-clause (():_) ::= "; /* for-cycle skipped due to no free lvals variables */"

for-clause ctx @
  (lv:rv:as:ivs:fs:ret:old_caf:throw:_) = ctx,
  type-sets = scalar-type-sets(),
  i       = anyTypes(lv, type-sets),
  (i-name, i-type) = i,
  new-lv  = diff(lv,(i,)),
  new-ivs = (i:ivs),
  new-ctx = (new-lv:rv:as:new-ivs:fs:ret:():throw:())
  ? le(len(new-ivs), 3)
::= *10 "for (" i-name "=" low-lim(ivs) "; " i-name " <= " big-lim(ivs) "; " step-pos(i-name)  ") " block(new-ctx)
  | *2  "for (" i-name "=" big-lim(ivs) "; " i-name " > "  low-lim(ivs) "; " step-neg1(i-name) ") " block(new-ctx)


for-clause ctx ::= "; /* for-cycle skipped due to nesting limit */"

# if condition
if-clause ctx
::= "if (" cond(ctx) ") " block(ctx)
  | "if (" cond(ctx) ") " block(ctx) " else " block(ctx)

switch-clause ctx
::= {
    "switch (" type-cast(expr(ctx, "int"), "double", "size_t") ") {"
      switch-cases(int-set(randint(1,5)), ctx)
    "}" }
  | {
    "switch (" type-cast(expr(ctx, "int"), "double", "size_t") ") {"
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
cond ctx @
  type-sets = integer-type-sets(),
  cond-type = any(type-sets)
::= *16 rvalint(ctx)
  | *1 cond(ctx) " " logical-op() " " cond(ctx)
  | *1 "(" cond(ctx) ")"
  | *1 expr(ctx, cond-type) " " relation-op() " " expr(ctx, cond-type)

#TODO: vector support start here
expr ctx T ::= expr-term(ctx, T) expr-T(ctx, T)

#Jie: limit line length by removing expr-T
expr-T ctx T
::= *1 " " binary-op(T) " " expr-term(ctx, T)
  #| *1 " " binary-op(T) " " expr-term(ctx, T) expr-T(ctx, T)
  | *3 ""

expr-term ctx T
::= *24 const(T)
  | *24 rval(ctx, T)
  | *2 unary-expr(ctx, T)
  | *10 try-fun-call(ctx, T)
  | *1 "(" expr(ctx, T) ")"
  | *1 "(" expr(ctx, T) ", " expr(ctx, T) ")"
  #| *1 "(" cond(ctx) " ? " expr(ctx, T) " : " expr(ctx, T) ")"
  #| *1 div-expr(ctx, T)

#Jie: won't try %. That will limit rval data type
div-expr ctx T @
  rv = rval(ctx, T),
  type-sets = scalar-type-sets()
  ? in(T, type-sets)
::= "(" rv "? (" expr(ctx, T) ") / " rv " : (" expr(ctx, T) "))"
#  | "(" rv "? (" expr(ctx, T) ") % " rv " : (" expr(ctx, T) "))"
div-expr ctx T ::= expr-term(ctx, T)

#Jie: Remove cean-get-new-as and cean-get-pre-as. Instead, check array number
isrval ctx @ (lv:rv:as:ivs:fs:ret:_) = ctx
::= or(or(neq(len(rv), 0), neq(len(ivs), 0)), neq(len(as), 0))

rvalint ctx ? not(isrval(ctx)) ::= int()
rvalint ctx @
  type-sets = integer-type-sets(),
  int-type = any(type-sets)
::= rval(ctx, int-type)

#Jie: If no rval can be found, use const instead
#TODO: Support struct rval!!!! lval support for struct is finished by select member of struct
rval ctx T ? not(isrval(ctx)) ::= const(T)

rval ctx T @ (lv:rv:as:ivs:fs:ret:_) = ctx ? neq(len(rv), 0)
::= *100 rval1(ctx, T)
  | *20  rval2(ctx, T)
  | *10  rval3(ctx, T)

rval ctx T ::= rval2(ctx, T)

rval1 ctx T
::= *100 scalar-rval(ctx, T)
  | "copy(" scalar-rval(ctx, T) ")"

rval2 ctx T @ (lv:rv:as:ivs:fs:ret:_) = ctx ? and(neq(len(as),0), neq(len(ivs), 0))
::= *20 array-rval(ctx, T)
  | "copy(" array-rval(ctx, T) ")"
rval2 ctx T ::= rval3(ctx, T)

rval3 ctx T
::= *100 vector-rval(ctx, T)
# | "copy(" vector-rval(ctx, T) ")"

# TODO: unary-op require int type
unary-expr ctx T @
  type-sets1 = integer-type-sets(),
  type-sets2 = integer-vector-type-sets()
  ? or(in(T, type-sets1), in(T, type-sets2))
::= unary-op() " " expr-term(ctx, T)
unary-expr ctx T ::= expr-term(ctx, T)

#TODO: add more scalar rval selection (vec for example)
#TODO: SHOULD STATIC_CAST BE USED?
scalar-rval ctx T @
  (lv:rv:as:ivs:fs:ret:_) = ctx,
  type-sets = scalar-type-sets(),
  v = anyTypes(rv, type-sets)
? neq("EMPTY", v)
::= normal-scalar-rval-cast(v, T)
scalar-rval ctx T ::= rval2(ctx, T)

normal-scalar-rval-cast v T @
  (var-name, var-type) = v
::= type-cast(var-name, var-type, T)


#TODO: add more array rval selection
#TODO: SHOULD STATIC_CAST BE USED?
array-rval ctx T @
  (lv:rv:as:ivs:fs:ret:_) = ctx,
  v = any(as)
::= normal-array-rval-cast(v, T, ctx)
array-rval ctx T ::= "array-rval ERROR!!!"

normal-array-rval-cast v T ctx @
  (array, var-type) = v,
  (aname, adim) = array,
  int-sets = integer-type-sets(),
  float-sets = float-type-sets()
::= type-cast(ivs-val(array, ctx), var-type, T)

vector-rval ctx T @
  (lv:rv:as:ivs:fs:ret:_) = ctx,
  type-sets = vector-type-sets(),
  v = anyTypes(rv, type-sets)
? not(eq("EMPTY", v))
::= normal-vector-rval-cast(v, T)
vector-rval ctx T ::= const(T)

#TODO: randomly use element
normal-vector-rval-cast v T @
  (var-name, var-type) = v
::= type-cast(var-name, var-type, T)


# C operators
# TODO: ! and ~ will change data type
unary-op
::= "-" | "+"
#  | "!" | "~"

#TODO: Add all logical operators
binary-op T
::= *40  binary-cal-op(T)
#  | *3   binary-logical-op(T)
#  |      relation-op()
#  |      logical-op()

binary-cal-op T
::= *20 "+"
  | *8  "-"
  | *6  "*"

binary-logical-op T @
  type-sets = integer-type-sets()
? in (T, type-sets)
::=     "|"
  |     "&"
  |     "^"
binary-logical-op T ::= binary-cal-op(T)

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

# TODO: add binary op
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

scal-val a @
  (a-name, a-type) = a,
  (dummy-type, elems, ptrs) = a-type
? in("struct", a-type)
::= any(elems)
scal-val a ::= a

ivs-val a ctx @ (aname:adim:_) = a ::= aname ivs-val2(adim, ctx)
ivs-val2 0 _ ::= ""
ivs-val2 adim ctx ::= "[" type-cast(ivs-val3(ctx), "double", "size_t") "]" ivs-val2(sub(adim, 1), ctx)
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
  | "((unsigned int)(" expr((lv:rv:as:ivs:fs:ret:():0:()), "int") "))%" array-size()

decl-arr a @
  (array,array-type) = a,
  (aname, adim) = array
::= array-type " " aname decl-arr2(adim) " = {" const(array-type) "};"
decl-arr2 0 ::= ""
decl-arr2 adim ::= "[" array-size() "]" decl-arr2(sub(adim, 1))

try-fun-call ctx T @
  (lv:rv:as:ivs:fs:ret:_) = ctx,
  type-sets = basic-type-sets(),
  f = anyTypes(fs, type-sets)
  ? and(and(neq(len(fs), 0), in(T, type-sets)), neq(f, "EMPTY"))
::= fun-call-cast(f, ctx, T)
try-fun-call ctx T ::= const(T)

fun-call-cast f ctx T @ (fname:ftype:_:_) = f
::= type-cast(fun-call(f, ctx), ftype, T)

fun-call f ctx @ (fname:_:():_) = f ::= fname "()"
fun-call f ctx @ (fname:_:fsig:_) = f, (i:l) = fsig
::= fname "(" expr(ctx, i) fun-call2(l, ctx)  ")"
fun-call2 () _ ::= ""
fun-call2 i:l ctx ::= ", " expr(ctx, i) fun-call2(l, ctx)

decl-fun f @ (fname:ftype:fsig:_) = f ::= ftype " " fname "(" join(", ", fsig) ");"

decl-struct s @
  (sname,stype) = s,
  (s1,elem,p_elem) = stype
::=
{
  "struct " sname " {"
  list-lines(elem, decl-var)
  list-lines(p_elem, decl-var)
  "};"
}

decl-var v @ (vname,vtype) = v ::= vtype " " vname ";"

####################################################################################################
# sets                                                                                             #
####################################################################################################
acc-set            ::= set-gen(acc, global_acc_type, (), 1)
var-set n          ::= set-gen(var, type, (), n)
ptr-set n          ::= set-gen(ptr, type, (), n)
buf-set n          ::= set-gen(buf, buf_type, (), n)
int-set n          ::= set-gen(int, integer_type, (), n)
struct-set n       ::= set-gen(struct, struct_type, (), n)
arr-set l          ::= arr-set2(l, 1)
arr-set2 () _      ::= ()
arr-set2 n:l dim   ::= cat(arr-set-gen(dim, n), arr-set2(l, add(dim, 1)))

fun-var-set param_types ::= set-gen-fun-var(len(param_types), param_types)

fun-set l          ::= fun-set2(l, 0)
fun-set2 () _      ::= ()
fun-set2 n:l arity ::= cat(fun-set-gen(arity, n), fun-set2(l, add(arity, 1)))

set-gen _ _ _ 0 ::= ()
set-gen genf type_foo genf_in n @
  l = set-gen(genf, type_foo, genf_in, sub(n, 1)),
  i = set-uniq(genf(genf_in,), type_foo, l, genf, genf_in)
::= i:l
set-uniq i_var type_foo l genf genf_in @
  lvars = get-vars(l)
  ? in(i_var, lvars)
::= set-uniq(genf(genf_in,), type_foo, l, genf, genf_in)
set-uniq i type_foo _ _ _ @
  var-type = type_foo()
::= (i, var-type)

# WTF? genf(genf_in,) converts list into a string???
arr-set-gen _ 0 ::= ()
arr-set-gen dim n @
  l = arr-set-gen(dim, sub(n, 1)),
  i = arr-set-uniq(arr(dim), l, dim)
::= i:l
arr-set-uniq i l dim @
  lvars = get-vars(l)
  ? in(i, lvars)
::= arr-set-uniq(arr(dim), l, dim)
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

#TODO: need to add support for acc dims
#TODO: Add placeholder
buf-acc-set ()     ::= ()
buf-acc-set n:bufs @
  l = buf-acc-set1(n),
  i = buf-acc-set(bufs)
::= l:i
buf-acc-set1 n @
  (buf-var, buf-type) = n,
  (_, real-type) = buf-type,
  acc-name = (buf-var "_acc", 1)
::= *1 (acc-name, real-type)
  | *1 (acc-name, "const " real-type)

getn 0 _ ::= ()
getn l s ? neq(len(s),0) ::= get(s, 0) : getn(sub(l,1), tail(s))
getn l _ ::= ()

get-vars n @
  (i:l) = n
  ? neq(len(n),0)
::= get-var(i) : get-vars(l)
get-vars n ::= ()
get-var i @
  (v,t) = i
::= v

set-gen-fun-var 0 _ ::= ()
set-gen-fun-var n params @
  (p:ps) = params,
  l = set-gen-fun-var(sub(n, 1), ps),
  i = set-uniq-fun-var(n, p)
::= i:l

set-uniq-fun-var n param @
  var-name = "arg_" n
::= (var-name, param)

####################################################################################################
# some basic stuff                                                                                 #
####################################################################################################
acc _      ::= "result[item.get_global_linear_id()]"
var _      ::= "v_" int() | *1000 "v_" identifier()
ptr _      ::= "p_" int() | *1000 "p_" identifier()
struct _   ::= "struct_" int() | *1000 "struct_" identifier()
buf _      ::= "buf_" int() | *1000 "buf_" identifier()
int _      ::= int()
#TODO: Add more const type definition
const T @ i-types = integer-type-sets() ? in(T, i-types)
::= int()
const T @ f-types = float-type-sets() ? in(T, f-types)
::= T "(" int()"."int() ")"
const T @ v-types = vector-type-sets() ? in(T, v-types)
::= T "(" int() ")"
const T ::= T " const ERROR!!!"

arr dim    ::= "a" dim "_" int(), dim | *1000 "a" dim "_" identifier(), dim
fun arity  ::= "f" arity "_" int(), type(), fun-sig(arity)
             | *1000 "f" arity "_" identifier(), type(), fun-sig(arity)
fun-sig 0 ::= ()
fun-sig arity ::= type() : fun-sig(sub(arity, 1))

int ::= str(randint(1,max-int()))
max-int ::= 100

anyVar vars @
  v = any(vars),
  (var-name, var-type) = v
::= var-name

anyVarTypes vars types @
  v = anyTypes(vars, types),
  (var-name, var-type) = v
::= var-name

cast exp T
::= "cast<" T ">(" exp ")"

# TODO: will cast vector type
# Supported cast: int2double, double2int
type-cast exp expT dstT @
    expT1 = constsub(expT),
    dstT1 = constsub(dstT)
? and(in("const", expT), in("const", dstT))
::= type-cast1(exp, expT1, dstT1)
type-cast exp expT dstT @
    expT1 = constsub(expT)
? in("const", expT)
::= type-cast1(exp, expT1, dstT)
type-cast exp expT dstT @
    dstT1 = constsub(dstT)
? in("const", dstT)
::= type-cast1(exp, expT, dstT1)
type-cast exp expT dstT
::= type-cast1(exp, expT, dstT)

type-cast1 exp expT dstT @
    half-types = "cl_half"
? or(eq(expT, half-types), eq(dstT, half-types))
::= cast(exp, dstT)
type-cast1 exp expT dstT @
    group-types = float-type-sets()
? and(in(expT, group-types), not(in(dstT, group-types)))
::= cast(exp, dstT)
type-cast1 exp expT dstT @
    group-types = integer-type-sets()
? and(in(expT, group-types), not(in(dstT, group-types)))
::= cast(exp, dstT)
type-cast1 exp expT dstT @
    group-types = vector-type-sets()
? and(or(in(expT, group-types), in(dstT, group-types)), neq(expT, dstT))
::= cast(exp, dstT)
type-cast1 exp expT dstT ::= exp

#TODO: Should we support more dims?
buf_type @
  tmp_type = type()
::= ("buffer", tmp_type)

struct_type @
  elem_types = var-set(randint(1,3)),
  ptr_types = ptr-set(randint(0,1))
::= ("struct", elem_types, ptr_types)

ptr_type ::= type() "*"

type
::= *100 scalar_type()
  | *50  vec_type()

scalar_type
::= integer_type()
  | float_type()

integer_type
::= cpp_type()
  | unsigned_cpp_type()
  #| cl_type()
  #| unsigned_cl_type()

cpp_type
::= *24 "int"
  | *4  "long"
  | *2  "long long"
  | *1  "short"
  | *2  "char"

unsigned_cpp_type
::= "unsigned " cpp_type()

cl_type
::= *24 "cl_char"
  | *2  "cl_short"
  | *2  "cl_int"
  | *2  "cl_long"


unsigned_cl_type
::= *24 "cl_uchar"
  | *2  "cl_ushort"
  | *2  "cl_uint"
  | *2  "cl_ulong"

float_type
::= "float"
  | "double"
  #| "cl_double"
  #| "cl_half"
  #| "cl_float"

vec_type ::= vec_elem_type() vec_dims()

vec_elem_type
::= "char" | "short" | "int" | "long" | "float" | "double" | "half"
  #| "cl_char" | "cl_uchar"   | "cl_double" | "cl_half"
  #| "cl_short" | "cl_ushort" | "cl_int" | "cl_uint" | "cl_long" | "cl_ulong" | "cl_float"
  | "schar" | "uchar" | "ushort" | "uint" | "ulong" | "longlong" | "ulonglong"

vec_dims
::= "2" | "3" | "4" | "8" | "16"

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
#TODO: half and double type !
float-type-set ::= "float","double","half"
cpp-integer-type-set ::= "int","long","long long","short","char","unsigned int","unsigned long","unsigned long long","unsigned short","unsigned char"
#cl-integer-type-set ::= "cl_char","cl_short","cl_int","cl_long","cl_uchar","cl_ushort","cl_uint","cl_ulong"

float-type-sets ::= float-type-set()
integer-type-sets ::= cpp-integer-type-set()
scalar-type-sets ::= cat(float-type-set(), integer-type-sets())

int-vector-elem-type-set2 ::= "char2","short2","int2","long2","schar2","uchar2","ushort2","uint2","ulong2","longlong2","ulonglong2"
int-vector-elem-type-set3 ::= "char3","short3","int3","long3","schar3","uchar3","ushort3","uint3","ulong3","longlong3","ulonglong3"
int-vector-elem-type-set4 ::= "char4","short4","int4","long4","schar4","uchar4","ushort4","uint4","ulong4","longlong4","ulonglong4"
int-vector-elem-type-set8 ::= "char8","short8","int8","long8","schar8","uchar8","ushort8","uint8","ulong8","longlong8","ulonglong8"
int-vector-elem-type-set16 ::= "char16","short16","int16","long16","schar16","uchar16","ushort16","uint16","ulong16","longlong16","ulonglong16"

float-vector-elem-type-set2 ::= "float2","double2","half2"
float-vector-elem-type-set3 ::= "float3","double3","half3"
float-vector-elem-type-set4 ::= "float4","double4","half4"
float-vector-elem-type-set8 ::= "float8","double8","half8"
float-vector-elem-type-set16 ::= "float16","double16","half16"

integer-vector-type-sets @
  set1 = cat(int-vector-elem-type-set2(), int-vector-elem-type-set3()),
  set2 = cat(int-vector-elem-type-set4(), int-vector-elem-type-set8())
::= cat(cat(set1, set2), int-vector-elem-type-set16())

float-vector-type-sets @
  set1 = cat(float-vector-elem-type-set2(), float-vector-elem-type-set3()),
  set2 = cat(float-vector-elem-type-set4(), float-vector-elem-type-set8())
::= cat(cat(set1, set2), float-vector-elem-type-set16())

vector-type-sets ::= cat(integer-vector-type-sets(), float-vector-type-sets())

basic-type-sets ::= cat(scalar-type-sets(), vector-type-sets())
