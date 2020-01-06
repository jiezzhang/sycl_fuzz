########################################################################
#                                                                      #
#  Intel Compiler Fuzzer for compiler testing                          #
#                                                                      #
#  rCSE generates a random sequence of statements with CSE potentials  #
#                                                                      #
#  Author: Mohammad R. Haghighat, Intel Corporation                    #
#                                                                      #
#  History:                                                            #
#     January 20, 2009 : Creation                                      #
#                                                                      #
#                                                                      #
########################################################################

MAX_CSE_STMT = 3
MAX_CSE_EXPR = 2
P_CSE = 60
P_PTR = 20

CSE_PTR_OP = [["rPAssign('=')",  4],
              ["rPAssign('+=')", 3],
              ["rPAssign('-=')", 2],
              ["rPAssign('*=')", 1]
             ]
CSE_PTR_OP_rNdx = rNdx2(CSE_PTR_OP)

def rCSE
    return rStmt if more(false) < 2

    # Prevent exprs with side effects 
    @NOPP += 1

    s  = "\n" + tab + "// Test CSE\n" 
    n = 1 + mrand(MAX_CSE_STMT)
    e = rExp
    s += tab + dVar + " = " + e + ";\n"
    n.times { 
        s += rPDef + "\n"                        if (prob P_PTR) and (more >= 0)
        break if more < 0
        s += tab + dVar + " = (" + e + ")" 
        m = 1 + mrand(MAX_CSE_EXPR)
        m.times {
            s += " " + rOp2 + " (" + ((prob P_CSE) ? e : rExp) + ")"
        }
        s += ";\n"
        break if more < 0
        s += eval(wrand(CSE_PTR_OP_rNdx)) + "\n" if (prob P_PTR) and (more >= 0) 
    }

    # Now, allow exprs with side effects 
    @NOPP -= 1

    return s
end
   
addExtension("rCSE", 0.5)
