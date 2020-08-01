注意--leader-elect 说明实际只有一个进程工作
kube-scheduler --v=2 --kubeconfig=/etc/kubernetes/ssl/kubecfg-kube-scheduler.yaml --address=0.0.0.0 --leader-elect=true --profiling=false

kube-controller-manager --cloud-provider= --root-ca-file=/etc/kubernetes/ssl/kube-ca.pem --service-cluster-ip-range=10.43.0.0/16 --allocate-node-cidrs=true --enable-hostpath-provisioner=false --kubeconfig=/etc/kubernetes/ssl/kubecfg-kube-controller-manager.yaml --service-account-private-key-file=/etc/kubernetes/ssl/kube-service-account-token-key.pem --v=2 --profiling=false --node-monitor-grace-period=40s --cluster-cidr=10.42.0.0/16 --address=0.0.0.0 --leader-elect=true --pod-eviction-timeout=5m0s --allow-untagged-cloud=true --configure-cloud-routes=false --terminated-pod-gc-threshold=1000 --use-service-account-credentials=true


Each of master replicas will run the following components in the following mode:

etcd instance: all instances will be clustered together using consensus;

API server: each server will talk to local etcd - all API servers in the cluster will be available;

controllers, scheduler, and cluster auto-scaler: will use lease mechanism - only one instance of each of them will be active in the cluster;

add-on manager: each manager will work independently trying to keep add-ons in sync.

In addition, there will be a load balancer in front of API servers that will route external and internal traffic to them.

Load balancing 

## 个人理解
apiserver 接受请求，然后根据etcd的watch在服务内建立事件缓存队列，所以多个apiserver中缓存的数据队列应该是一致的，可以多节点ha
controlmanager 和 scheduler会根据leader-ecect选举得到主节点，实现HA
## Reference
[Set up High-Availability Kubernetes Masters](https://kubernetes.cn/docs/tasks/administer-cluster/highly-available-master/)
[Introduction to Kubernetes Architecture](https://rancher.com/learning-paths/introduction-to-kubernetes-architecture/)