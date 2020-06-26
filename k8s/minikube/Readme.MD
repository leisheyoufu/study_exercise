## Setup k8s with minikube
curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64 && chmod +x minikube
curl -Lo kubectl https://storage.googleapis.com/kubernetes-release/release/$(curl -s https://storage.googleapis.com/kubernetes-release/release/stable.txt)/bin/linux/amd64/kubectl && chmod +x kubectl
minikube start --vm-driver=virtualbox --network-plugin='cni'
minikube dashboard --url

## Debug inside minikube virtual machine
minikube ssh
Query the ports which are listening on tcp
ss -ltp   // `ss -lup` for udp     busybox netstat -anlp can not work, use this instead


Api server use container mode
```
# docker ps -a | grep apiserver
6bae0f1d6d7b        7e28efa976bd           "kube-apiserver --ad…"   2 hours ago         Up 2 hours                              k8s_kube-apiserver_kube-apiserver-minikube_kube-system_5d746552bb1514ad264ed6541c216635_0
4afa880ea1c0        k8s.gcr.io/pause:3.2   "/pause"                 2 hours ago         Up 2 hours                              k8s_POD_kube-apiserver-minikube_kube-system_5d746552bb1514ad264ed6541c216635_0

# docker inspect -f '{{.HostConfig.NetworkMode}}'  k8s_kube-apiserver_kube-apiserver-minikube_kube-system_5d746552bb1514ad264ed6541c216635_0
container:4afa880ea1c0f0dde6cf0667b20271d2b5a0a8c5d0d599f2346be5058a1ff5b8
# docker inspect -f '{{.HostConfig.NetworkMode}}'  4afa880ea1c0f0dde6cf0667b20271d2b5a0a8c5d0d599f2346be5058a1ff5b8
```