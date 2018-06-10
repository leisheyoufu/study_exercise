/*
301. Remove Invalid Parentheses

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Examples:
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]
Credits:
Special thanks to @hpplayer for adding this problem and creating all test cases.


*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class Solution
{
public:

    void DFS(string s, char ch, int last)
    {
        for(int i = 0, cnt = 0; i < s.size(); i++) {
            if(s[i]=='('||s[i]==')') s[i]==ch?cnt++:cnt--;
            if(cnt <= 0) continue;
            for(int j = last; j <= i; j++) {
                if(s[j] == ch && (j ==last || s[j-1]!= ch))
                    DFS(s.substr(0, j)+s.substr(j+1), ch, j);
            }
            return;
        }
        reverse(s.begin(), s.end());
        if(ch == ')') return DFS(s, '(', 0);
        ans.push_back(s);
    }

    vector<string> removeInvalidParentheses(string s)
    {
        DFS(s, ')', 0);
        return ans;
    }
private:
    vector<string> ans;
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
