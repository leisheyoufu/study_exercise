/*
59. Spiral Matrix II

Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:

    vector<vector<int>> generateMatrix(int n)
    {
        vector<vector<int>> m(n, vector<int>(n,0));
        int i, c = 0, l = 0, r = n-1, u = 0, d = n-1;
        while(c<n*n) {
            // to right
            i = l;
            while( i <= r) {
                m[u][i++] = ++c;
            }
            // down
            i = ++u;
            while(i<=d) {
                m[i++][r] = ++c;
            }
            if (c == n*n) {
                return m;
            }
            //left
            i = --r;
            while(i>=l) {
                m[d][i--] = ++c;
            }
            // up
            i = --d;
            while(i>=u) {
                m[i--][l] = ++c;
            }
            i = ++l;
        }
        return m;
    }
};
int main()
{
    Solution sln;
    sln.generateMatrix(5);
    system("pause");
    return 0;
}
