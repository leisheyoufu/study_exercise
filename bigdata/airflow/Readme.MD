## Airflow Setup
docker pull puckel/docker-airflow
docker run -d -p 8080:8080 -v <dag path for local mathine>:/usr/local/airflow/dags puckel/docker-airflow webserver

Add helloworld.py in that path, then wait several minutes.

## Run dag
airflow list_dags
airflow test Helloworld task_1 2020-02-05


## Refefence
https://github.com/vishalsatam/Data-Pipelining/blob/master/Airflow/AirflowDemo/Helloworld.py
