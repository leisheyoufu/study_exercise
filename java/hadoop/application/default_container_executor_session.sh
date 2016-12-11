#!/bin/bash

echo $$ > /tmp/hadoop-root/nm-local-dir/nmPrivate/application_1481102906466_0019/container_1481102906466_0019_01_000001/container_1481102906466_0019_01_000001.pid.tmp
/bin/mv -f /tmp/hadoop-root/nm-local-dir/nmPrivate/application_1481102906466_0019/container_1481102906466_0019_01_000001/container_1481102906466_0019_01_000001.pid.tmp /tmp/hadoop-root/nm-local-dir/nmPrivate/application_1481102906466_0019/container_1481102906466_0019_01_000001/container_1481102906466_0019_01_000001.pid
exec setsid /bin/bash "/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019/container_1481102906466_0019_01_000001/launch_container.sh"
