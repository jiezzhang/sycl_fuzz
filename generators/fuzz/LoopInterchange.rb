###############################################################
#                                                             #
#  Intel Compiler Fuzzer for compiler testing                 #
#                                                             #
#  rInterchange generates a random test for loop interchange  #
#                                                             #
#  Author: Mohammad R. Haghighat, Intel Corporation           #
#                                                             #
#  History:                                                   #
#     December 10, 2008 : Creation                            #
#                                                             #
#                                                             #
###############################################################

AOP =   ['=', '+=', '-=']
AOP_D = [  3,    1,    1]
AOP_rNdx = $ICF.rNdx(AOP_D)

def rInterchange

    return rStmt if more(false) <= 3 or tooDeep

    maxStmt = 1+(2*@MAX_FOR_S/3).to_i

    @LN += 1
    iv1 = lpVar
    n1 = trips(@LN)
    s1 = start(n1)

    stmt  = "\n" + tab + "// Test Loop Interchange\n"
    stmt += For(iv1, s1.to_s, n1.to_s)
    forPre
   
    @LN += 1
    iv2 = lpVar
    n2 = trips(@LN)
    s2 = start(n2)

    stmt += For(iv2, s2.to_s, n2.to_s)
    forPre

    stmt += tab + rArrExp(5) + " " + AOP[wrand(AOP_rNdx)] + " " + rExp + ";\n"

    stmt += forPost(iv1)
    stmt += forPost(iv2)

    return stmt
end
   
addExtension("rInterchange")
