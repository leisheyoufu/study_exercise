For this first you need to start a detached screen.
```
screen -dmS MySessionName
```
And then send the script to that screen
```
screen -S MySessionName -p 0 -X stuff 'myprogram\n'
```
kill" will only kill one screen window. To "kill" the complete session, use quit.
```
screen -X -S [session # you want to kill] quit
```


screen -mDL sh -c 'your_command; echo $?' && tail -1 screenlog.0

## Reference
[Start a screen session and run a script without attaching to it?](https://askubuntu.com/questions/983063/start-a-screen-session-and-run-a-script-without-attaching-to-it)