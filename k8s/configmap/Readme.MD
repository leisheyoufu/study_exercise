## Use configmap as env
kubectl create -f config.yml
kubectl create -f pod.yml
kubectl logs mypod -n loch
kubectl logs mycommandpod -n loch
```
[root@k8sdev configmap]# kubectl logs mypod -n loch
config1=xxx
KUBERNETES_SERVICE_PORT=443
KUBERNETES_PORT=tcp://10.43.0.1:443
config2=yyy
HOSTNAME=mypod
CONFIG_KEY=nosql
SHLVL=1
HOME=/root
KUBERNETES_PORT_443_TCP_ADDR=10.43.0.1
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
CONFIG_NAME=redis
KUBERNETES_PORT_443_TCP_PORT=443
KUBERNETES_PORT_443_TCP_PROTO=tcp
KUBERNETES_SERVICE_PORT_HTTPS=443
KUBERNETES_PORT_443_TCP=tcp://10.43.0.1:443
KUBERNETES_SERVICE_HOST=10.43.0.1
PWD=/
[root@k8sdev configmap]# kubectl logs mycommandpod -n loch
redis nosql
```

## Mount configmap as volumn
kubectl replace --force -f pod.yml
```
[root@k8sdev configmap]# kubectl logs volpod -n loch
nosql[root@k8sdev configmap]#
```

Reference: https://www.jianshu.com/p/b1d516f02ecd


## Create config map from file
kubectl create configmap nginx-www --from-file=./www.conf -n loch
kubectl create -f nginx.yml
kubectl replace --force -f nginx.yml   # force restart
kubectl get pod {podname} -n {namespace} -o yaml | kubectl replace --force -f -  # force restart pod
kubectl exec -it nginx -n loch -- cat /etc/nginx/www.conf
sed -i 's/80/8080/g' www.conf
kubectl create configmap nginx-www --from-file=./www.conf --dry-run -o yaml | kubectl apply -n loch -f -
kubectl exec -it nginx -n loch -- cat /etc/nginx/www.conf   # wait about 30 seconds


## TODO
[watch file change](https://github.com/howeyc/fsnotify)
[Leverage side car to hot update the configuration](https://www.jianshu.com/p/66c1ac15044f)