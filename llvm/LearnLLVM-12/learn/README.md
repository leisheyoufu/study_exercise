## build llvm
首先编译llvm 作为库
mkdir llvm_build
cd llvm_build
cmake -G Ninja -DLLVM_EXTERNAL_PROJECTS=tinylang -DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../tinylang -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../llvm-12 /Users/leisheyoufu/Projects/c/llvm-project/llvm  (最后的参数是llvm的目录)

ninja
ninja install

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
mkdir calc_build
cd calc_build
cmake -G Ninja -DLLVM_EXTERNAL_PROJECTS=calc -DLLVM_EXTERNAL_TINYLANG_SOURCE_DIR=../calc -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../llvm-12 /Users/leisheyoufu/Projects/c/llvm-project/llvm

ninja
ninja install
cd -

编译llvm生成的文件拷贝到了calc/llvm-12里作为库使用

### build calc
mkdir calc_build
cd calc_build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_DIR=../llvm-12/lib/cmake/llvm -DCMAKE_INSTALL_PREFIX=../llvm-12 ../

因为没有定义install target , 手动拷贝到
cp src/calc ../llvm-12/bin/

修改src/CMakeLists.txt, 添加
```
install(TARGETS calc
  RUNTIME DESTINATION bin
  COMPONENT calc)  
```  

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
