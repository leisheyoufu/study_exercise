#include<rpc/rpc.h>
#define RPC_SVC

#include"rpc_dir.h"
static int retcode;

int rmkdir(char *word);
int rrmdir(char *word);


int *rmkdir_1_svc(char **w, struct svc_req* rqstp)
{
    retcode = rmkdir(*(char**)w);
    return &retcode;
}

int *rrmdir_1_svc(char **w, struct svc_req* rqstp)
{
    retcode = rrmdir(*(char**)w);
    return &retcode;
}

