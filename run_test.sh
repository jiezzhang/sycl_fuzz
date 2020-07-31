export ICS_START=/rdrive/ics/itools/unx/bin
source $ICS_START/icssetup.sh
source $ICS_START/icsenv.sh

ics ws -archive deploy_xmain xmainefi2linux 20200713_000000
ics config -ws xmainefi2linux prod gcc=7.5.0 ld=bfd
ics set context ws host

result_root=/export/users/jiezhang/fuzz_result
source_root=/export/users/jiezhang/fuzz_source
fuzz_root=`pwd`;

build_option["cpu"]="-fsycl-targets=spir64_x86_64-unknown-unknown-sycldevice";
build_option["gpu"]="-fsycl-targets=spir64_gen-unknown-unknown-sycldevice -Xs \"-device cfl\"";
build_option["oclgpu"]="-fsycl-targets=spir64_gen-unknown-unknown-sycldevice -Xs \"-device cfl\"";
build_option["acc"]="-fintelfpga";

if [ ! -d "$result_root" ]
then
    mkdir $result_root;
fi
if [ ! -d "$source_root" ]
then
    mkdir $source_root;
    cp -r ../test/* $source_root;
fi
cd $fuzz_root;

num=0;
compile_cmd="dpcpp -o test.run sycl_launcher.cpp libcpp.cpp -DPARALLEL_FOR_ND_RANGE -Wno-everything";
#while [ 1 ]
#do
    rm -rf $source_root/*
    cp -r ../test/* $source_root;
    date=`date +"%Y%m%d" --date="1 days ago"`;
    output_root=$result_root/$date;

    if [ ! -d "$output_root" ]
    then
        mkdir $output_root;
    fi

    python g -n 100000 runcg-0.6.g -f $source_root/kernel_impl.hpp;
    cd $source_root;
    result="";
    num=$(($num+1));
    echo "TEST $num:";

    for i in {"O0","O1","O2","O3"}
    do
        for j in {"JIT","AOT"}
        do
            for k in {"cpu","gpu","oclgpu","acc"}
            do
                # Build test
                if [[ $j == "JIT" ]]
                then
                    $compile_cmd -$i >compile_$i_$j.log 2>&1;
                else
                    $compile_cmd -$i ${build_option[$k]} >compile_$i_$j.log 2>&1;
                fi
                cmd_output=$?;
                if [[ $cmd_output != 0 ]]
                then
                    result="Compile fail in $i $j with $cmd_output";
                    echo $result;
                    continue;
                fi 

                # Run test
                env_var=""
                if [[ $k == "oclgpu" ]]
                then
                    env_var="SYCL_BE=PI_OPENCL"
                fi
                $env_var timeout 10m ./test.run -p intel -d $k > run_$i\_$j\_$k.log 2>&1;
                cmd_output=$?;
                if [[ $cmd_output != 0 ]]
                then
                    result="$k runfail in $i $j with $cmd_output";
                    echo $result;
                fi  
            done
        done
    done
    if [[ $result != "" ]]
    then
        mkdir "$output_root/$num";
        cp -r $source_root/* "$output_root/$num"; 
    else
        echo "PASS";
    fi

    cd $fuzz_root;
#done
