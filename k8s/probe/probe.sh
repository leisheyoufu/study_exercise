kubectl describe pod liveness -n loch

# Deployment will roll back to v1 due to liveness probe failure
kubectl create -f appv1.yml
kubectl apply 0f appv2.yml