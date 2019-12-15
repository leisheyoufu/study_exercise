## Rancher
If you use rancher(rke) to deploy k8s cluster, please add below in your config, run `rke up --config ./rancher-cluster.yml` again.
```
services:
  kubelet:
    extra_binds:
       - /mnt:/mnt:rshared
```
## Local vol
```
mkdir -p /data/local/vol1
kubectl get nodes
```
Modify host in nodeAffinity fields of static-local.yml, run below:
```
kubectl create -f static-local.yml
[root@k8sdev pv]# kubectl get pvc
NAME      STATUS   VOLUME             CAPACITY   ACCESS MODES   STORAGECLASS   AGE
myclaim   Bound    example-local-pv   5Gi        RWO            local-volume   6s
```
Local volumn bonding completed.

