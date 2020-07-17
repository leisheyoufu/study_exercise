## Useful command
docker rm $(docker ps -qf status=exited)  // delete exected containers
docker images | grep none | awk '{print $3}' | xargs docker rmi   // delete <none> image