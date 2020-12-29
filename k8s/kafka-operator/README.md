## kafka operator debug

kubectl create ns kafka
kubectl apply -f cluster-operator -n kafka
kubectl apply -f deploy-cluster/kafka-persistent.yaml -n kafka2


kubectl delete -f deploy-cluster/kafka-persistent.yaml -n kafka2

### prometheus
kubectl apply -f deploy-cluster/metrics/manifests/setup
kubectl apply -f deploy-cluster/metrics/manifests

kubectl apply -f deploy-cluster/metrics/prometheus-install


kubectl delete -f deploy-cluster/metrics/manifests/setup
kubectl delete -f deploy-cluster/metrics/manifests
kubectl delete -f deploy-cluster/metrics/prometheus-install

### User control

kubectl apply -f deploy-cluster/kafka-user-tls.yaml -n kafka2
kubectl apply -f deploy-cluster/kafka-super.yaml -n kafka2
kubectl apply -f deploy-cluster/kafka-external-service.yaml -n kafka2

## Online service
kubectl create namespace kafka
kubectl apply -f 'https://strimzi.io/install/latest?namespace=kafka' -n kafka
kubectl delete -f 'https://strimzi.io/install/latest?namespace=kafka' -n kafka
kubectl apply -f https://strimzi.io/examples/latest/kafka/kafka-persistent-single.yaml -n kafka 

## Test command
export KAFKA_CLUSTER_NAME=my-cluster-kafka
kubectl exec -it my-cluster-kafka-0 -n kafka2 -- /opt/kafka/bin/kafka-topics.sh --bootstrap-server my-cluster-kafka-external-bootstrap:9092 --list
kubectl exec -it my-cluster-kafka-0 -n kafka2 -- /opt/kafka/bin/kafka-topics.sh --bootstrap-server <ip:port> --list

kubectl exec -it my-cluster-kafka-0 -n kafka2 -- nslookup my-cluster-kafka-external-bootstrap
kubectl run kafka-producer -ti --image=strimzi/kafka:latest-kafka-2.6.0 --rm=true --restart=Never -n kafka2 -- bin/kafka-console-producer.sh --broker-list $KAFKA_CLUSTER_NAME-kafka-bootstrap:9092 --topic my-topic

kubectl get secret my-cluster-cluster-ca-cert -o jsonpath='{.data.ca\.crt}' | base64 -d > ca.crt

kubectl get pods -n kube-system -oname |grep coredns |xargs kubectl delete -n kube-system
kubectl exec -it my-cluster-kafka-0 -n kafka2 -- /opt/kafka/bin/kafka-topics.sh --bootstrap-server <ip:port> --create --topic test --partitions 2 --replication-factor 2

kubectl exec -it my-cluster-zookeeper-0 -n kafka2 -- /opt/kafka/bin/zookeeper-shell.sh 127.0.0.1:12181 get /brokers/ids/1
kubectl exec -it kafka-cluster-zookeeper-0 -n ephemeral-kafka-cluster -- /opt/kafka/bin/zookeeper-shell.sh 127.0.0.1:12181 ls /config/users

kubectl get sts my-cluster-kafka -n kafka2 -o jsonpath='{.spec.template.metadata.labels}'

## OPs
kubectl annotate statefulset <cluster-name> strimzi.io/manual-rolling-update=true
## Build From Source
wget https://github.com/mikefarah/yq/releases/download/3.4.0/yq_linux_amd64 -O /usr/bin/yq &&    chmod +x /usr/bin/yq
mvn package -DskipTests
mvn install -DskipTests  // setup package into maven local repository
cd cluster-operator && make docker_build && cd -
cd docker-images && make docker_build && cd -

user-operator, cluster-operator, topic-operator 都打在strimzi/operator:latest 这个image 里，根据k8s指定的arg脚本去指定执行cluster-operator还是user-operator, 比如 /opt/strimzi/bin/topic_operator_run.sh， /opt/strimzi/bin/user_operator_run.sh，
/opt/stunnel/entity_operator_stunnel_run.sh

for pv in `kubectl get pv | grep Released | awk '{print $1}' | xargs`; do
    kubectl patch pv $pv -p '{"spec":{"claimRef": null}}'
