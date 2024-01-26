result_root=/export/users/jiezhang/fuzz_result
source_root=/export/users/jiezhang/fuzz_source
fuzz_root=`pwd`;

declare -A build_option=( ["cpu"]="-fsycl-targets=spir64_x86_64-unknown-unknown-sycldevice" ["gpu"]="-fsycl-targets=spir64_gen-unknown-unknown-sycldevice -Xs \"-device cfl\"" ["oclgpu"]="-fsycl-targets=spir64_gen-unknown-unknown-sycldevice -Xs \"-device cfl\"" [acc]="-fintelfpga")

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
compile_cmd="icpx -fsycl -o test.run sycl_launcher.cpp libcpp.cpp -DPARALLEL_FOR_ND_RANGE -Wno-everything";
while [ 1 ]
do
    source init_env.sh > /dev/null 2>&1

    rm -rf $source_root/*
    cp -r ../test/* $source_root;
    date=`date +"%Y%m%d" --date="1 days ago"`;
    output_root=$result_root/$date;

    if [ ! -d "$output_root" ]
    then
        mkdir $output_root;
    fi

    while [ 1 ]
    do
    	python2 g -n 900000000 runcg-0.6.g -f $source_root/kernel.hpp>out.log 2>&1;
    	grep "exceed" out.log > /dev/null 2>&1
    	out=$?

    	if [[ $out == 1 ]]
   	then
		echo $out
		break
	fi
    done
    cd $source_root;
    result="";
    num=$(($num+1));
    echo "TEST $num:";

    for i in {"O1","O2","O3"}
    do
        for j in {"JIT","AOT"}
        do
            for k in {"cpu","gpu","oclgpu","acc"}
            do
                # Build test
                # Build test
                if [[ $j == "JIT" ]]
                then
                    $compile_cmd -$i >compile_$i\_$j.log 2>&1;
                else
                    echo "$compile_cmd ${build_option[$k]} "
                    $compile_cmd ${build_option[$k]} -$i >compile_$i\_$j\_$k.log 2>&1;
                fi
                cmd_output=$?;
                if [[ $cmd_output != 0 ]]
                then
                    result="Compile fail in $i $j $k with $cmd_output";
                    echo $result;
                    continue;
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
