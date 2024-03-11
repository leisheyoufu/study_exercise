查询某哥node关联对pod
kubectl get pods --all-namespaces -o wide --field-selector spec.nodeName=<node>

kubectl run busybox --image=busybox:1.34 -n <namespace> --overrides='{"spec": { "nodeSelector": {"kubernetes.io/hostname": "<nodename>"}}}' --command -- sleep 3600

kubectl port-forward <podname> 18888:38090 -n <namespace> // 其中18888为本地端口号，38090为pod内的端口号

kubectl get cm yaml-config -n mysql -o jsonpath='{.data}' | jq -r 'to_entries | map("  \(.key): \(.value)") | .[]' > /tmp/mysql.yaml // 按格式保持缩进获取configmap的内容