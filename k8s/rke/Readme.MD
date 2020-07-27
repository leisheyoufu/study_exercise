## Prerequest
$ sudo vim /etc/fstab
Add comment to swap line

sudo swapoff -a
useradd rke
passwd rke
usermod -aG docker rke

$ sudo vim /etc/sudoers.d/rke
rke  ALL=(ALL:ALL) NOPASSWD: ALL
$ sudo tee -a /etc/sysctl.d/99-kubernetes.conf <<EOF
net.bridge.bridge-nf-call-iptables  = 1
net.ipv4.ip_forward                 = 1
net.bridge.bridge-nf-call-ip6tables = 1
EOF

ssh -V // ssh version should be 7.6 or higher

$ sysctl --system
curl https://releases.rancher.com/install-docker/19.03.sh | sudo bash -

### Disable selinux
setenforce 0
vim /etc/sysconfig/selinux

SELINUX=enforcing 改为 SELINUX=disabled
### Firewalled ports
I always disable selinux and apparrmor helre .

systemctl start firewalld
for i in 22 80 443 179 5473 6443 8472 2376 8472 2379-2380 9099 10250 10251 10252 10254 30000-32767; do
    firewall-cmd --add-port=${i}/tcp --permanent
done
for i in 8285 8472 4789 30000-32767; do
   sudo firewall-cmd --add-port=${i}/udp --permanent
done
sudo firewall-cmd --reload

systemctl stop firewalld // 可直接关闭firewalld

yum install openssh-server  // openssh-server should be 6.7 above
sudo vi /etc/ssh/sshd_config
AllowTcpForwarding yes
PermitTunnel yes

## Debug network
docker network create --driver=bridge --subnet=172.11.0.1/24 --gateway=172.11.0.1 br0
docker run --name docker-proxy -d -p 2399:1337 --net br0 rancher/rke-tools:v0.1.59 /usr/bin/nc -kl -p 1337 -e echo
docker run --name docker-proxy -d -p 2399:1337 rancher/rke-tools:v0.1.59 /usr/bin/nc -kl -p 1337 -e echo
docker run -it --rm --name docker-proxy -p 2399:1337 -e PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin" rancher/rke-tools:v0.1.59 /bin/bash
ip link delete docker0 // delete interface
docker ps -qa | xargs docker rm -f

ifconfig eth0 promisc    #设置混杂
ifconfig eth0 -promisc　#取消混杂　

iptables -A INPUT -p tcp --dport 22 -j ACCEPT // if firewall is used , skip this
iptables -A INPUT -p tcp --dport 2379 -j ACCEPT

## Configuration
cluster.yml
```
nodes:
    - address: k8snode1
      user: rke
      role:
        - controlplane
        - etcd
        - worker
      port: 1800 // ssh port
network:
    plugin: flannel

services:
  kubelet:
    extra_binds:
       - /mnt:/mnt:rshared
```

## Change docker root dir
vim /etc/docker/daemon.json
```
{
    "data-root": "/new/docker/root"
}
```

rke up --config cluster.yml


## Note on centos7
```
if you run rke in centos7, you should not use the root user to open the ssh tunnel.you can try the following step to run rke
in all nodes:

update openssh to 7.4,and docker version v1.12.6
set "AllowTcpForwarding yes" "PermitTunnel yes" to /etc/ssh/sshd_config,and then restart sshd service
the host which run rke can ssh to all nodes without password
run: "groupadd docker" to create docker group,while docker group is not exist.
run: "useradd -g docker yourusername" to create yourusername user and set it's group to docker
set the docker.service's MountFlags=shared (vi /xxx/xxx/docker.service)
run:"su yourusername" to change current user,and then restart the docker service. so in the user yourusername session the docker.sock will be created in the path /var/run/docker.sock
in cluster.yml set the ssh user to yourusername(in setup hosts)
```
## Download kubectl
wget https://dl.k8s.io/v1.16.5/kubernetes-client-linux-amd64.tar.gz
export KUBECONFIG=./kube_config_cluster.yml


## Multiple control panel
Apiserver 通过 iptables dnat 获得负载均衡
```
Chain KUBE-SVC-NPX46M4PTMTKRN6Y (1 references)
 pkts bytes target     prot opt in     out     source               destination
   79  4740 KUBE-SEP-SVVJXOBZHHAJJJHX  all  --  *      *       0.0.0.0/0            0.0.0.0/0            /* default/kubernetes:https */ statistic mode random probability 0.33333333349
   79  4740 KUBE-SEP-PG4MXLJWJUFO5NJ3  all  --  *      *       0.0.0.0/0            0.0.0.0/0            /* default/kubernetes:https */ statistic mode random probability 0.50000000000
   96  5760 KUBE-SEP-UFC3O5QFP65VU4WQ  all  --  *      *       0.0.0.0/0            0.0.0.0/0            /* default/kubernetes:https */

Chain KUBE-SEP-PG4MXLJWJUFO5NJ3 (1 references)
 pkts bytes target     prot opt in     out     source               destination
   79  4740 DNAT       tcp  --  *      *       0.0.0.0/0            0.0.0.0/0            /* default/kubernetes:https */ tcp to:<ip1>:6443

Chain KUBE-SEP-SVVJXOBZHHAJJJHX (1 references)
 pkts bytes target     prot opt in     out     source               destination
   79  4740 DNAT       tcp  --  *      *       0.0.0.0/0            0.0.0.0/0            /* default/kubernetes:https */ tcp to:<ip2>:6443

Chain KUBE-SEP-UFC3O5QFP65VU4WQ (1 references)
 pkts bytes target     prot opt in     out     source               destination
   96  5760 DNAT       tcp  --  *      *       0.0.0.0/0            0.0.0.0/0            /* default/kubernetes:https */ tcp to:<ip3>:6443
```
kubelet node watch
```
apiVersion: v1
kind: Config
clusters:
- cluster:
    api-version: v1
    certificate-authority: /etc/kubernetes/ssl/kube-ca.pem
    server: "https://127.0.0.1:6443"
```

## Reference
- [Rancher official website](https://rancher.com/docs/rke/latest/en/installation/)
- [Rancher minimal configuration](https://rancher.com/docs/rke/latest/en/example-yamls/#minimal-cluster-yml-example)
- [More steps to setup kubernetes CL 最重要](https://computingforgeeks.com/install-kubernetes-production-cluster-using-rancher-rke/)
- [Change docker root dir](https://github.com/IronicBadger/til/blob/master/docker/change-docker-root.md)
- ["rke up" got "ssh: rejected: administratively prohibited (open failed)](https://github.com/rancher/rke/issues/93)