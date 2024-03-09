#include <stdio.h>
#include "include/math.h"

int main(int argc, char *argv[]) {

    int a = 20;
    int b = 10;

    printf("sum: %d\n", sum(a, b));
    printf("sub: %d\n", sub(a, b));
    printf("mul: %d\n", mul(a, b));
    printf("div: %d\n", div(a, b));

    return 0;
}