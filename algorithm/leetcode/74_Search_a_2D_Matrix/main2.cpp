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
        if(m == 0) {
            return false;
        }
        int n = matrix[0].size();
        if (n== 0) {
            return false;
        }
        int m1=0, m2=m-1, n1=0, n2=n-1, mid;
        while(m1<=m2) {
            mid = (m1+m2)/2;
            if(matrix[mid][0] == target) {
                return true;
            } else if(matrix[mid][0] < target) {
                if(matrix[mid][n-1] >= target) {
                    break;
                } else {
                    m1 = mid + 1;
                }
            } else {
                m2 = mid-1;
            }
        }
        if(m2 == -1) {
            return false;
        }
        m1 = mid;
        while(n1<=n2) {
            mid = (n1+n2)/2;
            if(matrix[m1][mid] == target) {
                return true;
            } else if(matrix[m1][mid] < target) {
                n1 = mid+1;
            } else {
                n2 = mid-1;
            }
        }
        return false;
    }
};

int main()
{
    Solution sln;
    int a[][4] = {{1,3,5,7}, {10,11,16,20}, {23,30,34,50}};
    vector<vector<int>> v (3, vector<int>(4, 0));
    for(int i=0; i<3; i++) {
        for(int j=0; j<4; j++) {
            v[i][j] = a[i][j];
        }
    }
    cout << sln.searchMatrix(v, 1) << endl; //true
    system("pause");
    return 0;
}
