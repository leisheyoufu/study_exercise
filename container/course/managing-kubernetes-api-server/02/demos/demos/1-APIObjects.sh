ssh aen@c1-master1
cd ~/content/course/m2/demos

#Get information about our current context, ensure we're logged into the correct cluster.
kubectl config get-contexts

#Change our context if needed.
kubectl config use-context kubernetes-admin@kubernetes

#Get information about the API Server for our current context, which should be kubernetes-admin@kubernetes
kubectl cluster-info

#Get a list of API Resources available in the cluster
kubectl api-resources | more

#Using kubectl explain
kubectl explain pods | more

#Creating a pod with YAML
kubectl apply -f pod.yaml

#Let's look more closely at what we need in pod.spec and pod.spec.containers
kubectl explain pod.spec | more
kubectl explain pod.spec.containers | more

#Get a list of our currently running pods
kubectl get pod 

#Remove our pod
kubectl delete pod hello-world
