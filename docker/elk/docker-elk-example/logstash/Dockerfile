FROM docker.elastic.co/logstash/logstash:7.1.1

LABEL maintainer="genius840215@163.com"

COPY ./config /usr/share/logstash/config
COPY ./pipeline /usr/share/logstash/pipeline

USER root

RUN echo "Asia/Shanghai" > /etc/timezone

USER logstash