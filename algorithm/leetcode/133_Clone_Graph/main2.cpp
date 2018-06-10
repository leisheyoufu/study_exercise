/*
133. Clone Graph
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<cstdio>

using namespace std;
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution
{
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
    {
        if (!node) {
            return NULL;
        }
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m;
        queue<UndirectedGraphNode*> q;
        q.push(node);
        UndirectedGraphNode* ret = new UndirectedGraphNode(node->label);
        UndirectedGraphNode* copy;
        m[node] = ret;
        while(!q.empty()) {
            UndirectedGraphNode* curr = q.front();
            q.pop();
            for( auto neighbor : curr->neighbors) {
                if (m.find(neighbor) == m.end()) {
                    copy = new UndirectedGraphNode(neighbor->label);
                    m[neighbor] = copy;
                    q.push(neighbor);
                } else {
                    copy = m[neighbor];
                }
                m[curr]->neighbors.push_back(copy);
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    UndirectedGraphNode n1 (1);
    UndirectedGraphNode n2(2);
    UndirectedGraphNode n3 (3);
    n1.neighbors.push_back(&n2);
    n1.neighbors.push_back(&n3);
    n2.neighbors.push_back(&n3);
    n3.neighbors.push_back(&n3);
    sln.cloneGraph(&n1);
    system("pause");
    return 0;
}