done

## openssl
openssl s_client -debug -connect <ip:port> -tls1_2 | grep subject
/opt/kafka/bin/kafka-console-producer.sh --broker-list <ip:port> --topic test4 --producer.config /tmp/client.properties
/opt/kafka/bin/kafka-console-producer.sh --broker-list localhost:9094 --producer.config /tmp/client.properties --topic test2 
/opt/kafka/bin/kafka-topics.sh --bootstrap-server localhost:9092 --list

openssl pkcs12 -export -in server.crt -inkey server.key -name myserver.internal.net > server.p12

### BrokerId
docker-images/kafka/scripts/kafka_run.sh
```
STRIMZI_BROKER_ID=$(hostname | awk -F'-' '{print $NF}')
```

### zookeeper 链接localhost:2181，sidecar stunnel
/usr/bin/stunnel /tmp/stunnel.conf
```
pid = /usr/local/var/run/stunnel.pid
foreground = yes
debug = notice
sslVersion = TLSv1.2
[zookeeper-2181]
client = yes
CAfile = /tmp/cluster-ca.crt
cert = /etc/tls-sidecar/eo-certs/entity-operator.crt
key = /etc/tls-sidecar/eo-certs/entity-operator.key
accept = 127.0.0.1:2181
connect = my-cluster-zookeeper-client:2181
delay = yes
verify = 2
```
## Kafka partition segment
No a partition cannot reside on multiple machine in kafka ... Partitions cannot be split between multiple brokers and not even between multiple disks on the same broker .....In other words you can say that the size of the partition is limited by the space in the disk mount.

## Reference
[quickstart](https://strimzi.io/quickstarts/)
[github source](https://github.com/strimzi/strimzi-kafka-operator)
[kafka sasl](https://www.cnblogs.com/xiao987334176/p/10110389.html)
[Kafka on Kubernetes, the Strimzi way! (Part 1)](https://itnext.io/kafka-on-kubernetes-the-strimzi-way-part-1-bdff3e451788)
[Kafka on Kubernetes, the Strimzi way! (Part 3)](https://itnext.io/kafka-on-kubernetes-the-strimzi-way-part-3-19cfdfe86660)
[github krallistic/kafka-operator](https://github.com/krallistic/kafka-operator)
[github banzaicloud/kafka-operator](https://github.com/banzaicloud/kafka-operator)
[Accessing Kafka: Part 4 - Load Balancers](https://strimzi.io/blog/2019/05/13/accessing-kafka-part-4/)
[Using Strimzi (0.19.0)](https://strimzi.io/docs/operators/latest/using.html)
[coredns rewrite cluster.local](https://serverascode.com/2020/03/25/rewrite-change-cluster-local-kubernetes.html)
[zookeeper without tls 12181](https://strimzi.io/docs/operators/master/using.html#assembly-zookeeper-node-configuration-deployment-configuration-kafka)
[zookeeper shell tls](https://docs.confluent.io/current/kafka/incremental-security-upgrade.html)
[kafka openssl client](https://docs.confluent.io/2.0.0/kafka/ssl.html)
[pkcs](https://smallstep.com/hello-mtls/doc/combined/kafka/kafka-cli)
[Kafka SASL/SCRAM+ACL实现动态创建用户及权限控制](https://blog.csdn.net/ashic/article/details/86661599)
[kafka add user dynamically](https://stackoverflow.com/questions/54147460/kafka-adding-sasl-users-dynamically-without-cluster-restart)
[k8s can not support pod from statefulset to node](https://github.com/kubernetes/kubernetes/issues/65267)
[prometheus service monitor federate](https://github.com/prometheus-operator/prometheus-operator/pull/1100)
[kafka cruise-control](https://github.com/linkedin/cruise-control)
[kafka strimzi cruise-control](https://strimzi.io/blog/2020/06/15/cruise-control/)
[Kafka partition in relation to a broker](https://stackoverflow.com/questions/48431016/kafka-partition-in-relation-to-a-broker#:~:text=No%20a%20partition%20cannot%20reside,space%20in%20the%20disk%20mount.)
[cruise-control-disk-capacity](https://github.com/linkedin/cruise-control/issues/1052)