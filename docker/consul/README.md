## start consul and register service
docker run --rm --name consul -p 8500:8500 bitnami/consul:latest

curl -X PUT -d '{"id": "test1","name": "test1","address": "192.168.56.12","port": 9100,"tags": ["service"],"checks": [{"http": "http://192.168.56.12:9100/","interval": "5s"}]}' http://127.0.0.1:8500/v1/agent/service/register

curl http://127.0.0.1:8500/v1/catalog/service/test1


## Reference
https://github.com/bitnami/bitnami-docker-consul