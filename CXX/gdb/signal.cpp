#include<iostream>
#include<csignal>
#include<cstdio>
#include <unistd.h>
#include<cstring>

using namespace std;

// void signalProcess(int signalval)
// {
//     //以下代码三选一：
//     //什么都不做或者return		  //1:
//     //exit(1); 					  //2:
//     //signal(signalval, SIG_DFL); //3
// }
bool bRun = true;

void signalProcess(int signalval)
{
    signal(signalval, SIG_DFL);  //必须放在第一行，否则coredump堆栈显示的地址会对应不上
    printf("signal:%d\n", signalval);
    if ((SIGINT == signalval)
        || (SIGQUIT == signalval)
        || (SIGTERM == signalval)
        || (SIGABRT == signalval)) {
        exit(0); //正常退出
    }
    //或者
    bRun = false;
}

void signalRegister(void)
{
	signal(SIGKILL, signalProcess);//执行非法指令
	signal(SIGSEGV, signalProcess);//段错误
	signal(SIGFPE, signalProcess );//算术运算错误
	signal(SIGBUS, signalProcess );//非法地址
    signal(SIGSYS, signalProcess );//非法系统调用
	signal(SIGABRT ,signalProcess);//调用abort函数
	signal(SIGTERM, signalProcess);//程序结束
	signal(SIGINT, signalProcess);//ctrl-c
	signal(SIGQUIT, signalProcess);//ctrl-c
}

int main(void) 
{
    
	signalRegister();
    
//    Logger::setLogFile("test.log");
    printf("WARN\n");
    
    printf("DEBUG\n");

    while (bRun){
        char *p = NULL;
        memset(p, 0u, 1);
        sleep(1);
    }
   
    return 0;
}
