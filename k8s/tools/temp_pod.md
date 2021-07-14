kubectl run --rm -i --tty busybox --image=busybox:1.28 --restart=Never -- ping 127.0.0.1

"kubectl -n nmspc exec $POD -- bash -c \"export curIP=123 && script01\""
kubectl -n nmspc exec "$POD" -- env curIP=123 script01

runScript() {
  kubectl -n nmspc exec "$POD" -- bash -c 'export curIP=123 && script01 "$@"' _ "$@"
}

runScript --command "do stuff"