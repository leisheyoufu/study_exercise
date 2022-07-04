## /etc/pf.conf
block drop out proto tcp from any to any port 2379

pfctl -f /etc/pf.conf
pfctl -e # enable
pfctl -d # disable

[How do I drop outgoing packets to specific host/port?](https://apple.stackexchange.com/questions/230209/how-do-i-drop-outgoing-packets-to-specific-host-port)
[Quick and easy pf (packet filter) firewall rules on macOS](https://blog.neilsabol.site/post/quickly-easily-adding-pf-packet-filter-firewall-rules-macos-osx/)