/*

52. N-Queens II

Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.

*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool valid(vector<int> &m, int i, int val)
    {
        for(int j=0; j<i; j++) {
            if(m[j] == val) {
                return false;
            } else if(m[j] == -1) {
                continue;
            }
            if (i-j == abs(val - m[j])) {
                return false;
            }
        }
        return true;
    }

    void dfs(vector<int> &m, int i, int &count)
    {
        int n = m.size();
        if(i==n) {
            count++;
            return;
        }
        for(int j=0; j<n; j++) {
            if( valid(m, i, j)) {
                m[i] = j;
                dfs(m, i+1, count);
                m[i] = -1;
            }
        }
    }
    int totalNQueens(int n)
    {
        int count = 0;
        vector<int> m(n, -1);
        dfs(m, 0, count);
        return count;
    }
};
int main()
{
    Solution sln;
    cout << sln.totalNQueens(7) << endl; // 40
    system("pause");
    return 0;
}
