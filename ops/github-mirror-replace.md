## Useful link

fastgit.org
https://doc.fastgit.org/

cnpmjs.org
https://github.com.cnpmjs.org/

gitclone.com
https://gitclone.com/

gitee
https://gitee.com/mirrors

克隆加速

#原地址
git clone https://github.com/kubernetes/kubernetes.git

#改为
git clone https://github.com.cnpmjs.org/kubernetes/kubernetes.git

#或者
git clone https://hub.fastgit.org/kubernetes/kubernetes.git

#或者
git clone https://gitclone.com/github.com/kubernetes/kubernetes.git

下载加速

#原地址
wget https://github.com/goharbor/harbor/releases/download/v2.0.2/harbor-offline-installer-v2.0.2.tgz

#改为
wget https://hub.fastgit.org/goharbor/harbor/releases/download/v2.0.2/harbor-offline-installer-v2.0.2.tgz

免替换方法

git config --global url."https://github.com/".insteadOf https://github.com.cnpmjs.org/

git clone https://github.com/kubernetes/kubernetes.git

## Reference
https://blog.csdn.net/networken/article/details/105122778