## build llvm
首先编译llvm 作为库
mkdir llvm_build
cd llvm_build
cmake -G Ninja -DLLVM_EXTERNAL_PROJECTS=tinylang -DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../tinylang -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../llvm-12 /Users/leisheyoufu/Projects/c/llvm-project/llvm  (最后的参数是llvm的目录)

ninja
ninja insetall

## build tinylang
mkdir tinylang_build
cd tinylang_build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_DIR=../llvm-12/lib/cmake/llvm -DCMAKE_INSTALL_PREFIX=../llvm-12 ../
ninja
ninja install
./tinylang

## Reference
https://blog.csdn.net/Zhanglin_Wu/article/details/124963173


## chapter 3
### build llvm 
mkdir llvm_build
cd llvm_build
cmake -G Ninja -DLLVM_EXTERNAL_PROJECTS=calc -DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../calc -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../llvm-12 /Users/franckcheng/Projects/c/llvm-project/llvm

ninja
ninja insetall
cd -

### build calc
mkdir calc_build
cd calc_build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_DIR=../llvm-12/lib/cmake/llvm -DCMAKE_INSTALL_PREFIX=../llvm-12 ../

