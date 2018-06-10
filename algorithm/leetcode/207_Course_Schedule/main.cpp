/*
207. Course Schedule
There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

Example 1:

Input: 2, [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
             To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.
Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
 Hints:

This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
Topological sort could also be done via BFS.
*/
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
    {
        unordered_map<int, vector<int> > m; // < pre course, target course>
        unordered_map<int, int> inDegree; // <target course, count pre course>
        for( auto pre : prerequisites) {
            m[pre.second].push_back(pre.first);
            if(inDegree.find(pre.first) == inDegree.end()) {
                inDegree[pre.first] = 1;
            } else {
                inDegree[pre.first] ++;
            }

        }
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(inDegree.find(i) == inDegree.end()) {
                q.push(i);
            }
        }
        int count = 0;
        while(!q.empty()) {
            int course = q.front();
            q.pop();
            count ++;
            for(auto target : m[course]) {
                inDegree[target] --;
                if(inDegree[target] == 0) {
                    q.push(target);
                }
            }
        }
        return count == numCourses;
    }
};
int main()
{
    Solution sln;
    cout << sln.rangeBitwiseAnd(5, 7) << endl; // 4
    cout << sln.rangeBitwiseAnd(0, 1) << endl; // 0
    system("pause");
    return 0;
}
