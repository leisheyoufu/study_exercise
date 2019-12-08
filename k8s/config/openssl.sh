#!/bin/bash
# Create openssl cert for loch user
mkdir -p ~/kuberole && cd ~/kuberole
umask 077;openssl genrsa -out loch.key 2048
openssl req -new -key loch.key -out loch.csr -subj "/CN=loch"

# Sign ssl key with k8s ca cert
openssl x509 -req -in loch.csr -CA /etc/kubernetes/ssl/kube-ca.pem -CAkey /etc/kubernetes/ssl/kube-ca-key.pem -CAcreateserial -out loch.crt -days 365

# Just print out the content of loch.crt
openssl x509 -in magedu.crt -text -noout
