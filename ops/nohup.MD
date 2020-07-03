## Why process killed with nohup
As far as I know, there are two situations that can cause a process to be killed after being protected by nohup, and each situation has a different workaround.

One possibility, which does not appear to be the case here, is that the system uses systemd where logind.conf is configured with KillUserProcesses=yes. In this case, closing the terminal will not cause problems, but logging out of the system will. The workaround in this case is to use

$ systemd-run --scope --user [command]
This basically just tells systemd that it should not kill the process.

The other possibility is that the spawned process implements its own handler for SIGHUP which overrides the protection of nohup. In this case, problems will occur as soon as the shell is closed, even if you remain logged in. You can check for this with:

$ nohup [command] &
$ grep Sig /proc/$!/status
You should see a line

SigIgn: 0000000000000001
(or some other string of hexadecimal digits). SIGHUP is signal number 1, so if this big-endian hexadecimal number has its first (least-significant) bit set (that is, the final digit is one of 1, 3, 5, 7, 9, B, D, or F), then SIGHUP is ignored. Otherwise, the program has installed its own handler overriding the protection of nohup.

In this case, the solution is to use disown:

nohup [command] & disown
This removes the process from the shell's job list, preventing SIGHUP from being sent in the first place.

## Reference
https://unix.stackexchange.com/questions/420594/why-process-killed-with-nohup