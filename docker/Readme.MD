## Useful command
docker rm $(docker ps -qf status=exited)  // delete exected containers
docker images | grep none | awk '{print $3}' | xargs docker rmi   // delete <none> image

docker image prune -a --force --filter "label=type=appimage" --filter "until=240h" // 删除无容器使用的镜像，外加条件：创建于10天前、限于应用程序image