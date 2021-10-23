gcc -o test main.c
```
root@ubuntu:~/project/uprobe# objdump -d test | grep print_curr_state_one
0000000000001169 <print_curr_state_one>:
    11a9:       e8 bb ff ff ff          callq  1169 <print_curr_state_one>
root@ubuntu:~/project/uprobe# objdump -d test | grep print_curr_state_two

0000000000001185 <print_curr_state_two>:
    11bd:       e8 c3 ff ff ff          callq  1185 <print_curr_state_two>
```

./test

echo 'p:print_current_state_one /root/project/uprobe/test:11a9' >> /sys/kernel/debug/tracing/uprobe_events
echo 'p:print_current_state_two /root/project/uprobe/test:11bd' >> /sys/kernel/debug/tracing/uprobe_events


echo 1 > /sys/kernel/debug/tracing/events/enable
```
root@ubuntu:~# cat /sys/kernel/debug/tracing/events/enable
1
```
echo 1 > /sys/kernel/debug/tracing/events/uprobes/enable

less /sys/kernel/debug/tracing/trace
```
test-10935   [000] d... 19543.828655: print_current_state_one: (0x55c883f551a9)
```
## other example
p:uprobes/p_bash_0x4ab500 /bin/bash:0x00000000004ab500 arg1=%ip arg2=%ax

```
  #           TASK-PID    CPU#    TIMESTAMP  FUNCTION
    #              | |       |          |         |
                 zsh-24842 [006] 258544.995456: p_bash_0x46420: (0x446420) arg1=446421 arg2=79
                 zsh-24842 [007] 258545.000270: p_bash_0x46420: (0x446420) arg1=446421 arg2=79
                 zsh-24842 [002] 258545.043929: p_bash_0x46420: (0x446420) arg1=446421 arg2=79
                 zsh-24842 [004] 258547.046129: p_bash_0x46420: (0x446420) arg1=446421 arg2=79
```

## clear
echo > /sys/kernel/debug/tracing/uprobe_events

## reference
[DevOps ftrace uprobe使用填坑历程](https://www.dazhuanlan.com/guuuuuu/topics/1174110)
[objdump -t](https://blog.csdn.net/badu_123/article/details/8302642)