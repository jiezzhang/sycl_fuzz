require 'icfuzz.rb'

P_CPRED = 50 
PRED_F = 4

def rPredicate
    k = ((@MAX_TRIPC)/PRED_F).to_i
    if ((rand(100) < P_CPRED) or (@LV.size <= 1))  
       n = rand(k).to_s 
    else
       k = (k/2).to_i
       n = @LV[rand(@LV.size-1)] 
       if (k != 0)
          n += ['+', '-'][rand(2)] 
          n += k.to_s
       end
    end
    s =  tab + "// Test Loop Predication" 
    s += rIf(@LV[-1] + " " + rRl + " " + n) 
    return s
end
   
$ICF.addLoopStmt("rPredicate")
