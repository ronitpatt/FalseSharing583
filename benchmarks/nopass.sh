# clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# opt -load-pass-plugin=./build/FsharingPass/FsharingPass.so -passes="fsharing-pass" test.ll -f > test.bc
# #clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# # clang -fprofile-instr-generate test.bc -o output_prof -Xclang -disable-O0-optnone
# # ./output_prof


clang -emit-llvm -S $1 -Xclang -disable-O0-optnone -O0 -o  nopass.ll -std=c++11 -stdlib=libc++ -fno-discard-value-names
opt  -passes="" nopass.ll -f > test.bc 

llvm-dis test.bc -o nopass.ll.out
clang -fprofile-instr-generate  test.bc -o run_this_code -std=c++11 -stdlib=libc++ -lpthread
