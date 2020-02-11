kubectl create ns airflow
kubectl apply -f airflow.yml

## Debug
kubectl debug airflow-deploy-5d8c4f9d9c-lrmsk --config /root/.kube/config -n airflow