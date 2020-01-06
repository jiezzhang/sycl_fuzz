###########################################################
#                                                         #
#  Intel Compiler Fuzzer for compiler testing             #
#                                                         #
#  rVectorization generates a random test for vectorizer  #
#                                                         #
#  Author: Mohammad R. Haghighat, Intel Corporation       #
#                                                         #
#  History:                                               #
#     December 25, 2008 : Creation                        #
#                                                         #
#                                                         #
###########################################################

###     [rNum rLit rExp rArr -rArr rOP2] 
VOP_D = [   3,   2,   1,   2,    2,   3]
VOP_rNdx = $ICF.rNdx(VOP_D)

P_RED = 30

def rVectorization

    return rStmt if tooDeep

    numVS = 1+mrand(@MAX_FOR_S/2)

    @LN += 1
    iv = lpVar
    n = trips(@LN)
    s = start(n)
    d = rStep

    stmt  = "\n" + tab + "// Test Loop Vectorization\n"
    stmt += For(iv, s.to_s, n.to_s, d)
    forPre

    numVS.times {
       break if more < 0
       vec =  rArrExp(1) + " "
       vec += rOp2 if prob P_RED
       vec += "= " 
       n = wrand(VOP_rNdx)
       case n
       when 0
          vec += mrand(@MAX_NUM).to_s
       when 1
          vec += rLit
       when 2
          vec += rExp
       when 3
          vec += rArrExp(1)
       when 4
          vec += "-" + rArrExp(1)
       when 5
          vec += rArrExp(1) + " " + rOp2 + " " + rArrExp(1) 
       else
          return fatal("rVectorization", ": n = " + n)
       end
       stmt += tab + vec + ";\n"
    }

    stmt += forPost(iv)

    return stmt
end
   
addExtension("rVectorization", 2)
