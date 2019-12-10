## Check dns service
```
[root@k8sdev init_container]# kubectl get svc -n kube-system
NAME             TYPE        CLUSTER-IP     EXTERNAL-IP   PORT(S)                  AGE
kube-dns         ClusterIP   10.43.0.10     <none>        53/UDP,53/TCP,9153/TCP   2d6h
```

## Check kubelet process
--cluster-dns=10.43.0.10
```
kubelet --hostname-override=192.168.126.151 --streaming-connection-idle-timeout=30m --cgroups-per-qos=True --make-iptables-util-chains=true --client-ca-file=/etc/kubernetes/ssl/kube-ca.pem --cloud-provider= --cluster-domain=cluster.local --authorization-mode=Webhook --cni-conf-dir=/etc/cni/net.d --network-plugin=cni --volume-plugin-dir=/var/lib/kubelet/volumeplugins --v=2 --cni-bin-dir=/opt/cni/bin --anonymous-auth=false --resolv-conf=/etc/resolv.conf --cluster-dns=10.43.0.10 --kubeconfig=/etc/kubernetes/ssl/kubecfg-kube-node.yaml --address=0.0.0.0 --event-qps=0 --fail-swap-on=false --pod-infra-container-image=rancher/pause:3.1 --root-dir=/var/lib/kubelet --read-only-port=0 --tls-cipher-suites=TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305,TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305 --authentication-token-webhook=true --cgroup-driver=cgroupfs
```
Kube-dns use list and watch service resource in k8s api-server, then keep the record in etcd.
kubelet add search domain in /etc/resolve.conf

## Check dns service
```
kubectl exec busybox  -- nslookup  <servicename>.<namespace>
kubectl exec busybox  -- nslookup kube-dns.kube-system
kubectl exec busybox  -- nslookup mydb.loch
kubectl exec busybox  -- nslookup myservice.loch

[root@k8sdev init_container]# kubectl exec -it myapp-pod -n loch -- cat /etc/resolv.conf
nameserver 10.43.0.10
search loch.svc.cluster.local svc.cluster.local cluster.local
options ndots:5
```

## Force restart a pod
```
kubectl get po myapp-pod -n loch -o yaml | kubectl replace --force -f -   # no pod configuration
kubectl replace --force -f service.yml    
```

More infomation could be found at https://blog.csdn.net/qq_31136839/article/details/97969947
