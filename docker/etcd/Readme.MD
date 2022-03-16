docker network create service --subnet 172.16.0.0/16
docker-compose up -d

## defrag
#使用API3
export ETCDCTL_API=3
# 查看告警信息，告警信息一般 memberID:8630161756594109333 alarm:NOSPACE
etcdctl --endpoints=http://127.0.0.1:2379 alarm list

# 获取当前版本
rev=$(etcdctl --endpoints=http://127.0.0.1:2379 endpoint status --write-out="json" | egrep -o '"revision":[0-9]*' | egrep -o '[0-9].*')
# 压缩掉所有旧版本
etcdctl --endpoints=http://127.0.0.1:2379 compact $rev
# 整理多余的空间
etcdctl --endpoints=http://127.0.0.1:2379 defrag
etcdctl --endpoints=http://127.0.0.1:2379 defrag --command-timeout=600s
# 取消告警信息
etcdctl --endpoints=http://127.0.0.1:2379 alarm disarm