/*
218. The Skyline Problem
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).

Buildings  Skyline Contour
The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
*/
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
using namespace std;
struct Point {
    int x;
    int y;
    int index;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Point()
    {

    }
};

struct cmpY {
    bool operator()(Point a,Point b)
    {
        return  a.y < b.y;  //大顶堆
    }
};

bool cmpX(const Point &a,const Point &b)
{
    if(a.x < b.x) {
        return true;
    } else if(a.x == b.x) {
        return a.y > b.y;
    }
    return false;
}

class Solution
{
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
    {
        int n = buildings.size();
        vector<vector<int>> ret;
        if(n == 0) {
            return ret;
        }
        vector<Point> points(2*n);
        for(int i=0; i<2*n; i+=2) {
            points[i] = Point(buildings[i/2][0], buildings[i/2][2]);
            points[i+1] = Point(buildings[i/2][1], -buildings[i/2][2]);
        }
        sort(points.begin(), points.end(), cmpX);

        multiset<int> s = {0};
        int curr = 0;
        for(auto point : points) {
            if(point.y > 0) {
                s.insert(point.y);
            } else {
                s.erase(s.find(-point.y));
            }
            if(curr != *s.rbegin()) {
                ret.push_back(vector<int> {point.x, *s.rbegin()});
                curr = *s.rbegin();
            }
        }
        return ret;

    }
};
int main()
{
    Solution sln;
    vector<vector<int>> buildings = {vector<int>{2,9,10}, vector<int>{3,7,15}, vector<int>{5,12,12}, {15,20,10}, {19,24,8},{21,24,3}};
    vector<vector<int>> ret = sln.getSkyline(buildings);
    for(int i=0; i<ret.size(); i++) {
        cout << "[" << ret[i][0] << " " << ret[i][1] << "], "; // [2 10], [9 0], [3 15], [7 0], [5 12], [12 0], [15 10], [20 0], [19 8], [24 0], [21 3], [24 0],
    }
    cout << endl;
    system("pause");
    return 0;
}
