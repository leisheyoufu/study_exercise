## Useful command
docker rm $(docker ps -qf status=exited)  // delete exected containers
docker images | grep none | awk '{print $3}' | xargs docker rmi   // delete <none> image

docker image prune -a --force --filter "label=type=appimage" --filter "until=240h" // 删除无容器使用的镜像，外加条件：创建于10天前、限于应用程序image

## Docker machine no space
https://stackoverflow.com/questions/31909979/docker-machine-no-space-left-on-device
docker rmi $(docker images -q -f "dangling=true")
docker volume rm $(docker volume ls -qf dangling=true)

## Change password in Dockerfile
RUN echo "123456" | chpasswd

## Save and load a docker image
docker tag <image> <target_image>
docker save <target_image> -o /tmp/<target_image>.tar
docker load -i /tmp/<target_image>.tar


## check what container use the docker volume
docker system df -v
docker inspect 805478a1451327de453e2f71c60087079d5d3b9fd1999e47c8cdf77324f8950a
docker ps -a --filter volume=805478a1451327de453e2f71c60087079d5d3b9fd1999e47c8cdf77324f8950a