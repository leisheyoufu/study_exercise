## Setup helm
$ curl -fsSL -o get_helm.sh https://raw.githubusercontent.com/helm/helm/master/scripts/get-helm-3
$ chmod 700 get_helm.sh
$ ./get_helm.sh

## Spark
$ helm repo add bitnami https://charts.bitnami.com/bitnami
$ helm install my-release bitnami/spark   // spark will be installed
$ helm delete my-release --purge  // uninstall spark Use the option --purge to delete all persistent volumes too.

## Port-Forward to access spark ui
Web UI port is 8080 in pod configration
```
- env:
    - name: SPARK_MODE
      value: master
    - name: SPARK_DAEMON_MEMORY
    - name: SPARK_MASTER_PORT
      value: "7077"
    - name: SPARK_MASTER_WEBUI_PORT
      value: "8080"
    image: docker.io/bitnami/spark:3.0.0-debian-10-r0
```
kubectl port-forward service/my-release-spark-master-svc 7000:7077  // port forward service
kubectl port-forward my-release-spark-master-0 --address 0.0.0.0 7000:8080  // with this we can access web ui from broswer

kubectl scale statefulset/my-release-spark-worker --replicas=1  // scale the worker, then we will see the worker node is dead

[spark 3.0.0 - bitnami](https://hub.helm.sh/charts/bitnami/spark)
[Helm install](https://helm.sh/docs/intro/install/)