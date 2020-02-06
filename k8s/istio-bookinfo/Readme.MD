## Setup bookinfo
kubectl label namespace default istio-injection=enabled
kubectl get namespace -L istio-injection
kubectl apply -f bookinfo.yml
kubectl apply -f <(istioctl kube-inject -f samples/bookinfo/platform/kube/bookinfo.yaml)  // if auto injection is disabled

## Deploy bookinfo
kubectl apply -f bookinfo.yaml
kubectl exec -it $(kubectl get pod -l app=ratings -o jsonpath='{.items[0].metadata.name}') -c ratings -- curl productpage:9080/productpage | grep -o "<title>.*</title>"
<title>Simple Bookstore App</title>


kubectl get svc productpage -o json | jq .spec.selector
kubectl get po -l app=$(kubectl get svc productpage -o jsonpath='{.spec.selector.app}') -o jsonpath='{.}' // from service to pod
pod=$(kubectl get po -l app=$(kubectl get svc productpage -o jsonpath='{.spec.selector.app}') -o jsonpath='{.items[0].metadata.name}')
kubectl debug --config /root/.kube/config $pod

istioctl proxy-config listeners <pod>

## Gateway , make the resource can be accessed from outside
kubectl apply -f bookinfo-gateway.yaml
kubectl get gateway
kubectl get svc istio-ingressgateway -n istio-system
```
[root@k8sdev istio-bookinfo]# kubectl get svc istio-ingressgateway -n istio-system
NAME                   TYPE           CLUSTER-IP    EXTERNAL-IP   PORT(S)                                                                                                                      AGE
istio-ingressgateway   LoadBalancer   10.43.26.13   <pending>     15020:30213/TCP,80:30736/TCP,443:31884/TCP,15029:31086/TCP,15030:31306/TCP,15031:30666/TCP,15032:32004/TCP,15443:30644/TCP   16d
```

No external loadbalance, use node port
export INGRESS_PORT=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.spec.ports[?(@.name=="http2")].nodePort}')
export SECURE_INGRESS_PORT=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.spec.ports[?(@.name=="https")].nodePort}')
export INGRESS_HOST=$(kubectl get po -l istio=ingressgateway -n istio-system -o jsonpath='{.items[0].status.hostIP}')
export GATEWAY_URL=$INGRESS_HOST:$INGRESS_PORT
curl -s http://${GATEWAY_URL}/productpage | grep -o "<title>.*</title>"

## Destination rule version control
kubectl apply -f destination-rule-all.yaml


## istioctl
istioctl -n istio-system proxy-config listener <pod>
```
istioctl -n istio-system proxy-config listener istio-ingressgateway-649f9646d4-jwl6k
[
    {
        "name": "0.0.0.0_80",
        "address": {
            "socketAddress": {
                "address": "0.0.0.0",
                "portValue": 80
            }
        },
        "filterChains": [
            {
                "filters": [
                    {
                        "name": "envoy.http_connection_manager",
                        "typedConfig": {
                            "@type": "type.googleapis.com/envoy.config.filter.network.http_connection_manager.v2.HttpC                                                                                  onnectionManager",
                            "statPrefix": "outbound_0.0.0.0_80",
                            "rds": {
                                "configSource": {
                                    "ads": {}
                                },
                                "routeConfigName": "http.80"
                            },
   ......
```
istioctl -n istio-system pc clusters istio-ingressgateway-649f9646d4-jwl6k -o json
## Reference

http://blog.daocloud.io/istio-canary-deployment/  使用 Istio 实现应用的金丝雀部署
http://blog.daocloud.io/istio-ingress/   使用 Istio 控制 Ingress 流量
http://blog.daocloud.io/where-is-the-request-1/   Istio 网关中的 Gateway 和 VirtualService 配置深度解析
http://blog.daocloud.io/istio-1-part-2/   // 服务网格内部的 VirtualService 和 DestinationRule 配置深度解析
