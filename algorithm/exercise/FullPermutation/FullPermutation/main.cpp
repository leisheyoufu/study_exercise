#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;


void printArray(char *array)
{
    printf("%s",array);
}
void perm(int start,int end,char array[]);
void swap(int a,int b,char array[]);


int main()
{
    char array[]="maryy";
    vector<char*> string_vec;
    char *a = (char*)malloc(sizeof(char)*4);
    strcpy(a,"aaa");

    string_vec.push_back(a);
    a = (char*)malloc(sizeof(char)*4);

    strcpy(a,"bbb");


    string_vec.push_back(a);
    /*
    vector<char *>::iterator charIter = find(string_vec.begin(),string_vec.end(),"bbb");
    if(charIter !=string_vec.end())
    	cout << *charIter <<endl;
    	*/

    vector<char*>::iterator iter;
    for (iter=string_vec.begin(); iter!=string_vec.end(); iter++) {
        cout<<*iter<<endl;
    }

    printf("sizeof %d\n",sizeof(array));
    perm(0,sizeof(array)-1,array);
    getch();
    return 0;
}

void perm(int start,int end,char array[])
{
    if(start >= end) {
        printArray(array);
        printf("\n");
        return;
    } else {
        for(int i=start; i<end; i++) {
            swap(start,i,array);
            perm(start+1,end,array);
            swap(i,start,array);
        }
    }
}

void swap(int a,int b,char array[])
{
    char temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}