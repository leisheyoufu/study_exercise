#include<stdio.h>
#include<algorithm>
#include<conio.h>

using namespace std;

int gcd(int a,int b)
{
    do {
        int c = a%b;
        a = b;
        b = c;
    } while(b!=0);
    return a;
}

int gcd2(int a,int b)
{
    int c=a%b;
    if(c!=0) {
        return gcd2(b,c);
    }
    return b;
}


int main()
{
    printf("%d\n",gcd(110,330));
    printf("%d\n",gcd2(110,330));
    getch();
    return 0;
}
