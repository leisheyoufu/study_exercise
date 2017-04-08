/*
54. Spiral Matrix

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
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

    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        vector<int> ret;
        int m = matrix.size();
        if(m==0) {
            return ret;
        }
        int n = matrix[0].size();
        int x=0, y = 0;
        int count = 0;
        vector<vector<int>> temp = matrix;
        while(count < m*n) {
            // right
            while(x<n && temp[y][x] == matrix[y][x]) {
                ret.push_back(temp[y][x]);
                temp[y][x] = matrix[y][x]-1;
                x++;
                count ++;
            }
            x--;
            y++;
            // down
            while(y<m && temp[y][x] == matrix[y][x]) {
                ret.push_back(temp[y][x]);
                temp[y][x] = matrix[y][x]-1;
                y++;
                count ++;
            }
            y--;
            x--;
            //left
            while(x>=0 && temp[y][x] == matrix[y][x]) {
                ret.push_back(temp[y][x]);
                temp[y][x] = matrix[y][x]-1;
                x--;
                count ++;
            }
            x++;
            y--;
            // up
            while(y>=0 && temp[y][x] == matrix[y][x]) {
                ret.push_back(temp[y][x]);
                temp[y][x] = matrix[y][x]-1;
                y--;
                count ++;
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
    int matrix[][3] = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> v(3, vector<int>(3));
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            v[i][j] = matrix[i][j];
        }
    }
    sln.spiralOrder(v);
    system("pause");
    return 0;
}
