###########################################################
#                                                         #
#  Intel Compiler Fuzzer for compiler testing             #
#                                                         #
#  select a random set of extensions for test generation  #
#                                                         #
#  Author: Mohammad R. Haghighat, Intel Corporation       #
#                                                         #
#  History:                                               #
#     December 23, 2008 : Creation                        #
#                                                         #
#                                                         #
###########################################################

require 'icFuzz.rb'

extensions = []
extensions << 'LoopFusion.rb'
extensions << 'LoopInterchange.rb'
extensions << 'LoopPredication.rb'
extensions << 'PointerIntensiveness.rb'
extensions << 'Vectorization.rb'
extensions << 'CSE.rb'

#extensions = []

n = extensions.size
s = rand(n+1)

ext = []

s.times {
   e = extensions[rand(extensions.size)]
   ext << e
   extensions -= [e]
}

ext.each {
   |e|
   require e
}

gencode
