# clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# opt -load-pass-plugin=./build/FsharingPass/FsharingPass.so -passes="fsharing-pass" test.ll -f > test.bc
# #clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# # clang -fprofile-instr-generate test.bc -o output_prof -Xclang -disable-O0-optnone
# # ./output_prof

LoadPass=""
PassName=""
echo $#
if [ $1 = "group" ]; then
    LoadPass="GroupTPass"
    PassName="groupt-pass"
elif [ $1 = "pad" ]; then
    sh newrun.sh print $2
    LoadPass="PaddingPass"
    PassName="padding-pass"
    sh end.sh perf.txt
elif [ $1 = "reorder" ]; then
    sh newrun.sh print $2
    LoadPass="ReorderPass"
    PassName="reorder-pass"
    sh end.sh perf.txt reorder
elif [ $1 = "print" ]; then
    LoadPass="PrintPass"
    PassName="print-pass"
elif [ $1 = "indirection" ]; then
    LoadPass="IndirectionPass"
    PassName="indirection-pass"
elif [ $1 = "nopass" ]; then
    LoadPass="FsharingPass"
    PassName=""
fi

echo "Running $PassName"
cd ../build && make && cd ../benchmarks
if [ $# -eq 2 ]; then
    clang -emit-llvm -S $2 -Xclang -disable-O0-optnone -O0 -o  test.ll -std=c++11 -stdlib=libc++ -fno-discard-value-names
fi
opt -load-pass-plugin=../build/$LoadPass/$LoadPass.so -passes=$PassName test.ll -f > test.bc 
llvm-dis test.bc -o test.ll.out
clang -fprofile-instr-generate -g test.bc -o run_this_code -std=c++11 -stdlib=libc++ -lpthread
cp test.ll preop.ll
cp test.ll.out test.ll
if [ $1 = "reorder" ]; then
    sh newrun.sh pad 
fi

