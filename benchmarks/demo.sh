# printpass ll - wanna show that we added print statements into the ir code
# perfc2c txt - wanna show the perf output can do this with perf report, also show the print pass output, briefly say python script
# reordering output ll  - make it stop after reordering is done show ll file that order is different, reorder.txt, padding.txt
# padding output ll - show that final output is padded and reorered, 
#sh ./demo.sh reorder reordertest.cpp 
LoadPass=""
PassName=""
echo $# $1
if [ $1 = "group" ]; then
    LoadPass="GroupTPass"
    PassName="groupt-pass"
elif [ $1 = "pad" ]; then
    # if [ $# -eq 2 ]; then
    #     echo "here"
    #     sh newrun.sh print $2
    #     sh end.sh perf.txt
    # fi
    LoadPass="PaddingPass"
    PassName="padding-pass"
elif [ $1 = "reorder" ]; then
    sh demo.sh print $2 
    echo "Show preop.ll and test.ll.out for print pass"
    code preop.ll test.ll.out
    read -p "Paused: " pause
    LoadPass="ReorderPass"
    PassName="reorder-pass"
    sh end.sh perf.txt reorder
    echo "Show perf.txt and vars.txt and reorder.txt for dynamic analysis"
    code perf.txt vars.txt reorder.txt padding.txt
    read -p "Paused: " pause
elif [ $1 = "print" ]; then
    LoadPass="PrintPass"
    PassName="print-pass"
elif [ $1 = "indirection" ]; then
    LoadPass="IndirectionPass"
    PassName="indirection-pass"
elif [ $1 = "nopass" ]; then
    LoadPass="PrintPass"
    PassName=""
fi

cd ../build && make && cd ../benchmarks
echo "Running $PassName"
if [ $# -eq 2 ]; then
    clang -emit-llvm -S $2 -Xclang -disable-O0-optnone -O0 -o  test.ll -std=c++11 -stdlib=libc++ -fno-discard-value-names
fi
opt -load-pass-plugin=../build/$LoadPass/$LoadPass.so -passes=$PassName test.ll -f > test.bc 
llvm-dis test.bc -o test.ll.out
clang -fprofile-instr-generate -g test.bc -o run_this_code -std=c++11 -stdlib=libc++ -lpthread
cp test.ll preop.ll
cp test.ll.out test.ll
if [ $1 = "reorder" ]; then
    echo "Show preop.txt and test.ll.out for reordering"
    code preop.ll test.ll.out
    read -p "Paused: " pause
    sh demo.sh pad 
fi

if [ $1 = "pad" ]; then
    echo "Show preop.ll and test.ll.out fo rpadding"
    code preop.ll test.ll.out
    read -p "Paused: " pause
fi


