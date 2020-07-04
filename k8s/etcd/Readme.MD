# Show all the keys in etcd

ETCDCTL_API=3 etcdctl get "" --prefix --keys-only | sed '/^\s*$/d'

```
/ # ETCDCTL_API=3 etcdctl get "" --prefix --keys-only | sed '/^\s*$/d' | grep deployment
/registry/clusterrolebindings/system:controller:deployment-controller
/registry/clusterroles/system:controller:deployment-controller
/registry/deployments/ingress-nginx/default-http-backend
/registry/deployments/kube-system/calico-kube-controllers
/registry/deployments/kube-system/coredns
/registry/deployments/kube-system/coredns-autoscaler
/registry/deployments/kube-system/metrics-server
/registry/deployments/loch/tomcat-deploy
/registry/secrets/kube-system/deployment-controller-token-xczng
/registry/serviceaccounts/kube-system/deployment-controller
```

etcdctl --endpoints <ip>：<port> member list