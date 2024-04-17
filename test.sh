# clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# opt -load-pass-plugin=./build/FsharingPass/FsharingPass.so -passes="fsharing-pass" test.ll -f > test.bc
# #clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# # clang -fprofile-instr-generate test.bc -o output_prof -Xclang -disable-O0-optnone
# # ./output_prof

cd build && make && cd ..
opt  -passes="" test.ll.out -f > test.bc
llvm-dis test.bc -o save.ll
clang -fprofile-instr-generate test.bc -o run_this_code -std=c++11 -stdlib=libc++
