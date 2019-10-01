#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <vector>
using namespace std;

FILE *infp,*outfp;

int C,N,M;


typedef struct {
    int flavorid;
    int malted;
} cus;

vector<cus> cus_like[3000];
vector<int> v_satisfy;
int state[3000];
vector<int> cur_satisfy;

bool impossible = false;

void print(int index)
{
    fprintf(outfp,"Case #%d: ",index);
    for(int i=0; i<N; i++) {
        fprintf(outfp,"%d ",state[i]);
    }
    fprintf(outfp,"\n");
}

bool inCur_satisfy(int cusid)
{
    for(int i=0; i<cur_satisfy.size(); i++) {
        if(cur_satisfy[i]==cusid) {
            return true;
        }
    }
    return false;

}

bool inSatisfy(int id)  // ��ĳ��flavor����
{
    for(int i=0; i<v_satisfy.size(); i++) {
        if(v_satisfy[i]==id) {
            return true;
        }
    }
    return false;
}

void distribute(int index)
{
    while(true) {
        for(int i=0; i<M; i++) {
            if(!inSatisfy(i+1)) {
                if(cus_like[i].size()==1 && cus_like[i][0].malted == 1) {
                    state[cus_like[i][0].flavorid-1] = 1; // flavor��1
                    cur_satisfy.push_back(i);
                }
            }
        }

        int num = v_satisfy.size();

        for(int i=0; i<M; i++) {
            if(!inCur_satisfy(i)) {
                vector<cus>::iterator iter2 = cus_like[i].begin();
                while(iter2 !=  cus_like[i].end()) {
                    if( state[ (*iter2).flavorid -1 ] ==1) {
                        if((*iter2).malted == 1) {
                            v_satisfy.push_back((*iter2).flavorid );

                        }
                        if( (*iter2).malted == 0 &&  cus_like[i].size()==1  ) { // &&inSatisfy((*iter2).flavorid)
                            impossible = true;
                        }
                        iter2 = cus_like[i].erase(iter2);

                    } else {
                        iter2++;
                    }
                }// end of while
            }// end of in cus_satisfy
        }// end of for
        if(impossible) {
            fprintf(outfp,"Case #%d: IMPOSSIBLE\n",index);
            return;
        }
        if(num ==v_satisfy.size()) {
            print(index);
            return;
        }


    }//end of while
}

int main()
{
    //infp=fopen("B-small-practice.in","r");
    infp=fopen("B-small-practice.in","r");
    outfp=fopen("out2.txt","w");

    fscanf(infp,"%d",&C);
    for(int i=0; i<C; i++) {
        v_satisfy.clear();

        fscanf(infp,"%d",&N);

        memset(state,0,N*sizeof(int));

        fscanf(infp,"%d",&M);
        for(int j=0; j<M; j++) {
            cus_like[j].clear();

            int temp;
            fscanf(infp,"%d", &temp);
            for(int k=0; k<temp; k++) {
                int flavor_id,cus_malt;
                fscanf(infp,"%d %d",&flavor_id,&cus_malt);
                cus c_temp;
                c_temp.flavorid = flavor_id;
                c_temp.malted = cus_malt;
                cus_like[j].push_back(c_temp);

            }

        }
        impossible = false;
        distribute(i+1);

    }

    getch();
    return 0;
}