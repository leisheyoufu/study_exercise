## Setup ansible
pip3 install ansible

## Run command with ansible adhoc 
ansible all -m ping
ansible node -m ping

ansible node -a 'docker images'
ansible all -a 'df -h'

ansible all -m shell -a 'docker images | grep loch'
ansible all -m shell -a "docker images | grep loch | awk '{print \3}'"  // list all the docker image ids containing loch, be careful about single and double quotes

ansible all -m shell -a "docker images | grep loch | awk '{print \$3}' | xargs docker rmi"
## Reference
[ansible官网](https://docs.ansible.com/ansible/latest/user_guide/intro_getting_started.html)