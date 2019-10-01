#include <cstdio>
#include <conio.h>
#include <vector>
#include <cstdlib>

using namespace std;


#define INF 999999

struct Edge {
    int id;
    int d;  // 目的端点
    int weight;
    struct Edge *next;
};

struct result {
    int s;
    int d;
};

struct Node {
    struct Edge *next;
};

struct Node nodes[1001];

int N,M;
struct Edge edges[15001];


bool exist(int id,vector<int> node_ids)
{
    for(int i=0; i<node_ids.size(); i++) {
        if(id == node_ids[i]) {
            return true;
        }
    }
    return false;
}

int find_min(int id,vector<int> node_ids)
{
    struct Edge *e = nodes[id].next;
    if(e == NULL) {
        return 0;
    }
    int min = INF;
    int min_id = 0;

    while(e != NULL) {
        int weight = e->weight;
        if( weight < min) {
            int n = e->d;
            if(exist(n,node_ids)) {
                e= e->next;
                continue;
            } else {
                min_id=e->id;
                min=weight;
            }
        }
        e=e->next;
    }

    return min_id;
}





void kruskra()
{
    vector<int> node_ids;
    node_ids.push_back(1);
    vector<int> edge_ids;
    vector<struct result> results;

    int max_weight = 0;

    while(node_ids.size() != N) {
        int min_id=0;
        int weight = INF;
        struct result r;
        for(int i=0; i<node_ids.size(); i++) {
            int id = node_ids[i];
            int n_id = 0;
            if( (n_id = find_min(id,node_ids)) !=0) {
                if(weight > edges[n_id].weight) {
                    min_id = n_id;  //  最小的边id
                    weight =  edges[n_id].weight;
                    r.s = id;
                }
            }
        }
        node_ids.push_back(edges[min_id].d);
        edge_ids.push_back(min_id);

        r.d = edges[min_id].d;

        results.push_back(r);
        if(max_weight < edges[min_id].weight) {
            max_weight = edges[min_id].weight;
        }
    }
    printf("%d\n",max_weight);
    printf("%d\n",edge_ids.size());

    for(int i=0; i<results.size(); i++) {
        printf("%d %d\n",results[i].s,results[i].d);
    }




}


int main()
{
    freopen("test.txt","r",stdin);
    scanf("%d %d",&N,&M);
    int v, w, weight;

    for(int i=0; i<M; i++) {
        scanf("%d %d %d",&v,&w,&weight);
        edges[i+1].id=i+1;
        edges[i+1].d=w;
        edges[i+1].weight = weight;
        struct Edge *e = nodes[v].next;
        if( e == NULL) {
            nodes[v].next = &edges[i+1];
        } else {
            while(e->next != NULL) {
                e = e->next;
            }
            e->next =  &edges[i+1];

        }
    }
    kruskra();






    getch();
    return 0;
}