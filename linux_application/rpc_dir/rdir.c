/*
Author : chenglong
This is a simple programe to test sunrpc
type
1 dirname  to mkdir a directory
2 dirname  to rma a directory
10 to quit
*/

#include<rpc/rpc.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

#include"rpc_dir.h"

#define MAXWORD 50
#define RMACHINE "127.0.0.1"   /* 服务器端ip address */
CLIENT *handle;


int main(int argc, char **argv)
{
    char word[MAXWORD+1];
    int cmd;
    int wrdlen;
    if(argc >= 2) {
        handle = clnt_create(argv[1], DIRPROG, DIRVERS, "tcp");
    } else{
        handle = clnt_create(RMACHINE, DIRPROG, DIRVERS, "tcp");
    }

    if (handle == NULL) {
        printf("cound not contact remote program.\n");
        exit(1);
    }

    while (1) {
        scanf("%d",&cmd);
        if(cmd == 10)
            exit(0);
        scanf("%s",word);
        switch(cmd) {
        case 1:
            rmkdir(word);
            printf("mkdir dir %s\n",word);
            break;
        case 2:
            rrmdir(word);
            printf("rmdir dir %s\n",word);
            break;
        case 10:
            printf("program quits.\n");
            exit(0);
        default:
            printf("command %d invalid.\n", cmd);
            break;
        }
    }
    return 0;
}

