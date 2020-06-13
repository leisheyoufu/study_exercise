pscp -pw 123456 -r D:\Projects\study_exercise\linux_application\backtrace root@192.168.126.141:/root/projects/study_exercise/linux_application/
g++ sigsabort.cpp -g -o sigsabort

## Reference
[c++运用backtrace追踪函数调用的堆栈](https://www.cnblogs.com/osyun/archive/2012/08/17/2644018.html)
[How ro resolve cpp symbols from backtrace_symbols() in the offset during runtime for addr2line](https://stackoverflow.com/questions/55450932/how-ro-resolve-cpp-symbols-from-backtrace-symbols-in-the-offset-during-runtime)
[C++ library reference](http://www.cplusplus.com/reference/)