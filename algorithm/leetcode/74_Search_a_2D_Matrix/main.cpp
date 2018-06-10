/*
74. Search a 2D Matrix

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.
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
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        int m = matrix.size();
        if (m == 0) {
            return false;
        }
        int n = matrix[0].size();
        if (n == 0) {
            return false;
        }
        int row = 0;
        if(matrix[0][0] > target) {
            return false;
        }
        if(matrix[m-1][n-1] < target) {
            return false;
        }
        for(int i=1; i<m; i++) {
            if(matrix[i][0] > target) {
                break;
            }
            row++;
        }
        for(int j=0; j<n; j++) {
            if(matrix[row][j] == target) {
                return true;
            } else if(matrix[row][j] > target) {
                return false;
            }
        }
        return false;
    }
};

int main()
{
    Solution sln;
    vector<vector<int>> v (1, vector<int>(2, 1));
    v[0][1] = 3;
    sln.searchMatrix(v, 3);
    system("pause");
    return 0;
}
