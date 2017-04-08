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
        vector<vector<int>> ret(n, vector<int>(n, 0));
        int num = 1;
        int count = 0;
        int x=0, y = 0;
        while(count < n*n) {
            // right
            while( x<n && ret[y][x]==0) {
                ret[y][x] = ++count;
                x++;
            }
            x--;
            y++;
            // down
            while(y<n && ret[y][x]== 0) {
                ret[y][x] = ++count;
                y++;
            }
            y--;
            x--;
            //left
            while(x>=0 &&  ret[y][x]== 0) {
                ret[y][x] = ++count;
                x--;
            }
            x++;
            y--;
            // up
            while(y>=0 && ret[y][x]== 0) {
                ret[y][x] = ++count;
                y--;
            }
            y++;
            x++;
        }
        return ret;
    }


};
int main()
{
    Solution sln;
    sln.generateMatrix(5);
    system("pause");
    return 0;
}
