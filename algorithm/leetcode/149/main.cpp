/*
Max Points on a Line

Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
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
        while(b!=0) {
            int c = a%b;
            a =b;
            b= c;
        }
        return a;
    }
    int maxPoints(vector<Point>& points)
    {
        int n = points.size();
        int maxn = 0;

        for(int i=0; i<n; i++) {
            Point p1 = points[i];
            int self = 1;
            int samex =0;
            int samey = 0;
            map<pair<int,int>, int> map;
            int count = 0;
            for(int j=0; j<n; j++) {
                if(i==j) {
                    continue;
                }
                Point p2 = points[j];
                if(p2.x == p1.x && p2.y ==p1.y) {
                    self++;
                } else if(p2.y == p1.y) {
                    samey++;
                } else if(p2.x == p1.x) {
                    samex++;
                } else {
                    int g = gcd(p2.y - p1.y,p2.x-p1.x);
                    int a = (p2.y - p1.y)/g;
                    int b = (p2.x-p1.x)/g;
                    float k = (double)(a)/(b);
                    map[make_pair(a,b)]++;
                    count = max(count, map[make_pair(a,b)]);
                }
            }

            maxn = max(self+samex, maxn);
            maxn = max(self+samey,maxn);
            maxn = max(self+count, maxn);
        }
        return maxn;
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
