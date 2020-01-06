#!/bin/bash

# ========================CORE================================
# BUILDER
# screen -t "BUILDER"   sh -c '. ./atg_profile && . ./ATG/bin/activate &&  mkdir --parents $ATG_WORK_DIR; cd $ATG_WORK_DIR;  python $ATG_HOME_DIR/atg_core.py --build -c clang -j8 --use-svn; bash'

# RETESTER
screen -t "RETESTER"    sh -c '. ./atg_profile && . ./ATG/bin/activate &&  mkdir --parents $ATG_WORK_DIR; cd $ATG_WORK_DIR;  python $ATG_HOME_DIR/atg_core.py --retest; bash'  

# Standart generators
screen -t "fuzz"    sh -c '. . ./atg_profile &&. ./ATG/bin/activate &&  mkdir --parents $ATG_WORK_DIR; cd $ATG_WORK_DIR;  python $ATG_HOME_DIR/atg_test.py -c xmain -g fuzz; bash'

screen -t "oldgen"    sh -c '. ./atg_profile && . ./ATG/bin/activate &&  mkdir --parents $ATG_WORK_DIR; cd $ATG_WORK_DIR;  python $ATG_HOME_DIR/atg_test.py -c xmain -g oldgen; bash'

screen -t "base"    sh -c '. ./atg_profile && . ./ATG/bin/activate &&  mkdir --parents $ATG_WORK_DIR; cd $ATG_WORK_DIR;  python $ATG_HOME_DIR/atg_test.py -c xmain -g base; bash'

screen -t "cexpr"    sh -c '. ./atg_profile && . ./ATG/bin/activate &&  mkdir --parents $ATG_WORK_DIR; cd $ATG_WORK_DIR;  python $ATG_HOME_DIR/atg_test.py -c xmain -g cexpr; bash'

screen -t "fuzz"    sh -c '. ./atg_profile && . ./ATG/bin/activate &&  mkdir --parents $ATG_WORK_DIR; cd $ATG_WORK_DIR;  python $ATG_HOME_DIR/atg_test.py -c xmain -g fuzz; bash'
