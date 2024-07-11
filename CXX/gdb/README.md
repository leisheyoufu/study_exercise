## gdb python pretty
gdb 调试的时候经常需要打印stl容器，正常gdb打印无法打印容器内容，不方便查看数据和问题，增加几行简单脚本即可实现，在.gdbinit文件中增加如下配置：

python
import sys
sys.path.insert(0, "文件的路径")
from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
end

gdb启动的时候会加载此文件，高版本gdb安装的时候会带有python脚本文件，只需要增加上面配置就可以了，也可以自己下载（https://gcc.gnu.org/svn/gcc/trunk/libstdc++-v3/python/libstdcxx/）把该目录中的所有文件都直接按照对应的目录和文件复制下就可以了.

## gdb core dump
ulimit -c unlimited
core 文件地址
cat /proc/sys/kernel/core_pattern
其次，输入 echo '/home/wangtian/coredump_file/core.%e-%p-%s' > /proc/sys/kernel/core_pattern 命令即可 更改 coredump 文件生成路径（注意：这种更改为临时更改方法）。

也可通过 `sysctl -p` kernel.core_pattern=core.%p.%u.%s.%e.%t

export COREDIR=/path/to/coredump/file


## addr2line readelf
1. 使用gdb调试器解析coredump文件：
   GDB是一个强大的调试器，可以用于解析和调试coredump文件。首先，确保安装了GDB：
   “`
   sudo apt-get install gdb
   “`
   然后，使用以下命令来加载coredump文件到GDB中：
   “`
   gdb <可执行文件路径> 
   “`
   进入GDB调试器后，可以使用一系列命令来查看崩溃时的状态信息，例如查看堆栈跟踪信息、查看变量的值等。

2. 使用addr2line命令解析coredump文件：
   addr2line命令可以将地址转换为文件名和行号，在解析coredump文件时非常有用。首先，确保安装了binutils工具包：
   “`
   sudo apt-get install binutils
   “`
   然后，使用以下命令来解析coredump文件：
   “`
   addr2line -e <可执行文件路径> -C -f <地址>
   “`
   使用该命令可以查找给定地址所对应的文件名和行号。

3. 使用readelf命令解析coredump文件：
   readelf命令可以查看ELF格式的文件的详细信息，可以用于解析coredump文件中的符号信息。使用以下命令来解析coredump文件：
   “`
   readelf -a 
   “`
   使用该命令可以查看core文件中的符号信息、段信息和程序的加载地址等。

以上是解析coredump文件的一些常用方法，可以根据具体情况选择合适的方法进行调试和排查程序崩溃问题。

## reference
                        
原文链接：https://blog.csdn.net/m08090420/article/details/104287817