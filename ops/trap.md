首先还是查man trap,看看啥情况会调起

       trap [-lp] [[arg] sigspec ...]
              The  command arg is to be read and executed when the shell receives signal(s) sigspec.

              If a sigspec is ERR, the command arg is executed
              whenever a simple command has a non-zero exit status, subject to the following conditions.  The ERR trap
              is not executed if the failed command is part of the command list immediately following a while or until
              keyword, part of the test in an if statement, part of a && or || list, or if the command's return  value
              is  being  inverted via !.
Ctrl + C 终止程序时执行 cleanup_data,函数再退出           
```
trap 'cleanup_data; exit 1' INT TERM
```