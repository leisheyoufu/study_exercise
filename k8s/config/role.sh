# Import cert into k8s for loch
kubectl config set-credentials loch --client-certificate=./loch.crt --client-key=./loch.key --embed-certs=true

# See new user loch was added
kubectl config view

# Add new context for user loch
kubectl config set-context loch@kubernetes --cluster=local --user=loch

# Switch to loch context
kubectl config use-context loch@kubernetes
kubectl config use-context local

# Create role
kubectl create role pods-reader --verb=get,list,watch --resource=pods --dry-run -o yaml > role-demo.yaml
kubectl apply -f role-demo.yaml
kubectl get role
kubectl describe role pods-reader

# Kubectl list all resource names
kubectl api-resources

# Create namespace then create rol in namespace loch
kubectl delete -f role-demo.yaml
kubectl create namespace loch
kubectl create role pods-reader --verb=get,list,watch --namespace loch --resource=pods --dry-run -o yaml > role-loch.yaml
kubectl apply -f role-loch.yaml
kubectl delete -f role-loch.yaml


# Create rolobinding
kubectl create rolebinding loch-read-pods --role=pods-reader --user=loch --dry-run -o yaml > rolebinding-loch.yaml
kubectl apply -f rolebinding-loch.yaml

# Test role binding
kubectl expose deployment hello-world --port=8080 --type=LoadBalancer --dry-run -o yaml > service.yaml
kubectl delete all -n loch --all

kubectl config use-context loch@kubernetes
