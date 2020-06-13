g++ -g  -rdynamic -o show_bt show_bt.cpp  // rdynamic expose all the symbols
gdb show_bt
```
Starting program: /root/projects/study_exercise/linux_application/backtrace/show_bt
0x555555555607 0x5555555557e4 0x5555555557c5 0x5555555557b9 0x555555555834 0x7ffff7464b97 0x5555555554ea
(gdb) info symbol 0x555555555607
MyException::MyException() + 61 in section .text of /root/projects/study_exercise/linux_application/backtrace/show_bt
```

Find function line with address
```
 objdump -D show_bt | grep -A20 function1
00000000000017c0 <_Z9function1v>:
    17c0:       55                      push   %rbp
    17c1:       48 89 e5                mov    %rsp,%rbp
    17c4:       e8 03 00 00 00          callq  17cc <_Z2f2v>

root@ubuntu1:~/projects/study_exercise/linux_application/backtrace# addr2line -e show_bt 17c0
/root/projects/study_exercise/linux_application/backtrace/show_bt.cpp:40
```

## Reference
https://stackoverflow.com/questions/55450932/how-ro-resolve-cpp-symbols-from-backtrace-symbols-in-the-offset-during-runtime