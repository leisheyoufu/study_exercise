## Replace docker image version with sed
```
sed -i "s/6.2.2/7.1.1/g" `grep "6.2.2" -rl .`
```
## Elasticsearch
curl "localhost:9200/_cat/indices?v"
curl -X GET "localhost:9200/metricbeat-7.1.1-2020.03.11-000001/_search?q=*&pretty"

## Reference
https://blog.51cto.com/13555423/2442499?source=dra   docker-compose elk7.1
https://www.cnblogs.com/hellxz/p/11059360.html   elk  kafka manualy
https://github.com/wilfordw/docker-elk-example/  docker compose for elk github repo