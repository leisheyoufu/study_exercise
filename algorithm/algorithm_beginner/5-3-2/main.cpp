#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

struct dict {
    char s[100];
    char d[100];
};

void insert_sort(char *src, char *dst)
{
    strcpy(dst,src);

    int len = strlen(dst);
    for(int i=0; i<len; i++) {
        for(int j=len-1; j>i; j--) {
            if(dst[j] < dst[j-1]) {
                swap(dst[j],dst[j-1]);
            }
        }
    }
}


int partition(char A[], int l, int r, char& pivot)
{
    do {             // Move the bounds inward until they meet
        while (A[++l] < pivot);     // Move l right and
        while ((r != 0) && A[--r]> pivot); // r left
        swap(A[l],A[r]);              // Swap out-of-place values
    } while (l < r);              // Stop when they cross
    swap(A[l], A[r]);                // Reverse last, wasted swap
    return l;      // Return first position in right partition
}


void qsort(char A[], int i, int j)   // Quicksort
{
    if (j <= i) return; // Don't sort 0 or 1 Elem
    int pivotindex = (i+j)/2;
    swap(A[pivotindex], A[j]);


    // k will be the first position in the right subarray
    int k = partition(A, i-1, j, A[j]);  // careful
    swap(A[k], A[j]);             // Put pivot in place
    qsort(A, i, k-1);
    qsort(A, k+1,j);
}

void sort(char *src, char *dst)
{
    strcpy(dst,src);
    qsort(dst,0, strlen(dst)-1);
}



bool find_s(struct dict *d, int n,char *str)
{
    bool find = false;
    for(int i=0; i<n; i++) {
        if(strcmp(d[i].d,str) ==0 ) {
            find = true;
            printf("%s ",d[i].s);
        }
    }
    return find;
}


int main()
{
    char word[100];
    struct dict d[100];
    freopen("test.txt","r",stdin);
    int i=0;
    while(scanf("%s",d[i].s) && strcmp(d[i].s,"******") !=0) {
        insert_sort(d[i].s,d[i].d);
        i++;
    }

    while(scanf("%s", word) != EOF) {
        char w[100];
        //insert_sort(word,w);
        sort(word,w);
        if(!find_s(d,i,w))
            printf(":)\n");
        else
            printf("\n");
    }

    return 0;
}
