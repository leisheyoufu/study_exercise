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
        int m = matrix.size();
        if(m ==0) {
            return vector<int>();
        }
        int n = matrix[0].size();
        vector<int> ret(m*n, 0);
        int c = 0, l = 0, r = n-1, u = 0, d = m-1;
        while( c < m*n) {
            // to right
            int i = l;
            while( i <= r) {
                ret[c++] = matrix[u][i++];
            }
            // to buttom
            i = ++u;
            while( i <= d) {
                ret[c++] = matrix[i++][r];
            }
            // to left
            i = --r;
            if( c == m*n) {
                break;
            }
            while( i >= l) {
                ret[c++] = matrix[d][i--];
            }
            // to up
            i = --d;
            while( i>=u) {
                ret[c++] = matrix[i--][l];
            }
            i = ++l;
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    /*
    int matrix[][3] = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> v(3, vector<int>(3));
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            v[i][j] = matrix[i][j];
        }
    }
    */
    int matrix[][1] = {{1},{2},{3},{4},{5},{6},{7}};
    vector<vector<int>> v(7, vector<int>(1));
    for(int i=0; i<7; i++) {
        for(int j=0; j<1; j++) {
            v[i][j] = matrix[i][j];
        }
    }
    // [[1],[2],[3],[4],[5],[6],[7],[8],[9],[10]]
    sln.spiralOrder(v);
    system("pause");
    return 0;
}
