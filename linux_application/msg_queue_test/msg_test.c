#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
int main ( void )
{
    int qid;
    key_t key;

    key = 113;
    qid=msgget( key, IPC_CREAT | 0666 )�� /*����һ����Ϣ����*/
    if ( qid < 0 ) { /* ����һ����Ϣ����ʧ�� */
        perror ( "msgget" );
        exit (1) ;
    }

    printf ("created queue id : %d /n", qid ); /* �����Ϣ���е�ID */

    system( "ipcs -q" ); /*�鿴ϵͳIPC��״̬*/
    return 0;
}
