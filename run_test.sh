fuzz_root=`pwd`;
gen_root=$fuzz_root/generators
result_root=$fuzz_root/fuzz_result
source_root=$fuzz_root/fuzz_source


declare -A build_option=( ["cpu"]="-fsycl-targets=spir64_x86_64-unknown-unknown-sycldevice" ["gpu"]="-fsycl-targets=spir64_gen-unknown-unknown-sycldevice -Xs \"-device gen12\"" ["oclgpu"]="-fsycl-targets=spir64_gen-unknown-unknown-sycldevice -Xs \"-device gen12\"" [acc]="-fintelfpga")
declare -A type_option=( ["cpu"]="" ["gpu"]="-DNON_DOUBLE=1" ["oclgpu"]="-DNON_DOUBLE=1" ["acc"]="-DNON_HALF=1")

if [ ! -d "$result_root" ]
then
    mkdir $result_root;
fi
if [ ! -d "$source_root" ]
then
    mkdir $source_root;
    cp -r test/* $source_root;
fi
cd $fuzz_root;

num=0;
cmd="icpx -fsycl -o test.run sycl_launcher.cpp libcpp.cpp -DPARALLEL_FOR_ND_RANGE -Wno-everything";
while [ 1 ]
do
    source ./init_env.sh > /dev/null 2>&1

    rm -rf $source_root/*
    cp -r test/* $source_root;
    date=`date +"%Y%m%d" --date="1 days ago"`;
    output_root=$result_root/$date;

    if [ ! -d "$output_root" ]
    then
        mkdir $output_root;
    fi

    while [ 1 ]
    do
        python2 $gen_root/g -n 900000000 $gen_root/runcg-0.6.g -f $source_root/kernel.hpp>out.log 2>&1;
    	grep "exceed" out.log > /dev/null 2>&1
    	out=$?

    	if [[ $out == 1 ]]
   	then
            break
	fi
    done
    cd $source_root;
    result="";
    num=$(($num+1));
    echo "TEST $num:";
    which icpx;

    for i in {"O1","O2","O3"}
    do
        for j in {"JIT",}
        do
            for k in {"cpu","gpu","oclgpu","acc"}
            do
                # Append type w/a
                compile_cmd="$cmd ${type_option[$k]} -$i"
                # Build test
                if [[ $j == "AOT" ]]
                then
                   compile_cmd="$compile_cmd ${build_option[$k]}"
                fi
                `$compile_cmd > compile_$i\_$j\_$k.log 2>&1`;
                cmd_output=$?;
                if [[ $cmd_output != 0 ]]
                then
                    result="Compile fail in $i $j $k with $cmd_output";
                    echo $result;
                    continue;
                else
                    rm compile_$i\_$j\_$k.log
                fi

                # Run test
                if [[ $i == "O0" ]] && [[ $k == *"gpu"* ]]
                then
                    continue;
                fi
                env_var=""
                if [[ $k == "oclgpu" ]]
                then
                    SYCL_BE=PI_OPENCL timeout 10m ./test.run -p intel -d gpu > run_$i\_$j\_$k.log 2>&1;
                else
                    timeout 10m ./test.run -p intel -d $k > run_$i\_$j\_$k.log 2>&1
                fi
                cmd_output=$?;
                if [[ $cmd_output != 0 ]]
                then
                    result="$k runfail in $i $j with $cmd_output";
                    echo $result;
                else
                    rm run_$i\_$j\_$k.log
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
    rm -rf $source_root/kernel*
    cd $fuzz_root;
done
