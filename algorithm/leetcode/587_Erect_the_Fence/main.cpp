/*
587. Erect the Fence

There are some trees, where each tree is represented by (x,y) coordinate in a two-dimensional garden. Your job is to fence the entire garden using the minimum length of rope as it is expensive. The garden is well fenced only if all the trees are enclosed. Your task is to help find the coordinates of trees which are exactly located on the fence perimeter.



Example 1:

Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
Explanation:

Example 2:

Input: [[1,2],[2,2],[4,2]]
Output: [[1,2],[2,2],[4,2]]
Explanation:

Even you only have trees in a line, you need to use rope to enclose them.


Note:

All trees should be enclosed together. You cannot cut the rope to enclose trees that will separate them in more than one group.
All input integers will range from 0 to 100.
The garden has at least one tree.
All coordinates are distinct.
Input points have NO order. No order required for output.
input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};


class Solution
{
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& points)
    {
        vector<Point> pos(points.size());
        for(int i = 0; i<points.size(); i++) {
            pos[i] = Point(points[i][0], points[i][1]);
        }
        vector<Point> ret = _outerTrees(pos);
        vector<vector<int>> res(ret.size(), vector<int>(2));
        for(int i=0; i< ret.size(); i++) {
            res[i][0] = ret[i].x;
            res[i][1] = ret[i].y;
        }
        return res;
    }

    vector<Point> _outerTrees(vector<Point>& points)
    {
        vector<Point> res;
        Point first = points[0];
        int firstIdx = 0, n = points.size();
        for (int i = 1; i < n; ++i) {
            if (points[i].x < first.x) {
                first = points[i];
                firstIdx = i;
            }
        }
        res.push_back(first);
        Point cur = first;
        int curIdx = firstIdx;
        while (true) {
            Point next = points[0];
            int nextIdx = 0;
            for (int i = 1; i < n; ++i) {
                if (i == curIdx) continue;
                int cross = crossProduct(cur, points[i], next);
                if (nextIdx == curIdx || cross > 0 || (cross == 0 && dist(points[i], cur) > dist(next, cur))) {
                    next = points[i];
                    nextIdx = i;
                }
            }
            for (int i = 0; i < n; ++i) {
                if (i == curIdx) continue;
                int cross = crossProduct(cur, points[i], next);
                if (cross == 0) {
                    if (check(res, points[i])) res.push_back(points[i]);
                }
            }
            cur = next;
            curIdx = nextIdx;
            if (curIdx == firstIdx) break;
        }
        return res;
    }



    int crossProduct(Point A, Point B, Point C)
    {
        int BAx = A.x - B.x;
        int BAy = A.y - B.y;
        int BCx = C.x - B.x;
        int BCy = C.y - B.y;
        return BAx * BCy - BAy * BCx;
    }
    int dist(Point A, Point B)
    {
        return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
    }
    bool check(vector<Point>& res, Point p)
    {
        for (Point r : res) {
            if (r.x == p.x && r.y == p.y) return false;
        }
        return true;
    }
};

int main()
{
    Solution sln;
    vector<vector<int>> points = {{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}};
    vector<vector<int>> ret = sln.outerTrees(points);
    for(auto point:points) {
        cout << point[0] << " " << point[1] << endl;
    }
    system("pause");
    return 0;
}
