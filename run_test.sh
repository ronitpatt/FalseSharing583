cd build && make && cd ..
clang -emit-llvm -S test.cpp -Xclang -disable-O0-optnone -O0 -o test.ll -std=c++11 -stdlib=libc++

opt -load-pass-plugin=./build/FsharingPass/FsharingPass.so -passes="" test.ll -f > test_unoptimized.bc
llvm-dis test_unoptimized.bc -o test.ll.out
clang -fprofile-instr-generate test_unoptimized.bc -o unoptimized -std=c++11 -stdlib=libc++ -lpthread
sudo perf stat -d -d ./unoptimized - benchmarks/unoptimized.txt

opt -load-pass-plugin=./build/FsharingPass/FsharingPass.so -passes="fsharing-pass" test.ll -f > test.bc
llvm-dis test.bc -o test.ll.out
clang -fprofile-instr-generate test.bc -o optimized -std=c++11 -stdlib=libc++ -lpthread
sudo perf stat -d -d ./optimized -o benchmarks/optimized.txt
