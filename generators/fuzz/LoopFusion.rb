###########################################################
#                                                         #
#  Intel Compiler Fuzzer for compiler testing             #
#                                                         #
#  rFusion generates a random test for loop fusion        #
#                                                         #
#  Author: Mohammad R. Haghighat, Intel Corporation       #
#                                                         #
#  History:                                               #
#     December 10, 2008 : Creation                        #
#                                                         #
#                                                         #
###########################################################

def rFusion

    return rStmt if more(false) <= 4 or tooDeep

    maxStmt = 1+(@MAX_FOR_S/2).to_i

    @LN += 1
    iv = lpVar
    n = trips(@LN)
    s = start(n)
    d = rStep

    stmt  = "\n" + tab + "// Test Loop Fusion\n"
    stmt += For(iv, s.to_s, n.to_s, d)
    forPre
    stmt += rSeq(maxStmt)
    stmt += forPost(iv)

    @LN += 1
    iv = lpVar
    stmt += For(iv, s.to_s, n.to_s, d)
    forPre
    stmt += rSeq(maxStmt)
    stmt += forPost(iv)

    return stmt
end
   
addExtension("rFusion", 0.5)
