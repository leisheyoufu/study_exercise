#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define PRINT_DEBUG

/*
 * Parse a string which was returned from backtrace_symbols() to get the symbol name
 * and the offset.
 */

void parseStrings(char * stackFrameString, char * symbolString, char * offsetString)
{
    char *        symbolStart = NULL;
    char *        offsetStart = NULL;
    char *        offsetEnd = NULL;
    unsigned char stringIterator = 0;

    //iterate over the string and search for special characters
    for(char * iteratorPointer = stackFrameString; *iteratorPointer; iteratorPointer++) {
        //The '(' char indicates the beginning of the symbol
        if(*iteratorPointer == '(') {
            symbolStart = iteratorPointer;
        }
        //The '+' char indicates the beginning of the offset
        else if(*iteratorPointer == '+') {
            offsetStart = iteratorPointer;
        }
        //The ')' char indicates the end of the offset
        else if(*iteratorPointer == ')') {
            offsetEnd = iteratorPointer;
        }

    }
    //Copy the symbol string into an array pointed by symbolString
    for(char * symbolPointer = symbolStart+1; symbolPointer != offsetStart; symbolPointer++) {
        symbolString[stringIterator] = *symbolPointer;
        ++stringIterator;
    }
    //Reset string iterator for the new array which will be filled
    stringIterator = 0;
    //Copy the offset string into an array pointed by offsetString
    for(char * offsetPointer = offsetStart+1; offsetPointer != offsetEnd; offsetPointer++) {
        offsetString[stringIterator] = *offsetPointer;
        ++stringIterator;
    }
}

static void print_reason(int sig)
{
    void *array[10];
    size_t size;
    size = backtrace(array, 10);
#ifdef PRINT_DEBUG
    char **strings;
    int i;
    strings = backtrace_symbols(array, size);
    printf("Obtained %d stack frames.\n", (int)size);
    for (i = 0; i < size; i++)
        printf("%s\n", strings[i]);


    char cmd[128] = "addr2line -C -f -e ";
    char* prog = cmd + strlen(cmd);  // CL: put the pointer to the end of cmd array
    // int readlink(const char * path, char * buf, size_t bufsiz);
    readlink("/proc/self/exe", prog, sizeof(cmd) - strlen(cmd) - 1);// cl: get programe name
    // now cmd is "addr2line -C -f -e /root/projects/study_exercise/linux_application/backtrace/sigsabort"
    for (i = 0; i < size; ++i) {
        char       symbolString[75] = {'\0'};
        char       offsetString[25] = {'\0'};
        char       printArray[128] = {0};
        parseStrings(strings[i], symbolString, offsetString);

        sprintf(printArray, "%s %s",cmd, offsetString);
        FILE *fp = popen(printArray,"r");
        char buf[256];

        while(fgets(buf,MAX_LINE,fp) != NULL)
        {
            fgets(buf,256,fp);
            printf("%s",buff);
        }
        pclose(fp);
    }
    free(strings);
#else
    int fd = open("err.log", O_CREAT | O_WRONLY);
    backtrace_symbols_fd(array, size, fd);
    close(fd);
#endif
    exit(0);
}
void die()
{
    char *test1;
    char *test2;
    char *test3;
    char *test4 = NULL;
    strcpy(test4, "ab");
}
void test1()
{
    die();
}
int main(int argc, char **argv)
{
    struct sigaction myAction;
    myAction.sa_handler = print_reason;
    sigemptyset(&myAction.sa_mask);
    myAction.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGSEGV, &myAction, NULL); // 无效内存引用
    sigaction(SIGABRT, &myAction, NULL); // 异常终止
    test1();
}