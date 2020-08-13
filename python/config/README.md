python3 set_config.py property.conf db.logLevel Info

## Update yaml file
python3 set_config.py conf.yaml common.kafka.brokers kafka:9093
python3 set_config.py conf.yaml loader.etcd.hosts etcd-cluster:2379