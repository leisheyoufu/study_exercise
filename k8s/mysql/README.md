## Command
$ kubectl create -f mysql.yml
$ kubectl get po -n loch
NAME                     READY   STATUS    RESTARTS   AGE
mysql-674c66fd5d-ck5dp   1/1     Running   0          3m2s
$ kubectl exec -it mysql-674c66fd5d-ck5dp -n loch -- mysql -uroot -p123456 -hmysql-svc
mysql: [Warning] Using a password on the command line interface can be insecure.
Welcome to the MySQL monitor.  Commands end with ; or \g.

## Mysql-pod
kubectl exec -it mysql -n loch -c mysql -- /bin/bash
mysql -uroot -p123456 -h127.0.0.1
mysql> set password for root@localhost = password('123');   // # modify password to make liveniness failure
mysql> set password for root@127.0.0.1 = password('123'); 
mysql> set password for root@'%' = password('123');

## Reference
- [通过搭建MySQL掌握k8s（Kubernetes）重要概念（上](https://blog.csdn.net/weixin_38748858/article/details/102514721)
- [通过搭建MySQL掌握k8s（Kubernetes）重要概念（下）：参数配置](https://blog.csdn.net/weixin_38748858/article/details/102514901)
- [Kubernetes中部署MySQL, statefulset, liveness readiness很详细](https://www.cnblogs.com/fan-gx/p/12874257.html)