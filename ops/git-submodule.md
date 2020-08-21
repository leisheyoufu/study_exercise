## 添加 gitsubmodule 和初始化
git clone --recurse-submodules <main_project_url>  # 获取主项目和所有子项目源码
git submodule update --remote <submodule_name> 

cd my_project/
git submodule add https://github.com/tensorflow/tensorflow.git my_tensorflow
git submodule update --init --recursive

### 更新submodule源码，默认更新的branch是master，如果要修改branch，在.gitmodule中设置
git submodule update --remote <submodule_name>  
### 更新所有submodule源码，默认更新.gitmodule中设置的跟踪分支，未设置则跟踪master
git submodule update --remote  
### 当submodule commits提交有问题的时候放弃整个push
git push --recurse-submodules=check
### 分开提交submodule和main project
git push --recurse-submodules=on-demand

## 例如我的子模块是tensorflow
rm -rf tensorflow  # 删除子模块目录文件
vim .gitmodules # 移除子模块的索引信息
vim .git/config # 移除子模块的配置信息
rm -rf .git/modules/tensorflow # 移除子模块的其他信息
git rm --cached tensorflow

## .gitmodule示例
[submodule "modules/tensorflow"]
	path = modules/tensorflow
	url = https://github.com/tensorflow/tensorflow.git
	branch = dev