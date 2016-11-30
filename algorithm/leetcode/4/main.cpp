#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include <map>
#include<conio.h>

using namespace std;

double findKth(int A[], int n1, int B[], int n2, int k)
{
    if(n1>n2) {
        return findKth(B,n2,A,n1,k);
    }
    if(n1 == 0 ) {
        return B[k-1];
    }
    if(k==1) {
        return min(A[0],B[0]);// as k==1, pa=0, it should be the return condition.
    }
    int pa = min(k/2,n1), pb = k-pa;
    if(A[pa-1] < B[pb-1]) {
        return findKth(A+pa, n1-pa,B,n2,k-pa);
    } else if(A[pa-1] > B[pb-1]) {
        return findKth(A,n1,B+pb,n2-pb, k-pb);
    } else {
        return A[pa-1];
    }

}

double findMedianSortedArrays(vector<int> A, vector<int> B)
{
    int n1= A.size();
    int n2 = B.size();
    int total = n1+n2;
    if (total&0x01) {
        if(n1==0) {
            return B[total/2];
        } else if(n2==0) {
            return A[total/2];
        }
        return findKth(&A[0],n1,&B[0],n2,total/2+1);
    } else {
        if(n1==0) {
            return (B[total/2]+B[total/2-1])/2.0;
        } else if(n2==0) {
            return (A[total/2]+A[total/2-1])/2.0;
        }
        return (findKth(&A[0],n1,&B[0],n2,total/2) + findKth(&A[0],n1,&B[0],n2,total/2+1))/2.0;
    }
}

int main()
{
    vector<int> A;
    A.push_back(1);
    A.push_back(3);

    vector<int> B;
    B.push_back(2);
    printf("%f\n",findMedianSortedArrays(A,B));
    getch();
    return 0;
}
