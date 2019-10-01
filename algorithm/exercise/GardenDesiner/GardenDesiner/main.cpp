

#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace std;

double mean(int a[],int first,int end)
{
    int n = end-first+1;
    int sum=0;
    for(int i=first-1; i<end; i++) {
        sum+=a[i];
    }
    return (double)sum/n;
}

void check_first(int a[],int &first,int end)
{
    if(mean(a,first,end)<mean(a,first+1,end)) {
        first = first+1;
    }

}

int check_next(double lastvalue,int a[],int first,int end)
{
    if(lastvalue<mean(a,first,end)) {
        return end;
    }
    return -1;

}

void print(int a[],int first,int end)
{
    for(int i=first-1; i<end; i++) {
        cout << a[i] << " ";
    }
}

int main()
{
    int m,n;
    scanf("%d%d",&n,&m);
    int *a = (int*)malloc(sizeof(int)*n);
    for(int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }


    int first =1;
    int end = m;
    int temp = 0;

    double lastvalue = mean(a,first,end);
    for(int e = m+1; e <=n; e++) {
        if((temp = check_next(lastvalue,a,first,e)) != -1) {
            end = temp;
            lastvalue =  mean(a,first,end);
        } else if(a[end-1]>a[first-1]) {
            first++;
            end++;
            lastvalue =  mean(a,first,end);

        }

        if(end-first+1 >m) {
            check_first(a,first,end);
            lastvalue =  mean(a,first,end);
        }



    }

    print(a,first,end);


    getch();
    return 0;
}