#include<rpc/rpc.h>
#include<string.h>
#include"rpc_dir.h"

int rmkdir(char *word)
{
    int ret;
    char cmd[256];
    strcpy(cmd,"mkdir ");
    strcat(cmd,word);
    ret = system(cmd);
    return ret;
}

int rrmdir(char *word)
{
    int ret;
    char cmd[256];
    strcpy(cmd,"rm -r ");
    strcat(cmd,word);
    ret = system(cmd);
    return ret;
}



