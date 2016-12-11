#!/bin/bash

export SHELL="/bin/bash"
export NM_HTTP_PORT="8042"
export LOCAL_DIRS="/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019"
export HADOOP_COMMON_HOME="/usr/local/hadoop"
export JAVA_HOME="/usr/java/default"
export NM_AUX_SERVICE_mapreduce_shuffle="AAA0+gAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=
"
export HADOOP_YARN_HOME="/usr/local/hadoop"
export CLASSPATH="$PWD:/usr/local/hadoop/etc/hadoop:/usr/local/hadoop/share/hadoop/common/*:/usr/local/hadoop/share/hadoop/common/lib/*:/usr/local/hadoop/share/hadoop/hdfs/*:/usr/local/hadoop/share/hadoop/hdfs/lib/*:/usr/local/hadoop/share/hadoop/mapreduce/*:/usr/local/hadoop/share/hadoop/mapreduce/lib/*:/usr/local/hadoop/share/hadoop/yarn/*:/usr/local/hadoop/share/hadoop/yarn/lib/*:$HADOOP_MAPRED_HOME/share/hadoop/mapreduce/*:$HADOOP_MAPRED_HOME/share/hadoop/mapreduce/lib/*:job.jar/job.jar:job.jar/classes/:job.jar/lib/*:$PWD/*"
export HADOOP_TOKEN_FILE_LOCATION="/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019/container_1481102906466_0019_01_000001/container_tokens"
export NM_HOST="6bec9d39c4fb"
export APPLICATION_WEB_PROXY_BASE="/proxy/application_1481102906466_0019"
export JVM_PID="$$"
export USER="root"
export HADOOP_HDFS_HOME="/usr/local/hadoop"
export PWD="/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019/container_1481102906466_0019_01_000001"
export CONTAINER_ID="container_1481102906466_0019_01_000001"
export HOME="/home/"
export NM_PORT="39563"
export LOGNAME="root"
export APP_SUBMIT_TIME_ENV="1481271512133"
export MAX_APP_ATTEMPTS="2"
export HADOOP_CONF_DIR="/usr/local/hadoop/etc/hadoop/"
export MALLOC_ARENA_MAX="4"
export LD_LIBRARY_PATH="$PWD"
export LOG_DIRS="/usr/local/hadoop/logs/userlogs/application_1481102906466_0019/container_1481102906466_0019_01_000001"
ln -sf "/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019/filecache/10/job.jar" "job.jar"
hadoop_shell_errorcode=$?
if [ $hadoop_shell_errorcode -ne 0 ]
then
  exit $hadoop_shell_errorcode
fi
ln -sf "/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019/filecache/13/job.xml" "job.xml"
hadoop_shell_errorcode=$?
if [ $hadoop_shell_errorcode -ne 0 ]
then
  exit $hadoop_shell_errorcode
fi
mkdir -p jobSubmitDir
hadoop_shell_errorcode=$?
if [ $hadoop_shell_errorcode -ne 0 ]
then
  exit $hadoop_shell_errorcode
fi
ln -sf "/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019/filecache/11/job.splitmetainfo" "jobSubmitDir/job.splitmetainfo"
hadoop_shell_errorcode=$?
if [ $hadoop_shell_errorcode -ne 0 ]
then
  exit $hadoop_shell_errorcode
fi
mkdir -p jobSubmitDir
hadoop_shell_errorcode=$?
if [ $hadoop_shell_errorcode -ne 0 ]
then
  exit $hadoop_shell_errorcode
fi
ln -sf "/tmp/hadoop-root/nm-local-dir/usercache/root/appcache/application_1481102906466_0019/filecache/12/job.split" "jobSubmitDir/job.split"
hadoop_shell_errorcode=$?
if [ $hadoop_shell_errorcode -ne 0 ]
then
  exit $hadoop_shell_errorcode
fi
exec /bin/bash -c "$JAVA_HOME/bin/java -Dlog4j.configuration=container-log4j.properties -Dyarn.app.container.log.dir=/usr/local/hadoop/logs/userlogs/application_1481102906466_0019/container_1481102906466_0019_01_000001 -Dyarn.app.container.log.filesize=0 -Dhadoop.root.logger=INFO,CLA -Dhadoop.root.logfile=syslog  -Xmx1024m org.apache.hadoop.mapreduce.v2.app.MRAppMaster 1>/usr/local/hadoop/logs/userlogs/application_1481102906466_0019/container_1481102906466_0019_01_000001/stdout 2>/usr/local/hadoop/logs/userlogs/application_1481102906466_0019/container_1481102906466_0019_01_000001/stderr "
hadoop_shell_errorcode=$?
if [ $hadoop_shell_errorcode -ne 0 ]
then
  exit $hadoop_shell_errorcode
fi
