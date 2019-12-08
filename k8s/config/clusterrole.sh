#!/bin/bash
# Create cluster role
kubectl create clusterrole cluster-read --verb=get,list,watch --resource=pods,deploy,svc -o yaml > clusterrole-demo.yaml
kubectl get clusterrole

# Create clusterrolebinding
kubectl create clusterrolebinding loch-read-pods-deploy-svc --clusterrole=cluster-read --user=loch --dry-run -o yaml > clusterrolebinding-demo.yaml
kubectl get clusterrolebinding

# Get pod,deploy,svc with loch user
kubectl config use-context loch@kubernetes
kubectl get deploy -n kube-system
kubectl get svc --all-namespaces