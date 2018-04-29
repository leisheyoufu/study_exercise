/*
149. Max Points on a Line

Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>

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
    int gcd(int a, int b)
    {
        while(b) {
            int c = b;
            b = a % b;
            a = c;
        }
        return a;
    }
    int maxPoints(vector<Point>& points)
    {
        int n = points.size();
        if (n == 0) {
            return 0;
        }
        int maxX =1, maxY = 1, maxK = 0;
        for(int i=0; i<n; i++) {
            int sameX = 1, sameY = 1, self = 0, sameK = 0;
            map<pair<int, int>, int> m; // unordered_map cause the compile error
            for(int j=i+1; j<n; j++) {
                if(points[i].x == points[j].x) {
                    sameX ++;
                    maxX = max(maxX, sameX);
                }
                if(points[i].y == points[j].y) {
                    sameY ++;
                    maxY = max(maxY, sameY);
                }
                if(points[i].x == points[j].x && points[i].y == points[j].y) {
                    self ++;
                }
                if(points[i].x != points[j].x && points[i].y != points[j].y) {
                    int y = points[i].y - points[j].y;
                    int x = points[i].x - points[j].x;
                    int g = gcd(y, x);
                    pair<int, int> p = make_pair(y/g, x/g);
                    if(m.find(p) != m.end()) {
                        m[p] ++;
                    } else {
                        m[p] = 2;
                    }
                    sameK = max(sameK, m[p]);
                }
            }
            maxK = max(sameK +self, maxK);
        }
        int ret = maxX;
        ret = max(ret, maxY);
        ret = max(ret, maxK);
        return ret;
    }
};
int main()
{
    Solution sln;
    Point p1(0,0);
    Point p2(94911151,94911150);
    Point p3(94911152,94911151);
    vector<Point> v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    cout << sln.maxPoints(v) << endl;
    system("pause");
    return 0;
}
