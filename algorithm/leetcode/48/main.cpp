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
        for(int i=0; i<n/2; i++) {
            for(int j=i; j<n-1-i; j++) {
                int t = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = t;
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
