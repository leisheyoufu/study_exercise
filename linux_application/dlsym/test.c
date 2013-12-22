#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv) {

    int fd = open("dlsym.c", 0);

    if (fd != -1) close(fd);

    return 0;
}
