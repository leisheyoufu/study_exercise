#!/bin/bash
# A tool to force kill k8s namespace
if [ -z "${1}" ] ; then
  echo -e "\nUsage: ${0} <name_of_the_namespace_to_remove_the_finalizer_from>\n"
  echo "Valid cluster names, based on your kube config:"
  kubectl config view -o jsonpath='{"Cluster name\tServer\n"}{range .clusters[*]}{.name}{"\t"}{.cluster.server}{"\n"}{end}'
  exit 1
fi

kubectl proxy --port=8901 &
PID=$!
sleep 1

echo -n 'Current context : '
kubectl config current-context 
read -p "Are you sure you want to remove the finalizer from namespace ${1}? Press Ctrl+C to abort."

kubectl get namespace "${1}" -o json \
            | jq '.spec.finalizers = [ ]' \
            | curl -k \
            -H "Content-Type: application/json" \
            -X PUT --data-binary @- "http://localhost:8901/api/v1/namespaces/${1}/finalize"

kill -15 $PID

# reference https://github.com/kubernetes/kubernetes/issues/60807