#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<set>

using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

struct Cmp {
    bool operator()(const Point &a, const Point &b) const
    {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

vector<Point> get_points()
{
    vector<vector<int>> points = {{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}};
    vector<Point> pos(points.size());
    for(int i = 0; i<points.size(); i++) {
        pos[i] = Point(points[i][0], points[i][1]);
    }
    return pos;
}

void print_points(vector<Point> &points)
{
    for(auto point:points) {
        cout << point.x << "," << point.y << endl;
    }
}

bool compare(Point &a, Point &b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

void sort_points(vector<Point> &points)
{
    sort(points.begin(), points.end(), compare);
    print_points(points);
}

void set_points(vector<Point> points)
{
    points.push_back(Point(2,0));
    points.push_back(Point(2,4));
    points.push_back(Point(3,4));
    set<Point, Cmp> s;
    for(auto point : points) {
        s.insert(point);
    }
    for(auto point: s) {
        cout << point.x << "," << point.y << endl;
    }
}

int main()
{
    vector<Point> points = get_points();
    //sort_points(points);
    set_points(points);
    system("pause");
    return 0;
}
