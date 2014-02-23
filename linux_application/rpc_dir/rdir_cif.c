 #include<rpc/rpc.h>
 #include<stdio.h>
 #define RPC_CLNT
 #include"rpc_dir.h"

 extern CLIENT *handle;
 static int *ret;

 int rmkdir(char *word)
 {
         char **arg;
         arg = &word;
         ret = rmkdir_1(arg, handle);
         return ret == NULL ? 0 : *ret;
 }

 int rrmdir(char *word)
 {
         char **arg;
         arg = &word;
         ret = rrmdir_1(arg, handle);
         return ret == NULL ? 0 : *ret;
 }
