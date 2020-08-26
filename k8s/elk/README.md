## Start service in k8s
sysctl -w vm.max_map_count=262144
kubectl create -f ./
kubectl port-forward svc/kibana -n loch --address 0.0.0.0 5601:5601


## filebeat
If -e option is specified, log will be redireccted to stdout
```
logging.level: info
logging.to_files: true
logging.to_syslog: false
logging.files:
  path: /usr/share/filebeat/logs
  name: filebeat.log
```

## Reference
[How to Setup an ELK Stack and Filebeat on Kubernetes](https://www.deepnetwork.com/blog/2020/01/27/ELK-stack-filebeat-k8s-deployment.html)
[docker-compose filebeat](https://github.com/namvu80ap/docker-elk-filebeat)
[通过环境变量将 Pod 信息呈现给容器](https://kubernetes.io/zh/docs/tasks/inject-data-application/environment-variable-expose-pod-information/)