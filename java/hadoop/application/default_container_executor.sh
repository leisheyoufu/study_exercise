#!/bin/bash
/bin/bash "/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019/container_1481102906466_0019_01_000001/default_container_executor_session.sh"
rc=$?
echo $rc > "/tmp/hadoop-root/nm-local-dir/nmPrivate/application_1481102906466_0019/container_1481102906466_0019_01_000001/container_1481102906466_0019_01_000001.pid.exitcode.tmp"
/bin/mv -f "/tmp/hadoop-root/nm-local-dir/nmPrivate/application_1481102906466_0019/container_1481102906466_0019_01_000001/container_1481102906466_0019_01_000001.pid.exitcode.tmp" "/tmp/hadoop-root/nm-local-dir/nmPrivate/application_1481102906466_0019/container_1481102906466_0019_01_000001/container_1481102906466_0019_01_000001.pid.exitcode"
exit $rc
