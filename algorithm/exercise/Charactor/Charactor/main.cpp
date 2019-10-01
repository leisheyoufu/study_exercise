#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include<iostream>

using namespace std;

#define CHARASUM 10


struct Charactor {
    string charactor;
    int value;
};

struct Person {
    set<struct Charactor> s;
};

int last;
int start;
//Charactor c[3][10] ={{{"美丽",90},{"冷淡",-60},{"外向",-5},{"乐观",20}},{{"美丽",10},{"冷淡",20}},{{"外向",20},{"乐观",-5}}};
int n ;

Charactor **c;

void InitCharactorSet(set<string> &total,Charactor **c,int n)
{
    for(int i=0; i<n; i++) {
        for(int j=0; j<CHARASUM; j++) {
            if( !c[i][j].charactor.empty())
                total.insert(c[i][j].charactor);
        }

    }
}

void BackTrack(int k,int p[],set<string> total,string mark[],int &max,string store[]);
int getCharactorPoint(Charactor **c,string charactor,int index);
bool isMarked(string mark[],string des);
bool insertMark(string mark[],string value);
bool eraseMark(string mark[],string value);



int main()
{

    scanf("%d %d %d",&n,&start,&last);
    c=(Charactor**)malloc(sizeof(Charactor*)*n);
    for(int i=0; i<n; i++) {
        *(c+i)=(Charactor*)malloc(sizeof(Charactor)*CHARASUM);

    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<CHARASUM; j++) {
            c[i][j].charactor = string("aa");
        }
    }




    set<string> total;


    int p[3] = {0};
    string store[CHARASUM];
    string mark[CHARASUM];
    for(int i=0; i<CHARASUM; i++) {
        mark[i]="";
    }
    int max = -255;
    InitCharactorSet(total,c,n);
    BackTrack(0,p,total,mark,max, store);

    printf("%d\n",max);
    for(int i=0; i<CHARASUM; i++) {
        if(store[i].length()!=0) {
            //printf("%s\n",store[i]);
            cout << store[i] << " ";
        }
    }
    cout << endl;





    system("PAUSE");
    return 0;
}

void BackTrack(int k,int p[],set<string> total,string mark[],int &max,string store[])
{
    if(k>last) {

        return;
    }

    if(k>=start && k<=last) {

        int min = 1000;
        for(int i=0; i<n; i++) {
            if(min > p[i]) {
                min = p[i];
            }
        }
        if(max <min) {
            max = min;
            for(int i=0; i<CHARASUM; i++) {
                store[i] = mark[i];
            }
        }

    }

    set<string>::iterator iter;
    for(iter = total.begin(); iter!=total.end(); iter++) {
        if(!isMarked(mark,*iter)) {
            int point;
            insertMark(mark,*iter);
            for(int i=0; i<n; i++) {
                point = getCharactorPoint(c,*iter,i);
                p[i]+=point;

            }

            BackTrack(k+1,p,total,mark,max,store);
            for(int i=0; i<n; i++) {
                point = getCharactorPoint(c,*iter,i);
                p[i]-=point;

            }
            eraseMark(mark,*iter);


        }
    }

}

int getCharactorPoint(Charactor **c,string charactor,int index)
{
    for(int i=0; i<CHARASUM; i++) {
        if(charactor.compare(c[index][i].charactor) == 0) {
            return c[index][i].value;
        }
    }
    return 0;

}

bool isMarked(string mark[],string des)
{
    for(int i=0; i<CHARASUM; i++) {
        if(des.compare(mark[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool insertMark(string mark[],string value)
{
    int i=0;
    for( i=0; i<CHARASUM; i++) {
        if(mark[i].length() == 0) {
            mark[i] = value;
            break;
        }
    }
    i++;
    while(i!=CHARASUM) {
        mark[i]="";
        i++;
    }
    return false;
}

bool eraseMark(string mark[],string value)
{
    int j=0;
    for(int i=0; i<CHARASUM; i++) {
        if(value.compare(mark[i])==0) {
            mark[i].clear();
            j=i;
            break;
        }
    }
    while(j<CHARASUM-1) {
        mark[j] = mark[j+1];
        j++;
    }
    return true;
}