####################################################################
#                                                                  #
#  Intel Compiler Fuzzer for compiler testing                      #
#                                                                  #
#  rPointerSeq generates a random sequence of pointer assignments  #
#                                                                  #
#  Author: Mohammad R. Haghighat, Intel Corporation                #
#                                                                  #
#  History:                                                        #
#     December 20, 2008 : Creation                                 #
#                                                                  #
#                                                                  #
####################################################################

MAX_PTRS = 5

PTR_OP = [["rPAssign('=')",  4],
          ["rPAssign('+=')", 3],
          ["rPAssign('-=')", 2],
          ["rPAssign('*=')", 1]
         ]
PTR_OP_rNdx = rNdx2(PTR_OP)

def rPointerSeq(numStmts=MAX_PTRS)
    return rStmt if more(false) < 2
    s  = "\n" + tab + "// Test Pointer Intensiveness" 
    n = 1+mrand(numStmts)
    n.times { 
        s += "\n" + rPDef                    if (prob 50) and (more >= 0)
        s += "\n" + eval(wrand(PTR_OP_rNdx)) if (prob 50) and (more >= 0)
    }
    s += "\n"
    return s
end
   
addExtension("rPointerSeq")
