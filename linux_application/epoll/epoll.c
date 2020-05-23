#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define BUF_MAX 512
#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000

void set_nonblock(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0) {
        perror("fcntl(sock,GETFL)");
        return;
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0) {
        perror("fcntl(sock,SETFL,opts)");
        return;
    }
}

void close_disable(int sockid, struct epoll_event ee)
{
    close(sockid);
    ee.data.fd = -1;
}

int my_listen(int epfd,int portnumber)
{
    int listenfd;

    struct sockaddr_in serveraddr;
    struct epoll_event ev;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port=htons(portnumber);
    // bind and listen
    bind(listenfd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(listenfd, LISTENQ);

    //������Ҫ������¼���ص��ļ�������
    ev.data.fd=listenfd;
    //����Ҫ������¼�����
    ev.events=EPOLLIN;//|EPOLLET;
    //ev.events=EPOLLIN;

    //ע��epoll�¼�
    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
    return listenfd;
}

int my_accept(int listenfd,int epfd)
{
    struct sockaddr_in clientaddr;
    socklen_t clilen;
    int connfd;
    struct epoll_event ev;
    connfd = accept(listenfd,(struct sockaddr *)&clientaddr, &clilen);
    if(connfd<0) {
        perror("connfd<0");
        exit(1);
    }


    char *str = inet_ntoa(clientaddr.sin_addr);
    printf( "accapt a connection from %s\n",str);
    //�������ڶ��������ļ�������

    set_nonblock(connfd);
    ev.data.fd=connfd;
    //��������ע��Ķ������¼�

    ev.events=EPOLLIN ;//| EPOLLET;
    //ev.events=EPOLLIN;

    //ע��ev
    epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
    return connfd;

}

void my_receive(struct epoll_event *events,char *buf,int epfd)
{
    int sockfd;
    struct epoll_event ev;

    if ( (sockfd = events->data.fd) < 0)
        return;
    char * head = buf;
    int recv_num = 0;
    int count = 0;
    int  read_ok = 0;
    while(1) {
        // ȷ��sockfd��nonblocking��
        recv_num = recv(sockfd, head + count, BUF_MAX, 0);
        if(recv_num < 0) {
            if(errno == EAGAIN) {
                // �����Ƿ�������ģʽ,���Ե�errnoΪEAGAINʱ,��ʾ��ǰ�������������ݿɶ�
                // ������͵����Ǹô��¼��Ѵ���.
                read_ok = 1;
                break;
            } else if (errno == ECONNRESET) {
                // �Է�������RST
                close_disable(sockfd, *events);
                printf( "connect part send out RST\n");
                break;
            } else if (errno == EINTR) {
                // ���ź��ж�
                continue;
            } else {
                //���������ֲ��Ĵ���
                close_disable(sockfd, *events);
                printf ("unrecovable error\n");
                break;
            }
        } else if( recv_num == 0) {
            // �����ʾ�Զ˵�socket�������ر�.���͹�FIN�ˡ�
            close_disable(sockfd, *events);
            printf("connect part has shut off\n");
            break;
        }

        // recv_num > 0
        count += recv_num;
        if ( recv_num == BUF_MAX) {
            continue;   // ��Ҫ�ٴζ�ȡ
        } else {
            // ��ȫ����
            read_ok = 1;
            break; // �˳�while(1),��ʾ�Ѿ�ȫ����������
        }
    }

    if (read_ok == 1) {
        // ��ȫ����������
        buf[count] = '\0';

        printf( "we have read from the client : %s\n", buf);
        //��������д�������ļ�������

        ev.data.fd=sockfd;
        //��������ע���д�����¼�

        ev.events = EPOLLOUT ;//| EPOLLET;
        //�޸�sockfd��Ҫ������¼�ΪEPOLLOUT


        if( epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev)<0) {
            printf("epoll failed fd = %d\n",sockfd);
        }
    }

}

void my_send(struct epoll_event *events,char *msg,int epfd)
{
    int sockfd;
    struct epoll_event ev;
    sockfd = events->data.fd;
    char buf[]="send from server";
    int written = 0;
    int write_len = 0;
    int count = 0;
    char * head = buf;
    while(1) {
        // ȷ��sockfd�Ƿ�������
        write_len = send(sockfd, head + count, BUF_MAX, 0);
        if (write_len == -1) {
            if (errno == EAGAIN) {
                // ����nonblocking ��socket���ԣ�����˵�����Ѿ�ȫ�����ͳɹ���
                written = 1;
                break;
            } else if(errno == ECONNRESET) {
                // �Զ�����,�Է�������RST
                close_disable(sockfd, *events);
                printf ("connect part send out RST\n");
                break;
            } else if (errno == EINTR) {
                // ���ź��ж�
                continue;
            } else {
                // ��������
            }
        }

        if (write_len == 0) {
            // �����ʾ�Զ˵�socket�������ر�.
            close_disable(sockfd, *events);
            printf( "connect part has shut off\n");
            break;
        }

        // ���µ������write_len > 0
        count += write_len;
        if (write_len == BUF_MAX) {
            // ���ܻ�û��д��
            continue;
        } else { // 0 < write_len < MAXLINE
            // �Ѿ�д����
            written = 1;
            break; // �˳�while(1)
        }
    }

    if (written == 1) {
        //�������ڶ��������ļ�������
        ev.data.fd=sockfd;

        //��������ע��Ķ������¼�
        ev.events=EPOLLIN; //| EPOLLET;


        //��������ע��Ķ������¼�


        if(epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev)<0) {
            printf("epoll_ctl failed fd = %d\n",sockfd);
        }

    }

}




int main()
{
    int i, listenfd,epfd,nfds, portnumber;
    char line[BUF_MAX];
    portnumber = 5000;

    //����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ������¼�

    struct epoll_event events[20];
    //�������ڴ���accept��epollר�õ��ļ�������
    epfd=epoll_create(256);
    listenfd = my_listen(epfd,portnumber);
    for ( ; ; ) {

        //�ȴ�epoll�¼��ķ���

        nfds=epoll_wait(epfd,events,20,-1);
        //�����������������¼�

        for(i=0; i<nfds; ++i) {
            if(events[i].data.fd==listenfd) { //����¼�⵽һ��SOCKET�û����ӵ��˰󶨵�SOCKET�˿ڣ������µ����ӡ�
                my_accept(listenfd, epfd);
            } else if(events[i].events & EPOLLIN) { //������Ѿ����ӵ��û��������յ����ݣ���ô���ж��롣
                my_receive( &events[i],line,epfd);
            } else if(events[i].events & EPOLLOUT) { // ��������ݷ���
                my_send( &events[i],line,epfd);
            } else if(events[i].events & EPOLLOUT) {
                close_disable(events[i].data.fd, events[i]);
            }
        }
    }
    return 0;
}
