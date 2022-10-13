## 容器内抓包，容器抓包
    容器内抓包：
    1.登陆节点；

    2.通过kubectl describe获取服务容器容器ID；

    3.通过docker inspect或者crictl inspect(如果没有节点安装docker)，获取容器信息，可以在其中找到"Pid"字段，其值便是容器进程号PID
    4.nsenter -n -t [PID]

    5.nohup tcpdump -i any -s 0 -vnn host [ip] and port [port] -C 200M -W 5 -w /tmp/pod.cap

nohup tcpdump -i any -s 0 -vnn host <连接目标host> and port <连接目标port> -C 200M -W 5 -w /tmp/pod.cap