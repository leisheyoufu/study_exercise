查询某哥node关联对pod
kubectl get pods --all-namespaces -o wide --field-selector spec.nodeName=<node>