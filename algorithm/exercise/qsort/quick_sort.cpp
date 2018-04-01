#include<iostream>
#include<algorithm>

using namespace std;

int partition(int a[], int l, int r, int pivot)
{
    do {
        while(a[++l] < pivot);
        while(r>0 && a[--r] > pivot);
        swap(a[l], a[r]);
    } while(l<r);
    swap(a[l], a[r]);
    return l;
}

void qsort(int a[], int left, int right)
{
    if(left>=right) {
        return;
    }
    int pivotindex = (left+right)/2;
    swap(a[right], a[pivotindex]);
    int k = partition(a, left-1, right, a[right]);
    swap(a[k], a[right]);
    qsort(a, left, k-1);
    qsort(a, k+1, right);
}

void sort(int a[], int n)
{
    qsort(a, 0, n-1);
}

int main()
{
    int a[] = {1,3,5,1,2,4,6,7,0,9,8};
    int n = sizeof(a)/sizeof(int);
    sort(a, n);
    for(int i=0; i<n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
