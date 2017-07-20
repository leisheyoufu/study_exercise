/*
92. Reverse Linked List II

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ? m ? n ? length of list.
*/
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    int numDecodings(string s)
    {
        if(s.empty()) {
            return 0;
        }
        int size = s.size();
        vector<int> d(size+1, 0);
        d[0] = 1;
        for(int i=1; i<=size; i++) {
            d[i] = s[i-1] == '0'?0: d[i-1];
            if(i>1 && (s[i-2] == '1' || s[i-2] == '2' && s[i-1] <='6')) {
                d[i] += d[i-2];
            }
        }
        return d.back();
    }
};

int main()
{
    Solution sln;
    cout << sln.numDecodings("1123");
    system("pause");
    return 0;
}
