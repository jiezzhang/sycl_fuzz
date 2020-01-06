#############################################################
#                                                           #
#  Intel Compiler Fuzzer for compiler testing               #
#                                                           #
#  rPredicate generates a random test for loop predication  #
#                                                           #
#  Author: Mohammad R. Haghighat, Intel Corporation         #
#                                                           #
#  History:                                                 #
#     December 10, 2008 : Creation                          #
#                                                           #
#                                                           #
#############################################################

P_CPRED = 50 
PRED_F = 4

def rPredicate

    return rStmt if more(false) <= 2 or tooDeep

    k = ((@MAX_TRIPC)/PRED_F).to_i
    if ((prob P_CPRED) or (@LV.size <= 1))  
       n = mrand(k).to_s 
    else
       k = (k/2).to_i
       n = @LV[mrand(@LV.size-1)] 
       if (k != 0)
          n += ['+', '-'][mrand(2)] 
          n += k.to_s
       end
    end
    s  = "\n" + tab + "// Test Loop Predication" 
    s += rIf(@LV[-1] + " " + rRl + " " + n) 

    return s
end
   
addLoopExtension("rPredicate")
