## Docker network
docker network create --driver bridge ceph-net
docker network inspect ceph-net
mkdir /etc/ceph
rm -f /etc/ceph/*   // regenerate fsid
mkdir /var/lib/ceph
docker run -d --net=ceph-net -v /etc/ceph:/etc/ceph -v /var/lib/ceph/:/var/lib/ceph/ -e MON_IP=172.19.0.2 -e CEPH_PUBLIC_NETWORK=172.19.0.0/16 --name=mon ceph/daemon:latest-luminous mon
docker exec -ti mon ceph -v
docker exec -ti mon ceph -s

docker rm `docker ps -a | awk '/41ca1a828719/ {print $1}' | tr '\n' ' '`
docker rm `docker ps -a | awk '/ceph/ {print $1}' | tr '\n' ' '`

echo 'alias ceph="docker exec mon ceph"' >> /etc/profile
source /etc/profile
ceph auth get client.bootstrap-osd -o /var/lib/ceph/bootstrap-osd/ceph.keyring

### Create Disk with loop device
dd if=/dev/zero of=/root/ceph/disk/ceph-volumes.img bs=1M count=2048 oflag=direct

### Create Disk (not use)
dd if=/dev/zero of=/root/ceph/disk/ceph-volumes.img bs=1M count=3074 oflag=direct
yum install gdisk
sgdisk -g --clear /root/ceph/disk/ceph-volumes.img
vgcreate ceph-volumes $(losetup --show -f /root/ceph/disk/ceph-volumes.img)
lvcreate -L1G -nceph0 ceph-volumes
lvcreate -L1G -nceph1 ceph-volumes
lvcreate -L1020M -nceph2 ceph-volumes
mkfs.xfs -f /dev/ceph-volumes/ceph0
mkfs.xfs -f /dev/ceph-volumes/ceph1
mkfs.xfs -f /dev/ceph-volumes/ceph2


lvremove ceph0 ceph-volumes

### Start Ceph OSD
dd if=/dev/zero of=/root/ceph/disk/ceph-volumes.img bs=1M count=3074 oflag=direct
LOOPDEV=$(losetup --show -f /root/ceph/disk/ceph-volumes.img)
# losetup -d /dev/loop0
docker run -d --net=ceph-net --privileged=true --pid=host -v /etc/ceph:/etc/ceph -v /var/lib/ceph/:/var/lib/ceph/ -v /dev/:/dev/ -e OSD_DEVICE=$LOOPDEV -e OSD_TYPE=disk -e OSD_FORCE_ZAP=1 --name osd0 ceph/daemon:latest-luminous osd
#docker run -d --net=ceph-net --privileged=true --pid=host -v /etc/ceph:/etc/ceph -v /var/lib/ceph/:/var/lib/ceph/ -v /dev/:/dev/ -e OSD_DEVICE=/dev/loop0 -e OSD_TYPE=disk -e OSD_FORCE_ZAP=1 --name osd0 ceph/daemon:latest-luminous osd
docker run -d --net=ceph-net --privileged=true --pid=host -v /etc/ceph:/etc/ceph -v /var/lib/ceph/:/var/lib/ceph/ -v /dev/:/dev/ -e OSD_DEVICE=/dev/ceph-volumes/ceph1 -e OSD_TYPE=disk -e OSD_FORCE_ZAP=1 --name osd1 ceph/daemon:latest-luminous osd
docker run -d --net=ceph-net --privileged=true --pid=host -v /etc/ceph:/etc/ceph -v /var/lib/ceph/:/var/lib/ceph/ -v /dev/:/dev/ -e OSD_DEVICE=/dev/ceph-volumes/ceph2 -e OSD_TYPE=disk -e OSD_FORCE_ZAP=1 --name osd2 ceph/daemon:latest-luminous osd

docker exec -ti osd1 df | grep "osd"

## Ceph Objecte Operation
ceph osd lspools
ceph quorum_status --format json-pretty
ceph osd pool create pooltest 128
ceph osd pool delete test test --yes-i-really-really-mean-it
ceph osd pool get pooltest size
ceph osd pool set pooltest size 1   // replication number for pool
ceph osd pool set-quota pooltest max_objects 100                              #最大100个对象
ceph osd pool set-quota pooltest max_bytes $((10 * 1024 * 1024 * 1024))       #容量大小最大为10G
ceph osd pool get pooltest pg_num
ceph osd pool set data pg_num = 1   // 修改存储池的PG和PGP




## Reference
[ceph ansible](https://docs.ceph.com/ceph-ansible/master/)
[ceph docker](https://github.com/ceph/ceph-container)
[ceph container bootstrap](https://ceph.io/geen-categorie/bootstrap-your-ceph-cluster-in-docker/)
[csdn ceph docker](https://blog.csdn.net/xingyuzhe/article/details/80324323) // has bug
[ceph docker auth to fix bug](https://www.cnblogs.com/zsl-find/articles/10800285.html)
[docker hub for ceph daemon container](https://hub.docker.com/r/ceph/daemon)
[ceph-disk bug](https://github.com/ceph/ceph-container/pull/1325)
[ceph disk 执行流程](https://blog.csdn.net/quqi99/article/details/81203771)
[ceph test](https://www.cnblogs.com/jinyuanliu/p/10684321.html)
[ceph 常用操作](https://www.cnblogs.com/shuaiyin/p/11043441.html)