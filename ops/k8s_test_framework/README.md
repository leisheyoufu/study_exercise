This is some test script, can not run.


## Force delete namespace
kubectl get namespace $NAMESPACE -o json > $NAMESPACE.json
sed -i -e 's/"kubernetes"//' $NAMESPACE.json
kubectl replace --raw "/api/v1/namespaces/$NAMESPACE/finalize" -f ./$NAMESPACE.json

## Detect where block the namespace from being deleted
kubectl api-resources --verbs=list --namespaced -o name | xargs -n 1 kubectl get --show-kind --ignore-not-found -n <terminating-namespace>
kubectl get APIService <version>.<api-resource>
kubectl get APIService v1beta1.custom.metrics.k8s.io
kubectl describe APIService <version>.<api-resource>
kubectl get namespace


## Reference
[Kubernetes Namespaces stuck in Terminating status](https://stackoverflow.com/questions/52954174/kubernetes-namespaces-stuck-in-terminating-status)
[Detect where block the namespace from being deleted](https://www.ibm.com/support/knowledgecenter/SSBS6K_3.2.x/troubleshoot/ns_terminating.html)

