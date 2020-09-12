## Viewing full output of PS command
Sometimes output from ps in busybox was trunicated by tty, below is some useful commands:
``` 
COLUMNS=1000 ps -ef
ps aux | less -S
ps aux | most
ps -efww
ps -A -o args,pid,lstart
```

## Referebce
[Viewing full output of PS command](https://stackoverflow.com/questions/2159860/viewing-full-output-of-ps-command)