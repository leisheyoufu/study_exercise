#include <stdio.h>
#include <conio.h>
#include "EightDigital.h"
#include "SortQueue.h"
int main()
{
    int a1[3][3]= {{2,8,3},{1,0,4},{7,6,5}};
    int a2[3][3]= {{2,3,8},{1,0,4},{7,6,5}};
    int b[3][3] = {{1,2,3},{8,0,4},{7,6,5}};
    EightDigital *goal = new EightDigital(b);
    EightDigital *digital1 = new EightDigital(a1,goal);
    digital1->father = NULL;

    SortQueue open_queue;
    SortQueue close_queue;

    open_queue.enqueue(digital1);
    EightDigital *X;
    while (X= open_queue.dequeue(),X!=NULL) {
        if(open_queue.equal(X,goal)) {

            printf("ÕÒµ½Â·¾¶\n");
            while(X!=NULL) {
                X->print();
                X= X->father;
            }
            getch();
            return 0;
        }
        X->initChild(goal);
        printf("X\n");
        X->print();
        for( int i=0; i<X->childNum; i++) {

            EightDigital *Y = X->child[i];
            Y->calf(goal);
            printf("Y\n");
            Y->print();

            if(!open_queue.inQueue(Y) && !close_queue.inQueue(Y) ) {

                open_queue.enqueue(Y);
            } else if(open_queue.inQueue(Y)) {
                open_queue.refreshNode(Y);
            } else if(close_queue.inQueue(Y)) {
                if(Y->f < close_queue.getNode(Y)->f) {
                    EightDigital *temp = close_queue.dequeue();
                    open_queue.enqueue(temp);
                }
            }
            close_queue.enqueue(X);
        }
    }





    getch();
    return 0;
}