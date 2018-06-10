/*
240. Search a 2D Matrix II

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Example 1:

Input: matrix, target = 5
Output: true
Example 2:

Input: matrix, target = 20
Output: false
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool dfs(vector<vector<int>>& matrix, int left, int right, int up, int down, int target)
    {
        if(left > right || up > down) {
            return false;
        }
        int mid1 = (left + right)/2;
        int mid2 = (up + down)/2;
        if(matrix[mid2][mid1] == target) {
            return true;
        }
        if(matrix[mid2][mid1] < target) {
            if(!dfs(matrix, mid1+1, right, up, down,target)) {
                return dfs(matrix, left, right, mid2+1, down, target);
            } else {
                return true;
            }
        } else {
            if(!dfs(matrix, left, mid1-1, up, down,target)) {
                return dfs(matrix, left, right, up, mid2-1, target);
            } else {
                return true;
            }
        }
        return false;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        int m = matrix.size();
        if (m == 0) {
            return false;
        }
        int n = matrix[0].size();
        if(n == 0) {
            return false;
        }
        return dfs(matrix, 0, n-1, 0, m-1, target);
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
