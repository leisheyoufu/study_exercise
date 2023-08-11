pip install passlib
export ANSIBLE_HOST_KEY_CHECKING=False
ansible-playbook -i inventory/hosts password.yaml --extra-vars newpassword=123456