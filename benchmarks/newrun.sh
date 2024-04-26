# clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# opt -load-pass-plugin=./build/FsharingPass/FsharingPass.so -passes="fsharing-pass" test.ll -f > test.bc
# #clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# # clang -fprofile-instr-generate test.bc -o output_prof -Xclang -disable-O0-optnone
# # ./output_prof

LoadPass=""
PassName=""



if [ $1 = "group" ]; then
    LoadPass="GTPass"
    PassName="groupt-pass"
elif [ $1 = "pad" ]; then
    LoadPass="FSharingPass"
    PassName="fsharing-pass"
elif [ $1 = "reorder" ]; then
    sh newrun.sh print $2
    LoadPass="ReorderPass"
    PassName="reorder-pass"
    sh end.sh
elif [ $1 = "print" ]; then
    LoadPass="PrintPass"
    PassName="print-pass"
fi

echo "Running $PassName"
cd ../build && make && cd ../benchmarks
clang -emit-llvm -S $2 -Xclang -disable-O0-optnone -O0 -o  test.ll -std=c++11 -stdlib=libc++ -fno-discard-value-names
opt -load-pass-plugin=../build/$LoadPass/$LoadPass.so -passes=$PassName test.ll -f > test.bc 
llvm-dis test.bc -o test.ll.out
clang -fprofile-instr-generate -g test.bc -o run_this_code -std=c++11 -stdlib=libc++ -lpthread




