/*
73. Set Matrix Zeroes

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

click to show follow up.
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
    void set_row(int row, vector<vector<int>>& matrix)
    {
        int n = matrix[0].size();
        for(int j=0; j<n; j++) {
            matrix[row][j] = 0;
        }
    }

    void set_column(int column, vector<vector<int>>& matrix)
    {
        int m = matrix.size();
        for(int i=0; i<m; i++) {
            matrix[i][column] = 0;
        }
    }

    void setZeroes(vector<vector<int>>& matrix)
    {
        int m = matrix.size();
        if (m==0) {
            return;
        }
        int n = matrix[0].size();
        vector<int> c_mark(n, 0);
        vector<int> r_mark(m, 0);
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(matrix[i][j] == 0 ) {
                    c_mark[j] = 1;
                    r_mark[i] = 1;
                }
            }
        }
        for(int j=0; j<n; j++) {
            if(c_mark[j] == 1) {
                set_column(j, matrix);
            }
        }
        for(int i=0; i<m; i++) {
            if(r_mark[i] == 1) {
                set_row(i, matrix);
            }
        }
    }
};

int main()
{
    Solution sln;
    vector<vector<int>> v (2, vector<int>(3, 1));
    v[0][1] = 0;
    sln.setZeroes(v);
    system("pause");
    return 0;
}
