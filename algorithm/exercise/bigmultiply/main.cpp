#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<algorithm>

using namespace std;

char a[]= "700";
char b[] = "70";

int* tonumber(char *s)
{
    int len = strlen(s);
    int *num =(int*)malloc(sizeof(int)*len);
    for(int i=0; i<len; i++) {
        num[i] = s[i] -'0';
    }
    return num;
}

char * tochar(int *num, int len)
{
    char *s = (char*)malloc(sizeof(char)*(len+1));
    int k=0;
    for(int i=len-1; i>=0; i--) {
        if(num[i] ==0) {
            k=i;
        } else {
            break;
        }
    }
    for(int i=0; i<len-k-1; i++) {
        s[i] = num[len-i+k-1]+'0';
    }
    s[len-k-1] = '\0';
    return s;
}

char *multiply(char *a, char *b)
{
    int *x = tonumber(a);
    int *y =tonumber(b);
    int l1 = strlen(a);
    int l2 = strlen(b);
    int len = l1 +l2 +1;
    int *result = (int*)malloc(sizeof(int)*len);
    memset(result, 0, sizeof(int)*len);

    for(int i=l1-1; i>=0; i--) {
        for(int j=l2-1; j>=0; j--) {
            result[len-i-j-2] += x[i]*y[j];
            result[len-i-j-1] +=result[len-i-j-2]/10;
            result[len-i-j-2] %=10;
        }
    }
    for(int i=0; i<len; i++) {
        result[i+1] += result[i]/10;
        result[i] = result[i]%10;
    }
    char *s = tochar(result, len);
    free(x);
    free(y);
    free(result);
    return s;

}

int main()
{
    char *s = multiply(a,b);
    printf("%s\n", s);
    free(s);
    getch();
    return 0;
}
