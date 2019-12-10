## OpaqueEnv
echo -n "passw0rd" | base64
kubectel create -f opaque.yml
kubectl create -f pod.yml
kubectl logs secret-opaque-env-pod -n loch
```
[root@k8sdev secret]# kubectl create -f pod.yml
pod/secret-opaque-env-pod created
[root@k8sdev secret]# kubectl logs secret-opaque-env-pod
Error from server (NotFound): pods "secret-opaque-env-pod" not found
[root@k8sdev secret]# kubectl logs secret-opaque-env-pod -n loch
KUBERNETES_SERVICE_PORT=443
KUBERNETES_PORT=tcp://10.43.0.1:443
HOSTNAME=secret-opaque-env-pod
SHLVL=1
HOME=/root
USERNAME=passw0rd
KUBERNETES_PORT_443_TCP_ADDR=10.43.0.1
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
KUBERNETES_PORT_443_TCP_PORT=443
KUBERNETES_PORT_443_TCP_PROTO=tcp
KUBERNETES_SERVICE_PORT_HTTPS=443
KUBERNETES_PORT_443_TCP=tcp://10.43.0.1:443
KUBERNETES_SERVICE_HOST=10.43.0.1
PWD=/
PASSWORD=passw0rd
```

## OpaqueVolumn
kubectl create -f volpod.yml
kubectl logs secret-opaque-volume -n loch
```
[root@k8sdev secret]# kubectl logs secret-opaque-volume -n loch
password
username
```
Two keys in two files

## Secret
kubectl create secret docker-registry dockersecret --namespace loch --docker-server=172.16.10.190 --docker-username=admin --docker-password=admin123 --docker-email=admin@example.org
```
[root@k8sdev secret]# kubectl get secret dockersecret -n loch -o yaml
apiVersion: v1
data:
  .dockerconfigjson: eyJhdXRocyI6eyIxNzIuMTYuMTAuMTkwIjp7InVzZXJuYW1lIjoiYWRtaW4iLCJwYXNzd29yZCI6ImFkbWluMTIzIiwiZW1haWwiOiJhZG1pbkBleGFtcGxlLm9yZyIsImF1dGgiOiJZV1J0YVc0NllXUnRhVzR4TWpNPSJ9fX0=
kind: Secret
metadata:
  creationTimestamp: "2019-12-10T12:50:06Z"
  name: dockersecret
  namespace: loch
  resourceVersion: "62209"
  selfLink: /api/v1/namespaces/loch/secrets/dockersecret
  uid: 09f28d39-b0ea-4a5d-8903-99917a5f24d7
type: kubernetes.io/dockerconfigjson
```

## ServiceAccount secret
kubectl create serviceaccount cluster-admin-dashboard-sa -n loch
 
kubectl create clusterrolebinding cluster-admin-dashboard-sa \
  --clusterrole=cluster-admin \
  --serviceaccount=default:cluster-admin-dashboard-sa \
  --namespace loch

```
[root@k8sdev secret]# kubectl get secret -n loch | grep cluster-admin-dashboard-sa
cluster-admin-dashboard-sa-token-6nxxx   kubernetes.io/service-account-token   3      51s
```
Serviceaccount will create secret automatically
```
[root@k8sdev secret]# kubectl describe serviceaccount cluster-admin-dashboard-sa
Error from server (NotFound): serviceaccounts "cluster-admin-dashboard-sa" not found
[root@k8sdev secret]# kubectl get serviceaccount cluster-admin-dashboard-sa -o yaml
Error from server (NotFound): serviceaccounts "cluster-admin-dashboard-sa" not found
[root@k8sdev secret]# kubectl get serviceaccount cluster-admin-dashboard-sa -n loch -o yaml
apiVersion: v1
kind: ServiceAccount
metadata:
  creationTimestamp: "2019-12-10T12:54:29Z"
  name: cluster-admin-dashboard-sa
  namespace: loch
  resourceVersion: "62572"
  selfLink: /api/v1/namespaces/loch/serviceaccounts/cluster-admin-dashboard-sa
  uid: 2520c8c4-021a-4d63-9fc4-cd01cb98c4a5
secrets:
- name: cluster-admin-dashboard-sa-token-6nxxx
```