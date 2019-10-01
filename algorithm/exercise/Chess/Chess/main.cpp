#include <stdio.h>
#include <conio.h>

void Conmmander1();
void Conmmander2();

int main()
{
    //Conmmander1();
    Conmmander2();
    getch();
    return 0;
}

void Conmmander1()
{
    struct {
        unsigned char a:4;
        unsigned char b:4;
    } i;
    for( i.a=1; i.a<=9; i.a++) {
        for( i.b=1; i.b<=9; i.b++) {
            if(i.a%3 != i.b%3) {
                printf("A=%d,B=%d \t",i.a,i.b);
            }
        }
    }
}

void Conmmander2()
{
    char i = 81;
    while(i--) {
        if(i/9%3 == i%9%3)
            continue;
        printf("A=%d,B=%d \t",i/9%3+1,i%9%3+1);
    }
}