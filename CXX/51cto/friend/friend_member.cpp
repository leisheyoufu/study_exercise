// 友元成员函数

#include "A.h"
#include "B.h"

int main() {

    B().func(A());

    return EXIT_SUCCESS;
}