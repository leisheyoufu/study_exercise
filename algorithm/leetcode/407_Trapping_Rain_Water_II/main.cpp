/*
407. Trapping Rain Water II

Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.


The above image represents the elevation map [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] before the rain.

After the rain, water is trapped between the blocks. The total volume of water trapped is 4.

*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>

using namespace std;

struct Node {
    int h;
    int i;
    int j;

    bool operator <(const Node a) const
    {
        return h < a.h;
    }
    bool operator >(const Node a) const
    {
        return h >= a.h;
    }
    Node(int h, int i, int j):h(h),i(i),j(j)
    {

    }
};
class Solution
{
public:
    int trapRainWater(vector<vector<int> >& heightMap)
    {
        int m = heightMap.size();
        if(m == 0) {
            return 0;
        }
        int n = heightMap[0].size();
        if (n == 0) {
            return 0;
        }
        vector<vector<bool> > vis(m, vector<bool>(n, false));
        priority_queue<Node, vector<Node>, greater<Node> > q;
        for(int i=0; i<m; i++) {
            for(int j=0; j < n; j++) {
                if(i == 0 || i==m-1 || j==0 || j==n-1) {
                    q.push(Node(heightMap[i][j], i, j));
                    vis[i][j] = true;
                }
            }
        }
        int mx = INT_MIN;
        vector<vector<int> > dirs = {{0,-1},{-1,0},{0,1},{1,0}};
        int ret = 0;
        while(!q.empty()) {
            Node node = q.top();
            q.pop();
            mx = max(mx, node.h);
            for(int k=0; k< dirs.size(); k++) {
                int i = node.i + dirs[k][0];
                int j = node.j + dirs[k][1];
                if(i<0 || i>=m || j<0 || j>=n || vis[i][j]) {
                    continue;
                }
                if(heightMap[i][j] < mx) {
                    ret += mx - heightMap[i][j];
                }
                vis[i][j] = true;
                q.push(Node(heightMap[i][j], i, j));
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    // [[9,9,9,9,9],[9,2,1,2,9],[9,2,8,2,9],[9,2,3,2,9],[9,9,9,9,9]]    57
    system("pause");
    return 0;
}
