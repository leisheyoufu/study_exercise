#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<conio.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Edge;

typedef struct AdjNode {
    int vertex;
    Edge *first;
} AdjNode;

typedef AdjNode AdjList[100];

typedef struct {
    AdjList adjlist;
    int n,e;
} ADJGraph;

void print(ADJGraph *G);


int main()
{
    ADJGraph *G = (ADJGraph*)malloc(sizeof(ADJGraph));
    freopen("test.txt","r+", stdin);
    scanf("%d %d", &G->n, &G->e);
    // read vertex
    for(int i=0; i<G->n; i++) {
        scanf("%d", &G->adjlist[i].vertex);
        G->adjlist[i].first = NULL;

    }
    for(int i=0; i<G->e; i++) {
        Edge *edge = (Edge*)malloc(sizeof(Edge));
        int v1,v2;
        Edge *temp;
        scanf("%d %d", &v1,&v2);
        edge->vertex = v2;
        edge->next = NULL;
        if(G->adjlist[v1].first !=NULL) {
            temp = G->adjlist[v1].first;
            while(temp->next !=NULL) {
                temp = temp->next;
            }
            temp->next = edge;
        } else {
            G->adjlist[v1].first = edge;
        }
    }
    print(G);


    getch();
    return 0;
}

void print(ADJGraph *G)
{
    for(int i=0; i<G->n; i++) {
        printf("%d->",i);
        Edge *temp = G->adjlist[i].first;
        while(temp) {
            printf("%d->",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }


}
