FROM ubuntu:latest

ENV DEBIAN_FRONTEND noninteractive

RUN echo "mysql-server mysql-server/root_password password 123456" | debconf-set-selections
RUN echo "mysql-server mysql-server/root_password_again password 123456" | debconf-set-selections


RUN apt-get update \
    && apt-get install -y vim \
    && apt-get install -y tree \
    && apt-get install -y net-tools \
    && apt-get install -y git \
    && apt-get install -y nginx \
    && apt-get install -y redis-server \
    && apt-get install -y python3.7 \
    && apt-get install -y python3-pip \
    && apt-get install -y mysql-server \
    && apt-get install -y openssh-server \
    && apt install -y mysql-client \
    && apt install -y libmysqlclient-dev \
    && mkdir /var/run/sshd \
    && echo 'root:123456' | chpasswd \
    && sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config \
    && sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd \
    && echo "export VISIBLE=now" >> /etc/profile

EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]
