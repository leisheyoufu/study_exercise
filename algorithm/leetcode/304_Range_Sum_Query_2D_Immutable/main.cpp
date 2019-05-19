/*
304. Range Sum Query 2D - Immutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.

*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class NumMatrix
{
public:
    vector<vector<int>> v;
    int m, n;
    NumMatrix(vector<vector<int>>& matrix)
    {
        m = matrix.size();
        if(m == 0) {
            return;
        }
        n = matrix[0].size();
        if( n == 0) {
            return;
        }
        v.resize(m);
        for(int i=0; i<m; i++) {
            v[i].resize(n);
        }
        v[0][0] = matrix[0][0];
        for(int i=1; i<m; i++) {
            v[i][0] = v[i-1][0] + matrix[i][0];
        }
        for(int j=1; j<n; j++) {
            v[0][j] = v[0][j-1] + matrix[0][j];
        }
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                v[i][j] = v[i-1][j] + v[i][j-1] - v[i-1][j-1] + matrix[i][j];
            }
        }
        /* for debug
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                cout << v[i][j] << " ";
            }
            cout << endl;
        }
        */
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        if(row1 < 0 || col1 < 0 || m ==0 || n ==0 || row2 >=m || col2 >= n) {
            return 0;
        }
        int left = 0;
        if(col1 > 0) {
            left = v[row2][col1-1];
        }
        int up = 0;
        if(row1 > 0) {
            up = v[row1-1][col2];
        }
        int common = 0;
        if(row1 > 0 && col1 > 0) {
            common = v[row1-1][col1-1];
        }
        return v[row2][col2] - left - up + common;
    }
};
/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

int main()
{
    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };
    NumMatrix *obj = new NumMatrix(matrix);
    cout << obj->sumRegion(2,1,4,3) << endl; // 8
    cout << obj->sumRegion(1,1,2,2) << endl; // 11
    cout << obj->sumRegion(1,2,2,4) << endl; // 12
    system("pause");
    return 0;
}
