#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<algorithm>

using namespace std;
void swap(int d[], int a, int b)
{
    int temp = d[a];
    d[a] = d[b];
    d[b] = temp;
}

int temp[100];

class Minheap
{
public:
    int sz;
    int *a;
    int maxnum;
    Minheap(int maxnum)
    {
        sz = 0;
        a = new int[maxnum];
        this->maxnum = maxnum;
    }
    ~Minheap()
    {
        delete []a;
    }
    bool isleaf(int pos)
    {
        return pos>=sz/2 && pos<sz;
    }
    bool insert(int num)
    {
        if (sz == maxnum) return false;
        int curr= sz;
        a[sz++] = num;

        while(curr!=0 && a[curr]<a[(curr-1)/2]) {
            swap(a,curr,(curr-1)/2);
            curr = (curr-1)/2;
        }
        return true;
    }
    void siftdown(int pos)
    {
        if (sz == 0 )
            return;
        int lc, rc;
        int temp, m;
        while (!isleaf(pos)) {
            lc = pos*2+1;
            rc = pos*2 +2;
            if (rc<sz && a[rc]<a[lc]) {
                m = rc;
            } else {
                m = lc;
            }
            if(a[m]<a[pos]) {
                swap(a, m, pos);
            }
            pos = m;
        }
    }
    int top()
    {
        return a[0];
    }

    int parent(int pos)
    {
        return (pos-1)/2;
    }

    bool remove(int pos, int &val)
    {
        if(pos<0 || pos >= sz) {
            return false;
        }
        val = a[pos];
        swap(a, pos, --sz);
        int curr = pos;
        while(curr >0 && a[curr]< a[parent(curr)]) {
            swap(a, curr, parent(curr));
            curr = parent(curr);
        }
        siftdown(pos);
        return true;
    }
    void print()
    {
        for(int i=0; i<sz; i++) {
            printf("%d ",a[i]);
        }
    }
    bool isFull()
    {
        return sz==maxnum?true:false;
    }
};

int partition(int a[], int pivot, int left, int right)
{
    while(left<right) {
        while(a[left] < pivot) left++;
        while(a[right] >=pivot) right--;
        if(left<right && a[left]>a[right]) {
            swap(a, left,right);
            left++;
            right--;
        }
    }
    return left;
}
void qsort(int a[], int left, int right)
{
    if (left >= right)
        return;
    int mid = (left+right)/2;
    int pivot = a[mid];
    swap(a,mid,right);
    int k = partition(a,pivot,left,right-1);
    swap(a, k, right);
    qsort(a,left,k-1);
    qsort(a,k+1,right);
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

int main()
{
    int num[] = { 8,9,11,12,15,4,3,98,100,79,88,64,57,37,91, 101, -101};
    //qsort(num, 0, sizeof(num)/sizeof(int)-1);
    //mergesort(num, temp, 0, sizeof(num)/sizeof(int)-1);
    for(int i=0; i<sizeof(num)/sizeof(int); i++) {
        printf("%d ",num[i]);
    }
    /*
    Minheap *heap = new Minheap(5);
    int size = sizeof(num)/sizeof(int);
    int val;
    for(int i=0;i<size;i++) {
    	if(heap->top() < num[i]) {
    		if(heap->isFull()) {
    			heap->remove(0, val);
    		}
    		heap->insert(num[i]);
    	}
    }
    heap->print();
    delete(heap);
    */
    getch();
    return 0;
}
