#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


#define MIN(A,B) ((A)<(B)?(A):(B))
#define MAX(A,B) ((A)>(B)?(A):(B))
struct Line {
    int start;
    int end;
};

struct Link {
    struct Line *l;
    struct Link *next;
};

struct Link *head;
struct Link *cur;


void insert(  struct Line *l2) // l2 是要插入的
{
//	bool intersect  = false;
    cur = head;
    while( cur!=NULL) {

        struct Line *l1 = cur->l;
        if(l1->end >l2->start) {
            l1->start = MIN(l1->start,l2->start);
            l1->end = MAX(l1->end,l2->end);

        } else {
            struct Link *temp = (struct Link*)malloc(sizeof(struct Link));
            temp->l = l2;
            temp->next = cur->next;
            cur->next = temp;
        }

        cur = cur->next;
    }
}


int main()
{
    //	struct Line *line = (struct Line*)malloc(sizeof(struct Line));

    struct Line l1;
    l1.start = 3;
    l1.end = 5;

    struct Line l_array[5];

    l_array[0].start = 1;
    l_array[0].end = 3;

    l_array[1].start = 2;
    l_array[1].end = 3;

    l_array[2].start =2;
    l_array[2].end=5;

    l_array[3].start = -1;
    l_array[3].end = 2;

    l_array[4].start = 7;
    l_array[4].end = 9;

    head = (struct Link*)malloc(sizeof(struct Link));
    head->l = &l1;
    head->next = NULL;

    for(int i=0; i<5; i++) {
        insert(&l_array[i]);
    }

    cur = head;
    while(cur!=NULL) {
        printf("(%d,%d)\n",cur->l->start,cur->l->end);
        cur = cur->next;
    }




    getch();
    return 0;
}