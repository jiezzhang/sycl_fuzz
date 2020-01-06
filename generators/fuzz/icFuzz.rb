###########################################################
#                                                         #
#  icFuzz:  Intel Compiler Fuzzer for compiler testing    #
#                                                         #
#  Author: Mohammad R. Haghighat, Intel Corporation       #
#                                                         #
#  History:                                               # 
#     November 15, 2008 : Creation                        # 
#                                                         #
#                                                         #
###########################################################

class Fuzzer   

   def initialize
   
       @MAX_S = 16
       @MAX_IF_S = 4
       @MAX_EL_S = 4
       @MAX_FOR_S = 5
       @MAX_LN = 4
       @MAX_FORINC = 3
       @MAX_TRIPC = 100 
       @MAX_VLEN = 3 
       @MAX_NUM_INIT = 100
       @MAX_NUM = 100
       @MAX_ARR_INIT = 100 
       @MAX_ARR_DIM = 2 
       @MAX_P_VREUSE = 90    # do not increase this parameter above 90
       @P_FOR_UP = 75
       @P_VDIG = 30
       @P_VREUSE = 60 
       @P_VUSE = 75 
       @P_ELSE = 50 
       @P_TRIANG = 30
       @P_LIVE_OUT = 20 
       @START_FRAC = 16 
       @VREUSE_INC = 20      # percentage of increase of reuse inside loops
       @AUTO_WEIGHT = true
       @AUTO_FACTOR = 0.5    # must be <= 1.0 

       @MAX_TRIPNM = 'N' 
       @INIT = 'INIT'
       @INITC = 'init'
       @CHECK = 'CS'
       @CHECKC = 'checkSum'
       @RES = 'res'
       @RAND = 'rand()'
       @SRAND = 'srand'
       
       @OP   = []
       @OP_D = []
       @OP_rNdx = []
       
       #         neg  pre   post   pre  post  deref
       @OP1 =   ['-', '++', '++', '--', '--',  '*']
       @OP1_D = [  4,   10,    8,    8,   10,   30]
       @OP1_rNdx = []
       
       @OP2   = ['+', '-', '*']
       @OP2_D = [ 40,  30,  20]
       @OP2_rNdx = []
       
       @OP2s   = ['/', '%']
       #@OP2s_D = [  3,   3]
       @OP2s_D = [0, 0]
       @OP2s_rNdx = []

       @OPArr   = ['[j-1]', '[j]', '[j+1]']
       @OPArr_D = [ 50,  60,  40]
       #@OPFor_D = [  0,   5,   0]
       
       #           VV  EV  VE  EE  
       @OPRND_D = [50, 20, 20, 10]
       @OPRND_D_rNdx = []

       @XDW = 16	# extension default weight
       @XSF = 2		# extension scale-down factor 

       @SSTMT_D = [["rAssign('=')",  40, 0],
                   ["rAssign('+=')", 20, 0],
                   ["rAssign('-=')", 16, 0],
                   ["rAssign('*=')",  8, 0],
                   ["rPAssign('=')",  8, 0],
                   ["rPAssign('+=')", 8, 0],
                   ["rPAssign('-=')", 8, 0],
                   ["rPAssign('*=')", 8, 0],
                   ["rPDef",          8, 0],
                   ["rIf",           32, 0],
                   ["rFor",          40, 0]
                  ] 
       @SSTMT_D_rNdx = []

       @LSTMT_D = [["rAssign('=')",  32, 0],
                   ["rAssign('+=')", 32, 0],
                   ["rAssign('-=')", 32, 0],
                   ["rAssign('*=')", 16, 0],
                   ["rPAssign('=')",  4, 0],
                   ["rPAssign('+=')", 4, 0],
                   ["rPAssign('-=')", 4, 0],
                   ["rPAssign('*=')", 4, 0],
                   ["rPAssign",       4, 0],
                   ["rPDef",          4, 0],
                   ["rIf",           16, 1.5],
                   ["rFor",          20, 2] 
                  ]
       @LSTMT_D_rNdx = []

       #           scalar  array 
       @SVTYPE_D = [    6,    2] 
       @SVTYPE_rNdx = []
       
       #           scalar  array 
       @LVTYPE_D = [    2,    6] 
       @LVTYPE_rNdx = []

       #
       @LP_PRE =   ['i', 'j', 'k']  
       @LP_PRE_D = [ 2,   4,   3]  
       @LP_PRE_rNdx = []

       @FOR_INC   = [-1, 0, 1]
       @FOR_INC_D = [ 2, 1, 4]
       @FOR_INC_rNdx = []
       
       @TYPE = ['int', 'double', 'char', 'float']
       
       @VAR = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
               'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
       
       @DIGIT = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
       
       @RL = ['==', '!=', '<', '<=', '>', '>=']
       
       @KW = [@CHECKC, @INITC, @MAX_TRIPNM, @RES, 
              'break', 'class', 'continue', 'do', 'double', 'char', 'else', 
              'exit', 'float', 'for', 'goto', 'if', 'int', 'long', 'main', 
              'repeat', 'return', 'short', 'signed', 'template', 'until', 
              'unsigned', 'while']
       
       @AV = []
       @AVArr = []
       @AVPtr = []
       @TAB = 1
       @TABN = 4
       @TABC = ' ' * @TABN
       @NOPP = 0
       @NPTR = 0
       @PP = [] 
       @LV = []
       @LVall = []
       @LN = 0
       @LFOR = []
       @LREUSE = []
       $NUMS = @MAX_S 
  
       # initializations 

       @MAX_TRIPC = maxTripCount
    
       @OP = @OP1 + @OP2 + @OP2s
       @OP_D = @OP1_D + @OP2_D + @OP2s_D
   
       @OP_rNdx   = rNdx(@OP_D) 
       @OP1_rNdx  = rNdx(@OP1_D) 
       @OP2_rNdx  = rNdx(@OP2_D) 
       @OP2s_rNdx = rNdx(@OP2s_D) 
       @OPArr_rNdx = rNdx(@OPArr_D) 
       #@OPFor_rNdx = rNdx(@OPFor_D) 
       @OPRND_D_rNdx  = rNdx(@OPRND_D)  
       @SVTYPE_rNdx = rNdx(@SVTYPE_D)
       @LVTYPE_rNdx = rNdx(@LVTYPE_D)
       @LP_PRE_rNdx = rNdx(@LP_PRE_D)
       @FOR_INC_rNdx = rNdx(@FOR_INC_D)

       @VTYPE_rNdx = @SVTYPE_rNdx 

       getStmtTable
       @SPTYPES = getW(@SSTMT_D)
       @LPTYPES = getW(@LSTMT_D)

       @OP_D_SUM   = eval(@OP_D.join("+"))
       @OP1_D_SUM  = eval(@OP1_D.join("+"))
       @OP2_D_SUM  = eval(@OP2_D.join("+"))
       @OP2s_D_SUM = eval(@OP2s_D.join("+"))
       @OPArr_D_SUM = eval(@OPArr_D.join("+"))
   
       @EXP_rNdx = rNdx([@OP1_D_SUM, @OP2_D_SUM, @OP2s_D_SUM, @OPArr_D_SUM])
   
   end

   def prob x
       return mrand(100) <= x
   end

   def maxTripCount
       return @MAX_TRIPC if @MAX_S <= 1 
       n = (10000 / @MAX_S).to_i
       n = 10 if n < 10
       n = @MAX_TRIPC if @MAX_TRIPC < n
       return n 
   end

   def fatal(f="", msg="")
       puts "internal error in #{f} #{msg}"
       exit
   end

   def mrand(n=0)
       r = rand(n)
       r = 0 if r < 1
       return r
   end

   def autoWeight(aw=true)
       @AUTO_WEIGHT = aw
   end 

   def getW(list)
       pt = []
       w = 0
       list.each {
          |s|
          w += s[1]
          pt << s 
       }
       return [pt, w] 
   end

   def loc(s, list)
       list.each {
          |e|
          return e if e[0] == s
       }
       return nil
   end
 
   def adjustW(list,ref)
       wlist = list[1]
       wref = ref[1]
       return if (wref == 0) or (wlist <= wref)
       r = @AUTO_FACTOR * ((wlist+0.0)/(wref+0.0)-1.0)
       l = ref[0]
       ls = list[0]
       l.each {
          |s|
          e = loc(s[0], ls)
          next if e == nil
          e[1] = (e[1]*(1+r)).to_i
       }
   end

   def xWeight
       return @XDW
   end 

   def updateSSTMT
       @SSTMT_D_rNdx = rNdx2(@SSTMT_D)
   end

   def updateLSTMT
       @LSTMT_D_rNdx = rNdx2(@LSTMT_D)
   end

   def updatetStmtTable
       updateSSTMT
       updateLSTMT 
   end 

   def getStmtTable
       updatetStmtTable
       @STMT_D_rNdx = @SSTMT_D_rNdx
   end 


   def addStmt(s, w=1, f=1)
       wi = (w*@XDW + 0.5).to_i
       fi = (f*@XSF + 0.5).to_i
       @SSTMT_D += [[s, wi, fi]]
       @LSTMT_D += [[s, wi, fi]]
       getStmtTable
   end

   def del(list, s)
       list.each {
          |e|
          next if (e[0] != s) 
          w = e[1]  
          list -= [[s, w]] 
       } 
       return list 
   end

   def del1(list, s)
       list.each {
          |e|
          next if (e[0] != s) 
          w = e[1]  
          list -= [[s, w]] 
          return list 
       } 
       return list 
   end

   def delStmt(s)
       @SSTMT_D = del(@SSTMT_D, s)
       @LSTMT_D = del(@LSTMT_D, s)
       getStmtTable
   end

   def del1Stmt(s)
       @SSTMT_D = del1(@SSTMT_D, s)
       @LSTMT_D = del1(@LSTMT_D, s)
       getStmtTable
   end

   def addLoopStmt(s, w=1, f=1)
       wi = (w*@XDW + 0.5).to_i
       fi = (f*@XSF + 0.5).to_i
       @LSTMT_D += [[s, wi, fi]]
       getStmtTable
   end

   def delLoopStmt(s)
       @LSTMT_D = del(@LSTMT_D, s)
       getStmtTable
   end

   def del1LoopStmt(s)
       @LSTMT_D = del1(@LSTMT_D, s)
       getStmtTable
   end

   def addScalarStmt(s, w=1, f=1)
       wi = (w*@XDW + 0.5).to_i
       fi = (f*@XSF + 0.5).to_i
       @SSTMT_D += [[s, wi, fi]]
       getStmtTable
   end

   def delScalarStmt(s)
       @SSTMT_D = del(@SSTMT_D, s)
       getStmtTable
   end

   def del1ScalarStmt(s)
       @SSTMT_D = del1(@SSTMT_D, s)
       getStmtTable
   end
    
   def min(list)
       return nil if list == nil
       x = list[0]
       list.each {
          |e|
          x = e if e < x
       }
       return x
    end
 
   def rType
       return @TYPE[mrand(@TYPE.size)]
   end	
   
   def rDigit
       return @DIGIT[mrand(@DIGIT.size)]
   end	
   
   def rChar
       return @VAR[mrand(@VAR.size)]
   end	
   
   def rNdx(list)
       res = []
       j = 0
       list.each do |e|
          if (e > 0) 
             e.times { res += [j] }
          end
          j = j + 1
       end
       return res
   end

   def rNdx2(list)
       res = []
       list.each do |t|
          e = t[1]
          if (e > 0) 
             e.times { res += [t[0]] }
          end
       end
       return res
   end
   
   def wrand(list)
       return list[mrand(list.size)]
   end
   
   def rOp
       return @OP[wrand(@OP_rNdx)]
   end	
   
   def rOp2
       return @OP2[wrand(@OP2_rNdx)]
   end	
   
   def rOp2s
       return @OP2s[wrand(@OP2s_rNdx)]
   end	
   
   def rRl
       return @RL[mrand(@RL.size)]
   end	
   
   def tab
       res = ""
       @TAB.times { res += "    " }
       return res
   end
   
   def iVar(iChar)
       while true 
          n = mrand(@MAX_VLEN-1)
          v = iChar
          v = rChar if v == nil
          n.times { v += rChar }
          v += rDigit if prob @P_VDIG 
          next if (@PP.member? v) 
          break if !(@KW.member? v) 
   
        end
   
       return v 
   end	

   def rVar
       return iVar(nil)
   end
   
   def arrVar(n)
       while true 
          if ((prob @P_VREUSE) and (@AVArr.size > 0)) 
             v = @AVArr[mrand(@AVArr.size)]
             next if (v[1] != n)
          else
             v = [rVar, n]
             next if memberOf([@AV, @LVall, @AVArr, @AVPtr], v[0])
             @AVArr << v if !(@AVArr.member? v)
          end
          break
       end
  
       return v[0]
   end 

   def dPtr
       while true
          if ((prob @P_VREUSE) and (@AVPtr.size > 0)) 
             v = @AVPtr[mrand(@AVPtr.size)]
          else
             v = iVar("p")
             next if memberOf([@AV, @LVall, @AVArr], v)
             @AVPtr << v if !(@AVPtr.member? v)
          end
          break
       end
   
       return v
   end 

   def rPtr
       @NPTR += 1
       return "*" + dPtr 
   end

   def arrDim(n=0)
       if n > 0
          if (n <= @LN) and (n <= @MAX_ARR_DIM)
             return n
          else
             return @LN <= @MAX_ARR_DIM ? @LN : @MAX_ARR_DIM
          end
       end

       n = @LN 
       n = @MAX_ARR_DIM if (n > @MAX_ARR_DIM)
       n = mrand(1+n)
       n = 1 if (n < 1)
       return n
   end

   def rArrExp(n=0)
       return (arrVar(1) + "[" + mrand(@MAX_TRIPC-1).to_s + "]") if @LN == 0

       s = []
       j = @LV.size-1
       n = arrDim(n) 
       n.times {
          s << @LV[j]
          j -= 1 if (j > 0)
       }
       ndx = ""
       n.times {
          j = s[mrand(s.size)]
          x = wrand(@OPArr_rNdx)
          case x 
          when 0 
             j += "-1"
          when 1 
          when 2 
             j += "+1"
          else
             return fatal("rArrExp", ": x = " + x) 
          end
          ndx += "[" + j + "]" 
       }
       
       return arrVar(n) + ndx
   end

   def dScalarVar
       while true
          if ((prob @P_VREUSE) and (@AV.size > 0)) 
             v = @AV[mrand(@AV.size)]
             next if memberOf([@LVall, @AVArr, @AVPtr], v)
          else
             v = rVar
             next if memberOf([@LVall, @AVArr, @AVPtr], v)
             @AV << v if !(@AV.member? v)
          end
          break
       end
   
       return v
   end 

   def dVar
       n = wrand(@VTYPE_rNdx)
       case n 
       when 0 
          return dScalarVar 
       when 1 
          return rArrExp 
       else
          return fatal("dVar", ": n = " + n) 
       end
   end

   def memberOf(aL, v)
       if aL
          aL.each do |l|
             next if l == nil
             return true if l.member? v
             l.each do |e|
                return true if e.member? v
             end 
          end
       end
       return false
   end

   def bVar(iC, bL, aL)
   
       while true
          v = iVar(iC)
          next if memberOf(aL, v) 
          break if !(bL.member? v) 
       end 
   
       bL << v
   
       return v 
   end	
   
   def ppVar
       v = bVar("n", @PP, [@AV, @AVArr, @AVPtr])
       @AV << v
       return v
   end
  
   def lpPre
       return @LP_PRE[wrand(@LP_PRE_rNdx)]
   end
 
   def lpVar
       v = bVar(lpPre, @LV, [@AV, @AVArr, @AVPtr])
       @AV << v
       @LVall << v if !(@LVall.member? v) 
       return v 
   end
   
   def rLit
       while true
          if ((prob @P_VUSE) and (@AV.size > 0))
             v = @AV[mrand(@AV.size)]
             next if @PP.member? v 
          else
             v = mrand(@MAX_NUM).to_s
          end
          break
       end
   
       return v 
   end
   
   def rASM
       n = wrand(@OPRND_D_rNdx)
       case n 
       when 0 
          return rLit + " " + rOp2 + " " + rLit
       when 1 
          return "(" + rExp + ") " + rOp2 + " " + rLit
       when 2 
          return rLit + " " + rOp2 + " (" + rExp + ")" 
       when 3 
          return "(" + rExp + ")" + " " + rOp2 + " (" + rExp + ")" 
       else
          return fatal("rASM", ": n = " + n) 
       end
   end
   
   def nZ(e)
       return "((" + e + " != 0) ? " + e + " : 1)"
   end
   
   def rDM
   
       @NOPP += 1
   
       n = wrand(@OPRND_D_rNdx)
       case n 
       when 0 
          res = rLit + " " + rOp2s + " " + nZ(rLit) 
       when 1 
          res = "(" + rExp + ") " + rOp2s + " " + nZ(rLit) 
       when 2 
          res = rLit + " " + rOp2s + " " + nZ(rExp)
       when 3 
          res = "(" + rExp + ") " + rOp2s + " " + nZ(rExp)
       else
          res = nil 
          return fatal("rDM", ": n = " + n) 
       end
   
       @NOPP -= 1
   
       return res
   end
   
   def rUni
   #
   #   avoid pre- and post increments in division and remainder operations
   #  
   
       n = wrand(@OP1_rNdx)
       case n 
       when 0 
          return "-(" + rExp + ")" 
       when 1 
          return rExp if (@NPTR > 0) or (@NOPP > 0)
          return "++" + ppVar 
       when 2 
          return rExp if (@NPTR > 0) or (@NOPP > 0)
          return ppVar + "++" 
       when 3 
          return rExp if (@NPTR > 0) or (@NOPP > 0)
          return "--" + ppVar
       when 4 
          return rExp if (@NPTR > 0) or (@NOPP > 0)
          return ppVar + "--" 
       when 5 
          return rExp if (@PP.size > 0)
          return rPtr 
       else
          return fatal("rUni", ": n = " + n) 
       end
   end
   
   def rExp
       n = wrand(@EXP_rNdx)
       case n 
       when 0 
          return rUni 
       when 1 
          return rASM
       when 2 
          return rDM
       when 3 
          return rArrExp
       else
          return fatal("rExp", ": n = " + n) 
       end
   end
   
   def rPDef 
       lhs = dPtr
       while true
          if ((prob @P_VREUSE) and (@AVPtr.size > 0)) 
             rhs = @AVPtr[mrand(@AVPtr.size)]
             next if lhs == rhs 
          else
             rhs = "&" + rPtrExp 
          end
          break 
       end
   
       return tab + lhs + " = " + rhs + ";" 
   end 

   def rPtrExp
       s = @AV - @LVall
       n = mrand(s.size + @AVArr.size)
       return s[n] if n < s.size
       return rArrExp 
   end
   
   def rPAssign(op='=')
       return tab + rPtr + " " + op + " " + rExp + ";"
   end
   
   def rAssign(op='=')
       return tab + dVar + " " + op + " " + rExp + ";"
   end
   
   def rCond
       return rExp + " " + rRl + " " + rExp
   end
   
   def rIf(c=rCond)
       return rStmt if more(false) < 1
       s = "\n" + tab + "if (" + c + ") {\n"
       @TAB += 1
       s += rSeq(@MAX_IF_S)
       @TAB -= 1
       s += tab + "}"
       if ((prob @P_ELSE) and more(false) > 0) 
          s += " else {\n" 
          @TAB += 1
          s += rSeq(@MAX_EL_S)
          @TAB -= 1
          s += tab + "}"
       end
       s += "\n"
       return s
   end
  
   # return a loop stop value; at most @MAX_TRIPC-3 
   def constTrips(d)
       n = mrand(@MAX_TRIPC-2)
       (d-1).times { n = n/2 }
       n = 0 if (n < 1)
       return n
   end
   
   # return a loop start value; at least 1 
   def constStart(n)
       f = @START_FRAC
       f = 1 if f < 0
       s = mrand(n.to_i/f) 
       s = 1 if (s < 1)
       return s
   end

