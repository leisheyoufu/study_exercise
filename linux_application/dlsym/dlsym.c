#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int (*realopen)(const char *pathname, int flags);
int (*realclose)(int fd);

int open(const char *pathname, int flags) {

    void *handle;
    char *error;

    handle = dlopen("libc.so.6", RTLD_LAZY);

    if ((error = dlerror()) != NULL) {
        puts(error);
        exit(-1);
    }

    realopen = dlsym(handle, "open");

    if ((error = dlerror()) != NULL) {
        puts(error);
        exit(-1);
    }

    fputs("you will open the file: ", stderr);
    puts(pathname);

    return realopen(pathname, flags); // old open
}

int close(int fd) {

    void *handle;
    char *error;

    handle = dlopen("libc.so.6", RTLD_LAZY);

    if ((error = dlerror()) != NULL) {
        puts(error);
        exit(-1);
    }

    realclose = dlsym(handle, "close");

    if ((error = dlerror()) != NULL) {
        puts(error);
        exit(-1);
    }

    printf("the file's fd you will close is: %d\n", fd);

    return realclose(fd);
}
