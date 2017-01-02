#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

class Solution
{
public:
    bool valid(vector<int> cur)
    {
        int size = cur.size();
        int last_item = cur[size-1];
        for(int i=0; i<size-1; i++) {
            if( last_item == cur[i]) {
                return false;
            }
            if(abs(last_item - cur[i]) == abs(size - i -1)) {
                return false;
            }
        }
        return true;
    }
    void backtrack(vector<vector<int>> &ret, vector<int> cur, int row, int n)
    {
        if(n==row) {
            ret.push_back(cur);
        }
        for(int i=0; i<n; i++) {
            cur.push_back(i);
            if(valid(cur)) {
                backtrack(ret, cur, row+1, n);
            }
            cur.pop_back();
        }
    }

    vector<vector<string>> convert(vector<vector<int>> ret, int n)
    {
        vector<vector<string>> str_ret;
        for(int k=0; k<ret.size(); k++) {
            vector<string> cur;
            for(int i=0; i<n; i++) {
                string str(n, '.');
                str[ret[k][i]] = 'Q';
                cur.push_back(str);
            }
            str_ret.push_back(cur);
        }
        return str_ret;
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<int> > ret;
        vector<int> cur;
        backtrack(ret, cur, 0, n);
        return convert(ret, n);
    }
};
int main()
{
    Solution sln;
    vector<vector<string>> temp;
    temp = sln.solveNQueens(4);
    system("pause");
    return 0;
}