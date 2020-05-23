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

    //设置与要处理的事件相关的文件描述符
    ev.data.fd=listenfd;
    //设置要处理的事件类型
    ev.events=EPOLLIN;//|EPOLLET;
    //ev.events=EPOLLIN;

    //注册epoll事件
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
    //设置用于读操作的文件描述符

    set_nonblock(connfd);
    ev.data.fd=connfd;
    //设置用于注测的读操作事件

    ev.events=EPOLLIN ;//| EPOLLET;
    //ev.events=EPOLLIN;

    //注册ev
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
        // 确保sockfd是nonblocking的
        recv_num = recv(sockfd, head + count, BUF_MAX, 0);
        if(recv_num < 0) {
            if(errno == EAGAIN) {
                // 由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读
                // 在这里就当作是该次事件已处理处.
                read_ok = 1;
                break;
            } else if (errno == ECONNRESET) {
                // 对方发送了RST
                close_disable(sockfd, *events);
                printf( "connect part send out RST\n");
                break;
            } else if (errno == EINTR) {
                // 被信号中断
                continue;
            } else {
                //其他不可弥补的错误
                close_disable(sockfd, *events);
                printf ("unrecovable error\n");
                break;
            }
        } else if( recv_num == 0) {
            // 这里表示对端的socket已正常关闭.发送过FIN了。
            close_disable(sockfd, *events);
            printf("connect part has shut off\n");
            break;
        }

        // recv_num > 0
        count += recv_num;
        if ( recv_num == BUF_MAX) {
            continue;   // 需要再次读取
        } else {
            // 安全读完
            read_ok = 1;
            break; // 退出while(1),表示已经全部读完数据
        }
    }

    if (read_ok == 1) {
        // 安全读完了数据
        buf[count] = '\0';

        printf( "we have read from the client : %s\n", buf);
        //设置用于写操作的文件描述符

        ev.data.fd=sockfd;
        //设置用于注测的写操作事件

        ev.events = EPOLLOUT ;//| EPOLLET;
        //修改sockfd上要处理的事件为EPOLLOUT


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
        // 确保sockfd是非阻塞的
        write_len = send(sockfd, head + count, BUF_MAX, 0);
        if (write_len == -1) {
            if (errno == EAGAIN) {
                // 对于nonblocking 的socket而言，这里说明了已经全部发送成功了
                written = 1;
                break;
            } else if(errno == ECONNRESET) {
                // 对端重置,对方发送了RST
                close_disable(sockfd, *events);
                printf ("connect part send out RST\n");
                break;
            } else if (errno == EINTR) {
                // 被信号中断
                continue;
            } else {
                // 其他错误
            }
        }

        if (write_len == 0) {
            // 这里表示对端的socket已正常关闭.
            close_disable(sockfd, *events);
            printf( "connect part has shut off\n");
            break;
        }

        // 以下的情况是write_len > 0
        count += write_len;
        if (write_len == BUF_MAX) {
            // 可能还没有写完
            continue;
        } else { // 0 < write_len < MAXLINE
            // 已经写完了
            written = 1;
            break; // 退出while(1)
        }
    }

    if (written == 1) {
        //设置用于读操作的文件描述符
        ev.data.fd=sockfd;

        //设置用于注测的读操作事件
        ev.events=EPOLLIN; //| EPOLLET;


        //设置用于注测的读操作事件


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

    //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件

    struct epoll_event events[20];
    //生成用于处理accept的epoll专用的文件描述符
    epfd=epoll_create(256);
    listenfd = my_listen(epfd,portnumber);
    for ( ; ; ) {

        //等待epoll事件的发生

        nfds=epoll_wait(epfd,events,20,-1);
        //处理所发生的所有事件

        for(i=0; i<nfds; ++i) {
            if(events[i].data.fd==listenfd) { //如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
                my_accept(listenfd, epfd);
            } else if(events[i].events & EPOLLIN) { //如果是已经连接的用户，并且收到数据，那么进行读入。
                my_receive( &events[i],line,epfd);
            } else if(events[i].events & EPOLLOUT) { // 如果有数据发送
                my_send( &events[i],line,epfd);
            } else if(events[i].events & EPOLLOUT) {
                close_disable(events[i].data.fd, events[i]);
            }
        }
    }
    return 0;
}
