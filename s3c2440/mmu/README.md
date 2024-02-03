gcc 编译出来的是 elf 文件。通常 gcc test.c 生成的 a.out 文件就是 elf 格式的，在 linux shell 下输入 ./a.out 可以执行。

$ file a.out
a.out: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, not stripped

bin 文件是经过压缩的可执行文件，去掉 elf 格式的东西。是值接的内存映像的表示。在系统没有加载操作系统的时候可以执行。

elf（executable and link format）文件里面包含了符号表、汇编等。

bin（binary）文件是将 elf 文件中的代码段、数据段，还有一些自定义的段抽取出来做成的一个内存的镜像。

在 Embedded 中，上电开始运行，没有 OS 系统，如果将 elf 格式的文件烧写进去，包含一些 elf 格式的东西，ARM 运行碰到这些指令，就会导致失败，如果用 objcopy 生成纯粹的汇编 bin 文件，程序就可以一步一步运行。

机器最终只认 bin，elf 格式是在有操作系统时，操作系统会根据 elf 解析出代码、数据等，最终仍是以 bin 运行。由于 elf 信息比较全，所以可以用来单步跟踪的方式运行。
