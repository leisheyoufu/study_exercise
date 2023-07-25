Host *.github.com
	ServerAliveInterval 10
	ControlMaster auto
	ControlPath ~/.ssh/%r@%h:%p
	TCPKeepAlive yes
	ServerAliveInterval 15
	ServerAliveCountMax 6
    
Host 192.168.1.*
	User root
	Port 22

Host *
	ServerAliveInterval 60
	ProxyCommand <path>/corkscrew 127.0.0.1 <port> %h %p
	ControlMaster auto
	ControlPath ~/.ssh/ssh_mux_%h_%p_%r
	ControlPersist 24h
	TCPKeepAlive yes
	ServerAliveInterval 15
	ServerAliveCountMax 6
