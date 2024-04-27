clang -emit-llvm -S test.c -Xclang -disable-O0-optnone -o test.ll 

opt -S -load-pass-plugin=./build/IndirectionOptPass/IndirectionOptPass.so -passes="func-name" test.ll -o test_transformed.ll

clang test.ll -o nonopt_out 

clang test_transformed.ll -o opt_out 
