/*
48. Rotate Image

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    //  [i][j] = [n-1-j][i]
    void rotate(vector<vector<int>>& matrix)
    {
        int n = matrix.size();
        // XY --------->
        for(int i=0; i<n; i++) {
            for(int j=0; j<n-i; j++) {
                swap(matrix[i][j], matrix[n-1-j][n-1-i]);
            }
        }
        // X ---------->
        for(int i=0; i<(n+1)/2; i++) {
            for(int j=0; j<n; j++) {
                swap(matrix[i][j], matrix[n-1-i][j]);
            }
        }
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
