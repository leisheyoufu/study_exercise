## Client
kubectl get secret $KAFKA_USER_NAME -n kafka2 -o jsonpath='{.data.user\.crt}' | base64 --decode > user.crt
kubectl get secret $KAFKA_USER_NAME -n kafka2 -o jsonpath='{.data.user\.key}' | base64 --decode > user.key
kubectl get secret $KAFKA_USER_NAME -n kafka2 -o jsonpath='{.data.user\.password}' | base64 --decode > user.password
kubectl get secret $KAFKA_USER_NAME -n kafka2 -o jsonpath='{.data.user\.p12}' | base64 --decode > user.p12

export USER_P12_FILE_PATH=user.p12
export USER_KEY_PASSWORD_FILE_PATH=user.password
export KEYSTORE_NAME=kafka-auth-keystore.jks
export KEYSTORE_PASSWORD=foobar
export PASSWORD=`cat $USER_KEY_PASSWORD_FILE_PATH`

keytool -importkeystore -deststorepass $KEYSTORE_PASSWORD -destkeystore $KEYSTORE_NAME -srckeystore $USER_P12_FILE_PATH -srcstorepass $PASSWORD -srcstoretype PKCS12

## Server
export CLUSTER_NAME=my-cluster
kubectl get secret $CLUSTER_NAME-cluster-ca-cert -o jsonpath='{.data.ca\.crt}' -n kafka2 | base64 --decode > ca.crt
kubectl get secret $CLUSTER_NAME-cluster-ca-cert -o jsonpath='{.data.ca\.password}' -n kafka2 | base64 --decode > ca.password

export CERT_FILE_PATH=ca.crt
export CERT_PASSWORD_FILE_PATH=ca.password
export KEYSTORE_LOCATION=/usr/lib/jvm/java-14-openjdk-amd64/lib/security/cacerts
export PASSWORD=`cat $CERT_PASSWORD_FILE_PATH`

keytool -importcert -alias strimzi-kafka-cert -file $CERT_FILE_PATH -keystore $KEYSTORE_LOCATION -keypass $PASSWORD // default jdk password is changeit

keytool -list -alias strimzi-kafka-cert -keystore $KEYSTORE_LOCATION

## Go client
export CA_CERT_LOCATION=/home/ubuntu/kube/ca.crt
export KAFKA_TOPIC=test-strimzi-topic
export USER_CERT_LOCATION=/home/ubuntu/kube/user.crt
export USER_KEY_LOCATION=/home/ubuntu/kube/user.key
export USER_KEY_PASSWORD=`cat /home/ubuntu/kube/user.password`
export KAFKA_BOOTSTRAP_SERVERS=<ip:port>

## /etc/profile for kafka client machine
export GOHOME=/usr/local/go
export GO111MODULE=on
export PATH=$PATH:/usr/local/go/bin
export GOPATH=/home/ubuntu/projects/go
export GOBIN=$GOPATH/bin
export GOPROXY=https://goproxy.cn
export KUBECONFIG=/home/ubuntu/kube/config.tke

wget https://studygolang.com/dl/golang/go1.13.12.linux-amd64.tar.gz
apt install openjdk-14-jre-headless

git clone https://github.com/abhirockzz/kafka-kubernetes-strimzi
cd part-3/go-client-app


