# iterm profile
~/login.exp <ip> loch '<password>'

# login exp
```
#!/usr/bin/expect
 if { $argc !=3 } {
     send_user "without host user password params"
     exit
 }
 set host [lindex $argv 0]
 set user [lindex $argv 1]
 set pwd  [lindex $argv 2]

 catch {spawn ssh -l <user> <host> -p <ssh port>}
 expect "<host info>" {send "ssh $host -l $user\r"}
 expect {
     "(yes/no)?"
     {send "yes\n";exp_continue}
     "*Password:*"
     {send "$pwd\n"}
     "*password:*"
     {send "$pwd\n"}
 }

 expect "Last login:" {send "cd ~\r";interact }
```