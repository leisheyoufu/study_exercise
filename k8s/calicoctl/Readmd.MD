# Usage of calicoctl command
calicoctl get --help


## Modify ip pool in calico
calicoctl create -f -<<EOF
apiVersion: projectcalico.org/v3
kind: IPPool
metadata:
name: new-pool
spec:
cidr: 10.0.0.0/16
ipipMode: Always
natOutgoing: true
EOF

[root@k8snode1 configmap]# calicoctl get ippool -o yaml
apiVersion: projectcalico.org/v3
items:
- apiVersion: projectcalico.org/v3
  kind: IPPool
  metadata:
    creationTimestamp: 2019-12-10T19:17:13Z
    name: default-ipv4-ippool
    resourceVersion: "1511"
    uid: e030b2ab-bf78-4731-8eb7-bbab13847db9
  spec:
    blockSize: 26
    cidr: 10.42.0.0/16
    ipipMode: Always
    natOutgoing: true
    nodeSelector: all()
    vxlanMode: Never
kind: IPPoolList
metadata:
  resourceVersion: "104395"

### Get node status
[root@k8snode1 configmap]# calicoctl node status
Calico process is running.

IPv4 BGP status
+-----------------+-------------------+-------+----------+-------------+
|  PEER ADDRESS   |     PEER TYPE     | STATE |  SINCE   |    INFO     |
+-----------------+-------------------+-------+----------+-------------+
| 192.168.126.202 | node-to-node mesh | up    | 11:13:49 | Established |
| 192.168.126.203 | node-to-node mesh | up    | 11:13:47 | Established |
+-----------------+-------------------+-------+----------+-------------+

IPv6 BGP status
No IPv6 peers found.

## Reference
[kubernetes Calico网络更改IP池](https://www.cnblogs.com/MinZhou/p/12587651.html)