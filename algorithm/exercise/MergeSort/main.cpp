#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void mergesort(int a[],int temp[],int left,int right);
void swap(int a[], int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int binary_search(int a[], int n,int val)
{
    int left=-1, right=n;

    while(left +1 != right) {
        int mid = (left+right)/2;
        if(a[mid] == val) return mid;
        else if(a[mid] > val) {
            right = mid;
        } else if(a[mid] < val) {
            left = mid;
        }
    }
    return -1;
}

int _partition(int a[], int pivot, int left, int right)
{
    while(left < right) {
        while(a[left] < pivot) {
            left++;
        }
        while(pivot <= a[right]) {
            right--;
        }
        if(left < right && a[left] >a[right]) {
            swap(a, left, right);
            left++;
            right--;
        }
    }
    return left;
}

void qsort(int a[], int left, int right)
{
    if( left >= right)
        return;
    int mid = (left + right)/2;
    int pivot = a[mid];
    swap(a, right, mid);
    int k = _partition(a, pivot, left, right-1);
    swap(a, right, k);
    qsort(a, left, k-1);
    qsort(a, k+1, right);
}

void insert_sort(int a[], int n)
{
    for(int i=1; i<n; i++) {
        for(int j=i; j>=1 && a[j] < a[j-1]; j--) {
            swap(a, j, j-1);
        }
    }
}

void bubble_sort(int a[], int n)
{
    for(int i=0; i<n; i++) {
        for(int j= n-1; j>i; j--) {
            if(a[j] < a[j-1]) {
                swap(a, j, j-1);
            }
        }
    }
}

void select_sort(int a[],int n)
{
    for(int i=0; i<n; i++) {
        int k=i;
        for(int j=i+1; j <n; j++) {
            if(a[j]< a[k]) {
                k = j;
            }
        }
        swap(a, k, i);
    }
}

int main()
{
    int a[] = {31,1,-3,42,25,78,64,3,100, 1000,4};
    int len = sizeof(a)/sizeof(int);
    int *b = (int*)malloc(sizeof(int)*len);
    mergesort(a,b,0,len-1);
    //qsort(a, 0, len-1);
    //insert_sort(a, len);
    //bubble_sort(a, len);
    //select_sort(a, len);

    free(b);

    for(int i=0; i<len; i++) {
        printf("%d ",a[i]);
    }
    printf("\nsearch index = %d\n",binary_search(a, len,52));
    getch();
    return 0;
}

void mergesort(int a[], int temp[],int left, int right)
{
    if(left>= right) {
        return;
    }
    int mid=(left+right)/2;
    mergesort(a,temp, left,mid);
    mergesort(a,temp,mid+1,right);
    for(int i=left; i<=right; i++) {
        temp[i] = a[i];
    }
    int curr, l1=left, l2=mid+1;
    for(curr=left; curr<=right; curr++) {
        if(l1==mid+1) {
            a[curr] = temp[l2++];
        } else if(l2 > right) {
            a[curr] = temp[l1++];
        } else if(temp[l1] > temp[l2]) {
            a[curr] = temp[l2++];
        } else {
            a[curr] = temp[l1++];
        }
    }
}

