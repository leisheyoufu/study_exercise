/*
228. Summary Ranges
Given a sorted integer array without duplicates, return the summary of its ranges.

Example 1:

Input:  [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.
Example 2:

Input:  [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.

*/

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

class Solution
{
public:
    vector<string> summaryRanges(vector<int>& nums)
    {
        vector<string> ret;
        int n = nums.size();
        if (n == 0) {
            return ret;
        }
        int last = nums[0];
        string s = to_string(last);
        bool first = true;
        for (int i = 1; i < n; i++) {
            if (nums[i] == last + 1) {
                last = nums[i];
                if (first) {
                    first = false;
                    s += "->";
                }
            } else {
                if (!first) {
                    s += to_string(last);
                }
                ret.push_back(s);
                last = nums[i];
                first = true;
                s = to_string(last);
            }
        }
        if (!first) {
            s += to_string(last);
        }
        ret.push_back(s);
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = { 0,1,2,4,5,7 };  // "0->2","4->5","7"
    vector<int> v(a, a + sizeof(a) / sizeof(int));
    vector<string> ret = sln.summaryRanges(v);
    for (auto s : ret) {
        cout << s << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
