## k8s command
kubectl exec -it zk-0 -- zkServer.sh status
kubectl exec -it zk-0 -- zkCli.sh create /hello world
kubectl delete -f zk.yaml 
kubectl apply -f zk.yaml
kubectl exec -it zk-0 -- zkCli.sh get /hello
/opt/kafka/bin/kafka-topics.sh --bootstrap-server 127.0.0.1:9092 --list
kubectl -n kube-system get configmaps coredns -o yaml   // get zone name
kubectl delete pods <pod> --grace-period=0 --force
kubectl delete -f kafka.yml --grace-period=0 --force
kubectl delete ns <ns> --grace-period=0 --force

## Topic command
kubectl exec kafka-0 -n loch -- /opt/kafka/bin/kafka-topics.sh --zookeeper zk-cs.loch.svc.cluster.local:2181 --list
kubectl exec kafka-0 -n loch -- /opt/kafka/bin/kafka-topics.sh --zookeeper zk-cs:2181 --list  // only service within the same namespace is ok
kubectl exec kafka-0 -n loch -- /opt/kafka/bin/kafka-topics.sh  --create --zookeeper zk-cs.loch.svc.cluster.local:2181 --replication-factor 1 --partitions 1 --topic demo
kubectl exec kafka-0 -n loch -- /opt/kafka/bin/kafka-topics.sh --bootstrap-server kafka-svc.loch.svc.cluster.local:9092 --list // maybe this version do not wupport
kubectl exec kafka-0 -n loch -- /opt/kafka/bin/kafka-topics.sh  --describe --zookeeper zk-cs.loch.svc.cluster.local:2181 --topic demo
kubectl exec kafka-0 -n loch -- /opt/kafka/bin/kafka-topics.sh --bootstrap-server kafka-svc.loch.svc.cluster.local:9092 --delete --topic demo

## NOTE
kafka.yml is for single node test
## Reference
- [kow3ns](https://kow3ns.github.io/kubernetes-kafka/manifests/)   // 3 years ago
- [k8s-kafka](https://www.jianshu.com/p/af79350a6ddb)    https://github.com/cuishuaigit/k8s-kafka  // 2 years ago  , kafka 2.2  
- [How to deploy Kafka and Zookeeper cluster on Kubernetes](https://github.com/ashishrpandey/kafka-demo) // 2020
- [local volumn provisioner](https://www.infoq.cn/article/AH1N57f8TGE2wIsQuJ00)
- [kubernetes部署kafka集群, statefulset 包括zookeeper,kafka](https://www.modb.pro/db/15250)