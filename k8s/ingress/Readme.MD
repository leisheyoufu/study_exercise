## Ingress nginx Env

```
[root@k8sdev ingress]# kubectl get svc -n ingress-nginx
NAME                   TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)   AGE
default-http-backend   ClusterIP   10.43.216.174   <none>        80/TCP    7d23h
[root@k8sdev ingress]# curl http://10.43.216.174/
default backend - 404[root@k8sdev ingress]#

spec:
    clusterIP: 10.43.216.174
    ports:
    - port: 80
      protocol: TCP
      targetPort: 8080
    selector:
      app: default-http-backend
```

## Qeury pod with specified label
```
kubectl get pod -l app=default-http-backend -n ingress-nginx
[root@k8sdev ingress]# kubectl get po -n ingress-nginx
NAME                                    READY   STATUS    RESTARTS   AGE
default-http-backend-67cf578fc4-pcbc6   1/1     Running   8          8d
nginx-ingress-controller-hckm8          1/1     Running   8          8d

```
nginx-ingress-controller runs in hostNetwork

## nginx
nginx is listening on 80 port started by nginx-ingress-controller. nginx was deployed as a daemonset.
[root@k8sdev ingress]# netstat -anlp | grep 80
tcp        0      0 0.0.0.0:80              0.0.0.0:*               LISTEN      17978/nginx: master

33        17825  17776  0 06:57 ?        00:00:27 /nginx-ingress-controller --default-backend-service=ingress-nginx/default-http-backend --configmap=ingress-nginx/nginx-configuration --tcp-services-configmap=ingress-nginx/tcp-services --udp-services-configmap=ingress-nginx/udp-services --annotations-prefix=nginx.ingress.kubernetes.io
33        17978  17825  0 06:57 ?        00:00:00 nginx: master process /usr/local/openresty/nginx/sbin/nginx -c /etc/nginx/nginx.conf

## Start demo
kubectl apply -f tomcat.yml

NAME             TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)             AGE
service/tomcat   ClusterIP   10.43.157.218   <none>        8080/TCP,8009/TCP   3h33m

Now can access tomcat service via cluster ip like `curl http://10.43.157.218:8080`

Access tomcat via ingress
```
kubectl apply -f ingress.yml
echo "192.168.126.151       tomcat.loch.com" >> /etc/hosts
curl http://tomcat.loch.com/
```