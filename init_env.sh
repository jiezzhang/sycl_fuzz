timestamp=$(date -d "2 day ago" "+%Y%m%d")_160000

export ICS_START=/rdrive/ics/itools/unx/bin
source $ICS_START/icssetup.sh
source $ICS_START/icsenv.sh

ics ws -archive deploy_xmain xmainefi2linux $timestamp
ics config -ws xmainefi2linux qa_release gcc=sys ld=bfd
ics set context ws host