# Build docker file locally
docker build -t hello-node:v1 .

# Check if a process is running in docker
docker ps -q | xargs docker inspect --format '{{.State.Pid}}, {{.Name}}' | grep "PID"

# k8s run hello-node image
kubectl run hello-node --image=hello-node:latest --port=8080 --image-pull-policy=Never  --namespace loch
kubectl expose deployment hello-node --port=8080 --target-port=8080 -n loch
#!/bin/bash
# Get cluster ip and access with curl
kubectl get service -n loch

# List all the fileds in service/hello-node
kubectl get -o template service/hello-node -n loch --template={{.}}
clusterip=`kubectl get -o template service/hello-node --template={{.spec.clusterIP}} -n loch`
port=`kubectl get -o template service/hello-node --template={{.spec.port}} -n loch`


# json path
port=`kubectl get service/hello-node -o jsonpath='{.spec.ports[0].port}' -n loch`
curl $clusterip:$port  # should print out hello-world

# Customize column name
name=`kubectl get po -n loch -o jsonpath='{.items[*].metadata.name}'`
kubectl get po $name -o custom-columns=HOST-IP:.status.hostIP,POD-IP:.status.podIP -n loch

# expose nodePort
kubectl delete service hello-node -n loch
kubectl expose deployment hello-node --type=NodePort -n loch  # randam node port , can not specify with this command
