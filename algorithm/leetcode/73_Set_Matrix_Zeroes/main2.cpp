/*
73. Set Matrix Zeroes

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

click to show follow up.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Solution
{
public:
    void setZeroes(vector<vector<int>>& matrix)
    {
        int m = matrix.size();
        if (m == 0) {
            return;
        }
        int n = matrix[0].size();
        int h = 1, v = 1;
        for(int i=0; i<m; i++) {
            if(matrix[i][0] == 0) {
                h = 0;
            }
        }
        for(int j=0; j<n; j++) {
            if(matrix[0][j] == 0) {
                v = 0;
            }
        }
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                if(matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        for(int i=1; i<m; i++) {
            if (matrix[i][0] == 0) {
                for(int j=1; j<n; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        for(int j=1; j<n; j++) {
            if(matrix[0][j] == 0) {
                for(int i=1; i<m; i++) {
                    matrix[i][j] = 0;
                }
            }
        }
        if(!h) {
            for(int i=0; i<m; i++) {
                matrix[i][0] = 0;
            }
        }
        if(!v) {
            for(int j=0; j<n; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};

int main()
{
    Solution sln;
    vector<vector<int>> v (3, vector<int>(4, 1));
    v[0][0] = 0;
    v[1][2] = 0;
    sln.setZeroes(v);
    system("pause");
    return 0;
}
