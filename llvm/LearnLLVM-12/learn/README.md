## clone and build llvm
cd /opt/projects
git clone https://github.com/llvm/llvm-project.git
cd llvm-project/
mkdir build
cd build/
cmake -G Ninja -DLLVM_ENABLE_PROJECTS=clang ../llvm

## chapter 2
build llvm lib
```
mkdir build
cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
-DLLVM_EXTERNAL_PROJECTS=tinylang \
-DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../tinylang \
-DCMAKE_INSTALL_PREFIX=../llvm-12 \
/opt/projects/llvm-project/llvm

ninja -j8
```
build tinylang
```
mkdir tinylang_build
cd tynylang_build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17 -DLLVM_DIR=../llvm-12/lib/cmake/llvm -DCMAKE_INSTALL_PREFIX=../llvm-12 ../
ninja -j8
ninja install
cd ../llvm-12
./bin/tinylang
Hello, I am Tinylang 0.1
```


## Reference
https://blog.csdn.net/Zhanglin_Wu/article/details/124963173


## chapter 3
### build llvm 
mkdir calc_build
cd calc_build
cmake -G Ninja -DLLVM_EXTERNAL_PROJECTS=calc -DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../calc -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../llvm-12 /Users/leisheyoufu/Projects/c/llvm-project/llvm

cmake -G Ninja -DLLVM_EXTERNAL_PROJECTS=calc -DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../calc -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/projects//llvm-12 /opt/projects/llvm-project/llvm

ninja
ninja install
cd -

编译llvm生成的文件拷贝到了calc/llvm-12里作为库使用

### build calc
mkdir calc_build
cd calc_build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_DIR=../llvm-12/lib/cmake/llvm -DCMAKE_INSTALL_PREFIX=../llvm-12 ../


-G Ninja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=/Users/leisheyoufu/Projects/c/llvm-12/lib/cmake/llvm

因为没有定义install target , 手动拷贝到
cp src/calc ../llvm-12/bin/

修改src/CMakeLists.txt, 添加
```
install(TARGETS calc
  RUNTIME DESTINATION bin
  COMPONENT calc)  
``` 

### chapter 5
#### build llvm
mkdir build && cd build


cmake -G Ninja -DLLVM_EXTERNAL_PROJECTS=tinylang -DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../tinylang -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/projects/llvm-12 /opt/projects/llvm-project/llvm

ninja -j8
ninja install

#### build tinylang
mkdir tinylang_build && cd tinylang_build

cmake -G Ninja -DLLVM_EXTERNAL_PROJECTS=tinylang -DCMAKE_CXX_STANDARD=17 -DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../tinylang -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/projects/llvm-12 /opt/projects/llvm-project/llvm

```
clang -v --version | grep Target | cut -d' ' -f2-
arm64-apple-darwin21.5.0

clang --target=arm64-apple-darwin21.5.0 -S -emit-llvm gcd.c  // generate gcd.ll
/opt/projects/llvm-project/build/bin/clang --target=arm64-apple-darwin21.5.0 -S -emit-llvm gcd.c // generate gcd.ll from llvm12
/opt/projects/llvm-project/build/bin/clang -O1 --target=arm64-apple-darwin21.5.0 -S -emit-llvm gcd.c // 带phi 优化
```

## Chapter 8 
bin/opt --disable-output --passes="countir" --stats  // 运行某一个pass

## Chapter 9
llc -mtriple=mips-linux-gnu -debug-pass=Structure < sum.ll

### Run
$ ninja insetall # 拷贝到llvm-12
$ cd calc_build/src
$ ./calc "with a: a*3"
生成如下IR代码
```
; ModuleID = 'calc.expr'
source_filename = "calc.expr"

@a.str = private constant [2 x i8] c"a\00"

define i32 @main(i32 %0, ptr %1) {
entry:
  %2 = call i32 @calc_read(ptr @a.str)
  %3 = mul nsw i32 %2, 3
  call void @calc_write(i32 %3)
  ret i32 0
}

declare i32 @calc_read(ptr)

declare void @calc_write(i32)
```

$ ./calc "with a: a*3" | ./llc -filetype=obj -o=expr.o  # llc 将中间IR 代码转换成二进制

$ cp expr.o ../../   # 文件拷贝到calc的目录
$ clang -o expr expr.o rtcalc.c  # 链接二进制文件 到expr
$ ./expr
Enter a value for a: 4
The result is: 12
