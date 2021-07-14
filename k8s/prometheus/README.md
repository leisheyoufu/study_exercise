## prometheus-operator quickstart

### Start monitor
git clone https://github.com/prometheus-operator/kube-prometheus.git
kubectl create -f consul.yml
kubectl create -f manifests/setup
kubectl create secret generic additional-consul-configs --from-file=config/prometheus-additional-consul.yaml -n monitoring
until kubectl get servicemonitors --all-namespaces ; do date; sleep 1; echo ""; done
kubectl create -f manifests/
kubectl create -f mysql.yml
kubectl create -f mysqld-exportor.yml
kubectl create -f service-monitor.yml

### Access dashboard
prometheus
kubectl --namespace monitoring port-forward --address 0.0.0.0 svc/prometheus-k8s 9090
grafana
kubectl --namespace monitoring port-forward --address 0.0.0.0 svc/grafana 3000   (admin/admin)
alertmanager
kubectl --namespace monitoring port-forward --address 0.0.0.0 svc/alertmanager-main 9093

### grafana process
```
bash-5.0$ COLUMNS=1000 ps -ef
PID   USER     TIME  COMMAND
    1 nobody    1:48 grafana-server --homepath=/usr/share/grafana --config=/etc/grafana/grafana.ini --packaging=docker cfg:default.log.mode=console cfg:default.paths.data=/var/lib/grafana cfg:default.paths.logs=/var/log/grafana cfg:default.paths.plugins=/var/lib/grafana/plugins cfg:default.paths.provisioning=/etc/grafana/provisioning
  145 nobody    0:00 /bin/bash
  235 nobody    0:00 ps -ef

bash-5.0$ cat /etc/grafana/provisioning/dashboards/dashboards.yaml
{
    "apiVersion": 1,
    "providers": [
        {
            "folder": "Default",
            "name": "0",
            "options": {
                "path": "/grafana-dashboard-definitions/0"
            },
            "orgId": 1,
            "type": "file"
        }
    ]
}
bash-5.0$ cat /etc/grafana/provisioning/datasources/datasources.yaml
{
    "apiVersion": 1,
    "datasources": [
        {
            "access": "proxy",
            "editable": false,
            "name": "prometheus",
            "orgId": 1,
            "type": "prometheus",
            "url": "http://prometheus-k8s.monitoring.svc:9090",
            "version": 1
        }
    ]
}

```
### mysqld-exporter docker
```
docker pull prom/mysqld-exporter

docker run -d \
  -p 9104:9104 \
  --network my-mysql-network  \
  -e DATA_SOURCE_NAME="user:password@(hostname:3306)/" \
  prom/mysqld-exporter
```
### Debug
 kubectl logs prometheus-k8s-1 -n monitoring -c prometheus

### Consul
Get services
curl http://consul.loch.svc.cluster.local:8500/v1/catalog/services
curl http://consul.loch.svc.cluster.local:8500/v1/health/service/mysqld-exporter-172.30.12.167

curl -X PUT http://172.30.12.167:8500/v1/agent/service/deregister/node-exporter 

## Delete kube-prometheus
kubectl delete --ignore-not-found=true -f manifests/ -f manifests/setup

## Container
核心指标只包含node和pod的cpu、内存等，一般来说，核心指标作HPA已经足够，但如果想根据自定义指标:如请求qps/5xx错误数来实现HPA，就需要使用自定义指标了，目前Kubernetes中自定义指标一般由Prometheus来提供，再利用k8s-prometheus-adpater聚合到apiserver，实现和核心指标（metric-server)同样的效果。

Prometheus可以采集其它各种指标，但是prometheus采集到的metrics并不能直接给k8s用，因为两者数据格式不兼容，因此还需要另外一个组件(kube-state-metrics)，将prometheus的metrics数据格式转换成k8s API接口能识别的格式，转换以后，因为是自定义API，所以还需要用Kubernetes aggregator在主API服务器中注册，以便直接通过/apis/来访问。


## prometheus adapter
promethues adapter把prometheus的metrics转换为k8s能识别的资源类型， 就能通过api server的接口访问 deployment的资源
···
apiVersion: apiregistration.k8s.io/v1
kind: APIService
metadata:
  name: v1beta1.metrics.k8s.io
spec:
  group: metrics.k8s.io
  groupPriorityMinimum: 100
  insecureSkipTLSVerify: true
  service:
    name: prometheus-adapter
    namespace: monitoring
  version: v1beta1
  versionPriority: 100
···
kubectl proxy --address='0.0.0.0'
curl localhost:8001/apis/metrics.k8s.io/v1beta1/pods
kubectl get --raw /apis/metrics.k8s.io/v1beta1/pods

## metrics-server
namespace terminating
kubectl api-resources --verbs=list --namespaced -o name | xargs -n 1 kubectl get --show-kind --ignore-not-found -n

metrics not available yet
https://www.cnblogs.com/binghe001/p/12821804.html

## Reference
[kube-prometheus](https://github.com/prometheus-operator/kube-prometheus#quickstart)
[github configmap-reload](https://github.com/jimmidyson/configmap-reload)
[grafana allowUiUpdates](https://github.com/grafana/grafana/blob/a45ce365667470725043c6b5053f9415b0eeb53e/devenv/dashboards.yaml)
[mysqld-exporter](https://github.com/prometheus/mysqld_exporter)
[云原生技术](http://www.xuyasong.com/?page_id=1827）
[容器监控实践—Custom Metrics](http://www.xuyasong.com/?p=1520)
[grafana dashboard template](https://grafana.com/grafana/dashboards/8919)
[prometheus serviceaccount](https://yunlzheng.gitbook.io/prometheus-book/part-iii-prometheus-shi-zhan/readmd/service-discovery-with-kubernetes)
[prometheus additionalScrapeConfigs](https://www.cnblogs.com/jayce9102/p/12074361.html)
[prometheus relabel](https://yunlzheng.gitbook.io/prometheus-book/part-ii-prometheus-jin-jie/sd/service-discovery-with-relabel)
[filter consul service based on tag](https://docs.d2iq.com/mesosphere/dcos/services/prometheus/0.1.1-2.3.2/configuration/service-discovery/)
[Monitoring Kafka on Kubernetes with Prometheus](https://medium.com/@agrajm/monitoring-kafka-on-kubernetes-with-prometheus-5b1d1518102)
[kfaka-minion - new kafka exporter](https://github.com/cloudworkz/kafka-minion)
[Kubernetes Apiserver和Extension apiserver的介绍](https://www.yisu.com/zixun/9840.html)