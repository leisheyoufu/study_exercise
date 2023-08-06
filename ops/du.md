## 层级目录大小
du -lh --max-depth=1

du -l --max-depth=1 | sort -rn | head -n 100  // du 不用-h 不会统计为MB, KB的歌是容易排序