#
#  We cannot have j+1 and j-1 in loop bounds until range checks are in place
#
#  def rForExp
#      return nil if @LN <= 1
#      v = @LV[mrand(@LN-1)]
#      x = wrand(@OPFor_rNdx)
#      case x 
#      when 0 
#         v += "-1"
#      when 1 
#      when 2 
#         v += "+1"
#      else
#         return fatal("rArrExp", ": x = " + x) 
#      end
#      
#      return v 
#  end

   def rForExp
       return nil if @LN <= 1
       return @LV[mrand(@LN-1)]
   end

   def trips(n)
       return constTrips(n) if @LN <= 1
       return rForExp if prob @P_TRIANG
       return constTrips(n)
       
   end

   def start(n)
       return constStart(n) if @LN <= 1
       return rForExp if prob @P_TRIANG
       return constStart(n)
   end

   def pushFor
       w = [] 
       @LSTMT_D.each {
          |e|
          next if e[2] == 0 
          w << e[1] 
          n = (e[1]/e[2]).to_i
          n = 1 if n < 1 and n != 0
          e[1] = n 
       } 
       @LFOR << w 
       updateLSTMT 

       @LREUSE << @P_VREUSE
       @P_VREUSE = (@P_VREUSE * (1 + @VREUSE_INC/100.0)).to_i
       @P_VREUSE = @MAX_P_VREUSE if @P_VREUSE > @MAX_P_VREUSE
   end

   def popFor
       w = @LFOR.delete_at(-1) 
       j = 0 
       @LSTMT_D.each {
          |e|
          next if e[2] == 0 
          e[0] = e[0] 
          e[1] = w[j] 
          e[2] = e[2] 
          j += 1
       } 
       updateLSTMT 

       @P_VREUSE = @LREUSE.delete_at(-1)
   end

   def forPre
       @TAB += 1
       if @LN == 1
          @VTYPE_rNdx = @LVTYPE_rNdx 
          @STMT_D_rNdx = @LSTMT_D_rNdx
       else
          pushFor 
       end
   end
   
   def forPost(iv)
       @TAB -= 1
       if @LN == 1
          @VTYPE_rNdx = @SVTYPE_rNdx 
          @STMT_D_rNdx = @SSTMT_D_rNdx
       else
          popFor
       end
       @LN -= 1
       @LV -= [iv]
       return tab + "}" + "\n"
   end

   def rStep
       step = @FOR_INC[wrand(@FOR_INC_rNdx)]
       step = 1+mrand(@MAX_FORINC) if step == 0
       step = -step if not prob @P_FOR_UP
       return step
   end

   def For(iv, st, stp, step=0)
       if step == 0
          step = rStep 
       end

       if step > 0
          inc = (step ==  1) ? "++" : " += " + step.to_s
          cmp = " < "
          first = st
          last = stp
       else
          # Would be wrong: inc = (step == -1) ? "--" : " -= " + (-step).to_s
          inc = '--'
          cmp = " > "
          first = stp
          last = st
       end

       if (inc == '++') or (inc == '--') 
          ivinc = (prob 50) ? iv + inc : inc + iv
       else
          ivinc = iv + inc
       end

       s =  tab +
           "for (" + 
                 iv + " = " + first + "; " + 
                 iv +  cmp  + last  + "; " +
                 ivinc +
               ") {\n"

       return s
   end

   def tooDeep
       return @LN >= @MAX_LN
   end
   
   def rFor
       return "" if tooDeep
       @LN += 1
       iv = lpVar
       n = trips(@LN)
       s = start(n)
       stmt = "\n"
       stmt += For(iv, s.to_s, n.to_s)
       forPre
       stmt += rSeq(@MAX_FOR_S)
       stmt += forPost(iv)
       return stmt
   end

   def stmtPre
       @PP = []
       @NPTR = 0
   end
   
   def rStmt
       stmtPre 
       return eval(wrand(@STMT_D_rNdx)) 
   end
   
   def num1(n)
       k = mrand(n+1)
       k = mrand(n+1) if k == 0
       k = mrand(n+1) if k == 0
       return k
   end

   def rSeq(n)
       n = num1(n)
       res = "" 
       n.times { 
          res += rStmt + "\n" 
          break if more <= 0
       }
       return res
   end

   def arrSize(d)
       s = @MAX_TRIPNM
       (d-1).times { s += "*" + @MAX_TRIPNM }
       return s 
   end

   def rPtrInit
       s = @AV - @LVall
       nvars = s.size + @AVArr.size 
       return dScalarVar if nvars == 0 
       n = mrand(nvars)
       return s[n] if n < s.size
       arr = @AVArr[mrand(@AVArr.size)]
       a = arr[0]
       arr[1].times { a += "[" + mrand(@MAX_TRIPC).to_s + "]" }
       return a
   end

   def ptrDecls
       n = @AVPtr.size
       return "" if (n == 0)
       ptrs = tab + "unsigned int "
       @AVPtr.each do |v|
           n -= 1
           ptrs += "*" + v + "=&" + rPtrInit
           ptrs += ', ' if (n > 0)
       end
       ptrs += ";\n\n"
       return ptrs 
   end
   
   def arrDecls(pdecls="")
       n = @AVArr.size
       return pdecls if (n == 0)
       initVars = tab + "unsigned int "
       inits = ""
       @AVArr.each do |v|
           n -= 1
           a = v[0]
           v[1].times { a += "[N]" }
           a += " = {0}"
           initVars += a
           initVars += ', ' if (n > 0)
           inits += tab + @INIT + " (" + v[0] +
                    ", " + arrSize(v[1]) + ", " +
                    (1+mrand(@MAX_ARR_INIT-1)).to_s + ");\n"
       end
       initVars += ";\n\n"
       return initVars + pdecls + inits + "\n"
   end
 
   def decls
       f = File.open("input.txt", "w")
       pdecls = ptrDecls 
       initVars = tab + "unsigned int "
       fmt = "" 
       vars = ""
       n = 0
       @AV.each do |v|
           if n == 0
              vars = '&' + v
              fmt = "%u"
           else
              vars = vars + ", &" + v
              fmt += " %u"
           end 
           val = mrand(@MAX_NUM_INIT)
           f.puts val
           initVars += v + "=" + val.to_s + ", " 
           n = n + 1
       end
       initVars += @RES + "=" + mrand(@MAX_NUM_INIT).to_s + ";\n\n"
       initVars += arrDecls(pdecls) 
       res = initVars
       if (n > 0 )
          res += tab + 'scanf ("' + fmt + '", ' + vars + ");\n\n"
       end
   
       f.close
   
       return res 
   end

   def arrRes
       res = tab + @RES + " += "
       op = [' + ', ' - ']
       j = 0

       if (@AVArr.size == 1)
          v = @AVArr[0]
          return res + @CHECK + " (" + v[0] + ", " + arrSize(v[1]) + ");\n"
       end

       n = @AVArr.size
       s = @TABN + 4 + @RES.size
       @AVArr.each do |v|
           n -= 1
           if n > 0
              str = @CHECK + " (" + v[0] + ", " + arrSize(v[1]) + ")" + op[j]
           else
              str = @CHECK + " (" + v[0] + ", " + arrSize(v[1]) + ")" + ";\n"
           end
           if (s+str.size < 80)
              res += str
              s += str.size
           else
              res += "\n" + tab + ' ' * (@RES.size+4) + str
              s = str.size + @TABN + 4 + @RES.size
           end
           j = 1 - j
       end
       return res
   end
   
   def getres
       res = "\n" + tab + @RES + "  = "
       op = [' + ', ' - ']
       j = 1
       first = true
       s = @TABN + 3 + @RES.size
       @AV.each do |v|
           next if (not prob @P_LIVE_OUT) and (@LVall.member? v)
           str = ''
           str += op[j] if !first
           str += v
           if (s+str.size < 80)
              res += str
              s += str.size
           else
              res += "\n" + tab + ' ' * (@RES.size+3) + str
              s = str.size + @TABN + 3 + @RES.size
           end
           first = false
           j = 1 - j
       end
       res += mrand(@MAX_NUM).to_s if first
       res += ";\n"
       res += arrRes if (@AVArr.size > 0)
       res += "\n" + tab + 'printf ("' + @RES + ' = %u\n", ' + @RES + ");\n"
       res += "\n" + tab + "return 0;\n"
       return res
   end


   def initArrs
       res  = "\n" + "#define " + @MAX_TRIPNM + " " + @MAX_TRIPC.to_s
       res += "\n" + "#define " + @CHECK + "(a,n) " +
              @CHECKC + "((unsigned int*) " + "a, n)"
       res += "\n" + "#define " + @INIT + "(a,n,s) " +
              @INITC + "((unsigned int*) " + "a, n, s)\n\n"
 
       res += "void " + @INITC +
              " (unsigned int a[], unsigned int n, int seed)\n"
       res += "{\n"
       res += tab + "unsigned int j = 0;\n\n"
       #res += tab + @SRAND + " (seed);\n"
       res += tab + "for (j = 0; j < n; j++) {\n"
       #res += tab + tab + "a[j] = "+@RAND+" % "+(1+@MAX_ARR_INIT).to_s + ";\n"
       res += tab + tab + "a[j] = " + "((j % 2 == 0) ? seed+j : seed-j)" +
              " % " + (1 + @MAX_ARR_INIT).to_s + ";\n"
       res += tab + "}\n"
       res += "}\n\n"
 
       res += "unsigned int " + @CHECKC +
              " (unsigned int a[], unsigned int n)\n"
       res += "{\n"
       res += tab + "unsigned int j = 0, sum = 0;\n\n"
       res += tab + "for (j = 0; j < n; j++) {\n"
       res += tab + tab + "sum += ((j % 2 == 0) ? a[j] : -a[j]);\n"
       res += tab + "}\n"
       res += tab + "return sum;\n"
       res += "}\n\n"
 
       return res
   end
   
   def prologue
       res = "//\n"
       if (ARGV[0] != nil) 
          res += "//   " + ARGV[0] + "\n"
       end
       res += "//   Generated by Moh's fuzzer on " + Time.now.ctime + "\n"
       res += "//\n"
       res += "//   Intel Corporation.\n"
       res += "//\n\n"
       res += "#include <stdio.h>\n"
       res += initArrs if (@AVArr.size > 0) 
       res += "int main()\n"
       res += "{\n"
       return res 
   end
   
   def epilogue
       res = "}\n"
       return res 
   end
   
   def num1(n)
       k = mrand(n+1)
       k = mrand(n+1) if k == 0
       return k
   end

   def init
       return if not @AUTO_WEIGHT
       adjustW(getW(@SSTMT_D), @SPTYPES)
       adjustW(getW(@LSTMT_D), @LPTYPES)
       getStmtTable
   end

   def gencode
       init
       txt = rSeq($NUMS)
       return prologue + decls + txt + getres + epilogue 
   end
  
end

def more(count=true)
    return 0 if $NUMS <= 0
    $NUMS -= 1 if count 
    return $NUMS
end

def rNdx2(list)
    return $ICF.rNdx2(list)
end

def addExtension(x, w=1, f=1)
    $ICF.addStmt(x, w, f)
end

def delExtension(x)
    $ICF.delStmt(x)
end

def addLoopExtension(x, w=1, f=1)
    $ICF.addLoopStmt(x, w, f)
end

def delLoopExtension(x)
    $ICF.delLoopStmt(x)
end

def addScalarExtension(x, w=1, f=1)
    $ICF.addScalarStmt(x, w, f)
end

def delScalarExtension(x)
    $ICF.delScalarStmt(x)
end

def gencode
    puts $ICF.gencode()
end

$ICF = Fuzzer.new()
