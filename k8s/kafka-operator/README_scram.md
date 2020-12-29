## Deploy kafkauser


kubectl create secret generic foo --from-literal=password=123456 -n kafka2
kubectl apply -f deploy-cluster/kafka-user-scram-foo.yaml -n kafka2
kubectl create secret generic admin --from-literal=password=123456 -n kafka2
kubectl apply -f deploy-cluster/kafka-super.yaml -n kafka2


## Get password
export USER_NAME=admin
kubectl get secret $USER_NAME -n kafka2 -o jsonpath='{.data.password}' | base64 --decode > user-scram.password

## Test kafka client
### client normal user
make sure group and topic permission is granted, `client.properties`
```
bootstrap.servers=<ip:port>
security.protocol=SASL_PLAINTEXT
sasl.mechanism=SCRAM-SHA-512
sasl.jaas.config=org.apache.kafka.common.security.scram.ScramLoginModule required username="foo" password="Fes5PItXfXeJ";
```
/opt/kafka/bin/kafka-console-producer.sh --broker-list <kafka ip:port> --topic foo --producer.config /tmp/client.properties

/opt/kafka/bin/kafka-console-consumer.sh --bootstrap-server <kafka ip:port> --topic foo --from-beginning --consumer.config /tmp/admin.properties

/opt/kafka/bin/kafka-consumer-groups.sh --bootstrap-server <kafka ip:port> --group demo-consumer --describe --command-config /tmp/admin.properties 

/opt/kafka/bin/kafka-consumer-groups.sh --bootstrap-server <kafka ip:port> --list --command-config /tmp/admin.properties 
### client super user
Define authorization like below in kafka resource.
```
authorization:
      type: simple
      superUsers:
        - admin
```
Then create super user
kubectl apply -f deploy-cluster/kafka-super.yaml -n kafka2

## Manually [not pass]
/opt/kafka/bin/kafka-configs.sh --bootstrap-server localhost:9092 --alter --add-config 'SCRAM-SHA-256=[password=123456],SCRAM-SHA-512=[password=123456]' --entity-type users --entity-name foo

/opt/kafka/bin/kafka-configs.sh --zookeeper localhost:12181 --alter --add-config 'SCRAM-SHA-256=[password=123456],SCRAM-SHA-512=[password=123456]' --entity-type users --entity-name foo

/opt/kafka/bin/kafka-configs.sh --zookeeper localhost:2182 --describe --entity-type users --entity-name foo
/opt/kafka/bin/kafka-configs.sh  --zookeeper localhost:2182 --alter  --delete-config 'SCRAM-SHA-512' --entity-type users --entity-name foo

cp /opt/kafka/bin/kafka-console-producer.sh /tmp/kafka-console-producer-admin.sh
```
/opt/kafka/bin/kafka-run-class.sh -Djava.security.auth.login.config=/tmp/kafka_client_jass_admin.conf kafka.tools.ConsoleProducer "$@"
```
/tmp/kafka-console-producer-admin.sh  --broker-list <ip:port> --topic test --producer.config /tmp/client-sasl.properties

/opt/kafka/bin/kafka-console-producer.sh  --broker-list <ip:port> --topic test --producer.config /tmp/client-sasl.properties

### No permission
/opt/kafka/bin/kafka-topics.sh --create --topic test --bootstrap-server localhost:9092
/opt/kafka/bin/kafka-topics.sh --describe --topic test--bootstrap-server localhost:9092
