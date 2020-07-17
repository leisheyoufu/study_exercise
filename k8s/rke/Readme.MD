## Prerequest
$ sudo vim /etc/fstab
Add comment to swap line

sudo swapoff -a
useradd rke
passwd rke
usermod -aG docker rke

$ sudo vim /etc/sudoers.d/rke
$ sudo tee -a /etc/sysctl.d/99-kubernetes.conf <<EOF
net.bridge.bridge-nf-call-iptables  = 1
net.ipv4.ip_forward                 = 1
net.bridge.bridge-nf-call-ip6tables = 1
EOF

$ sysctl --system
curl https://releases.rancher.com/install-docker/19.03.sh | sudo bash -
rke  ALL=(ALL:ALL) NOPASSWD: ALL

### Firewalled ports
I always disable selinux and apparrmor helre .

for i in 22 80 443 179 5473 6443 8472 2376 8472 2379-2380 9099 10250 10251 10252 10254 30000-32767; do
    sudo firewall-cmd --add-port=${i}/tcp --permanent
done
for i in 8285 8472 4789 30000-32767; do
   sudo firewall-cmd --add-port=${i}/udp --permanent
done
sudo firewall-cmd --reload

yum install openssh-server  // openssh-server should be 6.7 above
sudo vi /etc/ssh/sshd_config
AllowTcpForwarding yes

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

## Download kubectl
wget https://dl.k8s.io/v1.16.5/kubernetes-client-linux-amd64.tar.gz
export KUBECONFIG=./kube_config_cluster.yml


## Reference
- [Rancher official website](https://rancher.com/docs/rke/latest/en/installation/)
- [Rancher minimal configuration](https://rancher.com/docs/rke/latest/en/example-yamls/#minimal-cluster-yml-example)
- [More steps to setup kubernetes CL 最重要](https://computingforgeeks.com/install-kubernetes-production-cluster-using-rancher-rke/)
- [Change docker root dir](https://github.com/IronicBadger/til/blob/master/docker/change-docker-root.md)