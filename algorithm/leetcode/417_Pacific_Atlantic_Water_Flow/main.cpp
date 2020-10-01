/*
417. Pacific Atlantic Water Flow

Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:

The order of returned grid coordinates does not matter.
Both m and n are less than 150.


Example:

Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<int> >& matrix, vector<vector<int> > &flags, vector<vector<int> > &ret, int i, int j, int pre, int mark)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        if(i<0 || i>=m || j<0 || j>=n || matrix[i][j] < pre || (flags[i][j] & mark) == mark) {
            return;
        }
        flags[i][j] |= mark;
        if(flags[i][j] == 3) {
            ret.push_back({i, j});
        }
        dfs(matrix, flags, ret, i+1, j, matrix[i][j], flags[i][j]);
        dfs(matrix, flags, ret, i-1, j, matrix[i][j], flags[i][j]);
        dfs(matrix, flags, ret, i, j+1, matrix[i][j], flags[i][j]);
        dfs(matrix, flags, ret, i, j-1, matrix[i][j], flags[i][j]);
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int> >& matrix)
    {
        vector<vector<int> > ret;
        if (matrix.empty()) {
            return ret;
        }
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int> > flags (m, vector<int>(n, 0));
        for(int i=0; i<m; i++) {
            dfs(matrix, flags, ret, i, 0, INT_MIN, 1);
            dfs(matrix, flags, ret, i, n-1, INT_MIN, 2);
        }
        for(int j=0; j<n; j++) {
            dfs(matrix, flags, ret, 0, j, INT_MIN, 1);
            dfs(matrix, flags, ret, m-1, j, INT_MIN, 2);
        }
        return ret;
    }

};
int main()
{
    /*
    ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
    */
    Solution sln;
    vector<vector<int> > matrix = {{1,2,2,3,5}, {3,2,3,4,4}, {2,4,5,3,1}, {6, 7,1,4,5}, {5,1,1,2,4}};
    vector<vector<int> > ret = sln.pacificAtlantic(matrix);
    for(int i=0; i<ret.size(); i++ ) {
        cout << "[" << ret[i][0] << "," << ret[i][1] << "] ";
    }
    system("pause");
    return 0;
}
