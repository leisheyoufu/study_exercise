#include "daemon.h"



struct d_thread t_fds[THREAD_NUM];
struct d_thread main_fds;
pthread_t t[THREAD_NUM];

void init_thread()
{
    int i;
    for(i=0; i<THREAD_NUM; i++) {
        pthread_mutex_init(&t_fds[i].wait_mutex, NULL);
        pthread_create(&t[i],NULL,(void*)child_thread,i);
    }
}

int select_tfd(struct d_thread* fds)
{
    int min =0;
    int i;
    for(i= 1; i<THREAD_NUM; i++) {
        if(fds[i].size <fds[min].size) {
            min = i;
        }
    }
    return min;
}
void child_thread(int t_index)
{
    int epfd,nfds,i;
    struct epoll_event events[EPOLL_EVENT_SIZE];
    char rcv_buf[BUF_MAX];
    char send_buf[BUF_MAX];

    //�������ڴ���accept��epollר�õ��ļ�������
    epfd=epoll_create(256);
    printf("thread %d created epfd %d\n",t_index,epfd);
    t_fds[t_index].epfd = epfd;
    t_fds[t_index].id = t_index;
    sprintf(send_buf,"thread %d send",t_index);
    for ( ; ; ) {
        nfds=epoll_wait(epfd,events,EPOLL_EVENT_SIZE,100);
        //�����������������¼�

        for(i=0; i<nfds; ++i) {
            if(events[i].events & EPOLLIN) { //������Ѿ����ӵ��û��������յ����ݣ���ô���ж��롣
                my_receive( &events[i],rcv_buf,epfd,&t_fds[t_index]);
            } else if(events[i].events & EPOLLOUT) { // ��������ݷ���
                my_send( &events[i],send_buf,epfd,&t_fds[t_index]);
            }
        }

    }

}


void main_thread(int portnumber)
{
    int i, listenfd,epfd,nfds;
    char line[BUF_MAX];
    //����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ������¼�

    struct epoll_event events[EPOLL_EVENT_SIZE];
    //�������ڴ���accept��epollר�õ��ļ�������
    epfd=epoll_create(256);
    listenfd = my_listen(epfd,portnumber);
    init_thread();
    for ( ; ; ) {
        // wait
        nfds=epoll_wait(epfd,events,EPOLL_EVENT_SIZE,-1);
        //�����������������¼�

        for(i=0; i<nfds; ++i) {
            if(events[i].data.fd==listenfd) { //����¼�⵽һ��SOCKET�û����ӵ��˰󶨵�SOCKET�˿ڣ������µ����ӡ�
                int connfd;
                int t_index;
                int n;
                connfd = my_accept(listenfd, epfd);
                t_index = select_tfd(t_fds);
                if(insert_fd(&t_fds[t_index],connfd) == 1) {
                    epoll_add(connfd,t_fds[t_index].epfd);
                } else {
                    printf("thread %d: too many connection\n",t_index);
                    close(connfd);
                }
            }
        }
    }


}


void daemonize()
{


}
int main()
{
    main_thread(SERV_PORT);


    return 0;
}
