#include <stdio.h>
#include <conio.h>

int Factorial(int n);
int GetZeroNumber1(int num);
int GetZeroNumber2(int n);
int GetZeroNumber3(int n);


int GetOneBitOffset(int n);
int GetLowestOneBit(int n);

int main()
{
    int num = Factorial(14);
    printf("Factorial = %d\n",num);

    printf("Method 1:Number of Zero = %d\n", GetZeroNumber1(num));
    printf("Method 2:Number of Zero = %d\n",GetZeroNumber2(25));

    printf("Method 3:Number of Zero = %d\n",GetZeroNumber3(25));


    printf("Method 1 offset = %d\n",GetOneBitOffset(25));
    printf("Method 2 offset = %d\n",GetLowestOneBit(25));
    getch();
    return 0;
}

int Factorial(int n)
{
    if(n==1) {
        return 1;
    }
    return n*Factorial(n-1);
}

int GetZeroNumber1(int num)
{
    int factor = 1;
    int i = -1;
    for( i=-1; num%factor==0; i++) {
        factor*=10;
    }
    return i;
}
// 按贡献5的数量
int GetZeroNumber2(int n)
{
    int ret = 0;
    while(n) {
        ret += n/5;
        n/=5;
    }
    return ret;
}
// 质因式分解后 计算5的质因式数目
int GetZeroNumber3(int n)
{
    int ret =0;
    int j;
    for(int i=1; i<=n; i++) {
        j=i;
        while(j%5==0) {
            ret++;
            j/=5;
        }
    }
    return ret;
}
// 法1
int GetOneBitOffset(int n)
{
    int ret = 0;
    for(int i=1; i<=n; i++) {
        int j = i;
        while(j%2== 0) {
            ret ++;
            j/=2;
        }
    }
    return ret;
}
//法2
int GetLowestOneBit(int n)
{
    int ret =0;
    while(n) {
        n>>=1;
        ret +=n;
    }
    return ret;
}