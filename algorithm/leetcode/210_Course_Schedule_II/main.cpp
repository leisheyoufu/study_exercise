/*
210. Course Schedule II
There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

Example 1:

Input: 2, [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished
             course 0. So the correct course order is [0,1] .
Example 2:

Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both
             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
Hints:

This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
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
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites)
    {
        unordered_map<int, vector<int> > m;
        unordered_map<int, int> inDegree;
        for( auto pre : prerequisites) {
            m[pre.second].push_back(pre.first);
            if(inDegree.find(pre.first) == inDegree.end()) {
                inDegree[pre.first] = 1;
            } else {
                inDegree[pre.first]++;
            }
        }
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(inDegree.find(i) == inDegree.end()) {
                q.push(i);
            }
        }
        vector<int> ret;
        while(!q.empty()) {
            int course = q.front();
            q.pop();
            ret.push_back(course);
            for( auto pre : m[course]) {
                inDegree[pre] --;
                if(inDegree[pre] == 0) {
                    q.push(pre);
                }
            }
        }
        if(ret.size() != numCourses) {
            return vector<int>();
        }
        return ret;
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
