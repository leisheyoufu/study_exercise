#include "epoll.h"



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

void close_disable(int sockfd, struct epoll_event ee,struct d_thread *t)
{
    close(sockfd);
    if(remove_fd(t,sockfd) == 0) {
        printf("remove err\n");
    }
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

    ev.data.fd=listenfd;
    ev.events=EPOLLIN|EPOLLET;
    // register listenfd
    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
    return listenfd;
}

int my_accept(int listenfd,int epfd)
{
    struct sockaddr_in clientaddr;
    socklen_t clilen;
    int connfd;

    connfd = accept(listenfd,(struct sockaddr *)&clientaddr, &clilen);
    if(connfd<0) {
        perror("connfd<0");
        exit(1);
    }
    char *str = inet_ntoa(clientaddr.sin_addr);
    printf( "accapt a connection from %s\n",str);
    return connfd;
}

void epoll_add(int socdfd,int epfd)
{
    struct epoll_event ev;
    //set nonblock
    set_nonblock(socdfd);
    ev.data.fd=socdfd;
    // ET trigger
    ev.events=EPOLLIN | EPOLLET;
    // register confd
    epoll_ctl(epfd,EPOLL_CTL_ADD,socdfd,&ev);

}

void my_receive(struct epoll_event *events,char *buf,int epfd,struct d_thread *t)
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
        recv_num = recv(sockfd, head + count, BUF_MAX, 0);
        if(recv_num < 0) {
            if(errno == EAGAIN) {
                // no more data read
                read_ok = 1;
                break;
            } else if (errno == ECONNRESET) {
                // receive RST
                close_disable(sockfd, *events,t);
                printf( "connect part send out RST\n");
                break;
            } else if (errno == EINTR) {
                //signal interrupt
                continue;
            } else {
                close_disable(sockfd, *events,t);
                printf ("unrecovable error\n");
                break;
            }
        } else if( recv_num == 0) {
            // alrady fin
            close_disable(sockfd, *events,t);
            printf("connect part has shut off\n");
            break;
        }
        count += recv_num;
        if ( recv_num == BUF_MAX) {
            continue;  // read util EAGAIN
        } else {
            read_ok = 1;
            break;
        }
    }

    if (read_ok == 1) {
        // read end
        buf[count] = '\0';
        printf( "thread %d have read from the client : %s\n", t->id,buf);
        ev.data.fd=sockfd;
        ev.events = EPOLLOUT | EPOLLET;
        if( epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev)<0) {
            printf("epoll failed fd = %d\n",sockfd);
        }
    }

}

void my_send(struct epoll_event *events,char *msg,int epfd,struct d_thread *t)
{
    int sockfd;
    struct epoll_event ev;
    sockfd = events->data.fd;
    char buf[]="send from server";
    int written = 0;
    int write_len = 0;
    int count = 0;
    char * head = msg;
    while(1) {
        write_len = send(sockfd, head + count, BUF_MAX, 0);
        if (write_len == -1) {
            if (errno == EAGAIN) {
                written = 1;
                break;
            } else if(errno == ECONNRESET) {
                // client send RST
                close_disable(sockfd, *events,t);
                printf ("connect part send out RST\n");
                break;
            } else if (errno == EINTR) {
                // signal interrupt
                continue;
            } else {
            }
        }

        if (write_len == 0) {
            // socket closed
            close_disable(sockfd, *events,t);
            printf( "connect part has shut off\n");
            break;
        }

        count += write_len;
        if (write_len == BUF_MAX) {
            continue;
        } else {
            written = 1;
            break;
        }
    }

    if (written == 1) {
        printf("my send %s\n",head);
        ev.data.fd=sockfd;
        ev.events=EPOLLIN | EPOLLET;
        if(epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev)<0) {
            printf("epoll_ctl failed fd = %d\n",sockfd);
        }
    }

}