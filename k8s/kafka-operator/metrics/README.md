## Guide
- Add region label in prometheus metrics
- prometheus-rules is for rules sent to alert manager
- alert manager is a service to alert

## Prometheus part
export region=shenzhen
kubectl delete secret additional-federate-configs -n monitoring
kubectl create secret generic additional-federate-configs --from-file=metrics/manifests/overlays/$region/federate.yaml -n monitoring
kustomize build metrics/manifests/overlays/$region | kubectl apply -f -
kubectl apply -f metrics/manifests/alertmanager-secret.yaml
kubectl apply -f metrics/manifests/alertmanager-alertmanager.yaml
kubectl apply -f metrics/manifests/prometheus-rules.yaml
kustomize build metrics/manifests/overlays/$region | kubectl apply -f -