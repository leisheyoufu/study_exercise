## Node1 (as server)
cd /codes/<project>
git init
git config --local user.name leisheyoufu
git config --local user.email clscu@live.cn
git commit -m "create project for git bare"

cd ..
git clone --bare <project> <project.git>

cd <project>
git remote add origin /codes/<project.git>
git push origin master
git branch --set--upstream-to=origin/master master

## Node2
git clone ssh://<username>@<ip>:<port>/codes/<project.git>