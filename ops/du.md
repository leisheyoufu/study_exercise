## 层级目录大小
du -lh --max-depth=1

du -l --max-depth=1 | sort -rn | head -n 100  // du 不用-h 不会统计为MB, KB的歌是容易排序


## 磁盘在线扩容
yum install -y cloud-utils-growpart
执行以下命令，使用 growpart 工具扩容分区 /dev/vda1。命令中 /dev/vda 与 1 间需使用空格分隔
growpart /dev/vda 1
resize2fs /dev/vda1
df -TH
