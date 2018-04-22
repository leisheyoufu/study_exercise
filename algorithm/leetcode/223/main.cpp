/*
223. Rectangle Area

Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Rectangle Area

Assume that the total area is never beyond the maximum possible value of int.

Credits:
Special thanks to @mithmatt for adding this problem, creating the above image and all test cases.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;



class Solution
{
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
    {
        int area1 = (D-B) * (C-A);
        int area2 = (H-F) * (G-E);
        return area1 + area2 - overlap(A,B,C,D,E,F,G,H);

    }
    int overlap(int A, int B, int C, int D, int E, int F, int G, int H)
    {
        int h1 = max(A, E);
        int h2 = min(C, G);
        int v1 = max(B, F);
        int v2 = min(D, H);
        if (h2 <= h1 || v2 <= v1) {
            return 0;
        }
        return (h2-h1) * (v2-v1);
    }
};

int main()
{
    Solution sln;
    cout << sln.computeArea(-1500000001, 0 , -1500000000, 1, 1500000000, 0, 1500000001, 1) << endl; // 2
    system("pause");
    return 0;
}
