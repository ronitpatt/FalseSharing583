# clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# opt -load-pass-plugin=./build/FsharingPass/FsharingPass.so -passes="fsharing-pass" test.ll -f > test.bc
# #clang -emit-llvm -c test.c -Xclang -disable-O0-optnone -o test.bc
# # clang -fprofile-instr-generate test.bc -o output_prof -Xclang -disable-O0-optnone
# # ./output_prof

cd build && make && cd ..
clang -emit-llvm -S temp.cpp -Xclang -disable-O0-optnone -O0 -o temp.ll -std=c++11 -stdlib=libc++
opt  -passes="" temp.ll -f > temp.bc
llvm-dis temp.bc -o temp.ll.out
clang -fprofile-instr-generate temp.bc -o run_this_code_temp -std=c++11 -stdlib=libc++
