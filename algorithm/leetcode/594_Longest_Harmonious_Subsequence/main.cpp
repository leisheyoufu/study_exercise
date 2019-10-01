/*

594. Longest Harmonious Subsequence

We define a harmounious array as an array where the difference between its maximum value and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:

Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].


Note: The length of the input array will not exceed 20,000.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>
#include<unordered_map>

using namespace std;


class Solution
{
public:
    int findLHS(vector<int>& nums)
    {
        int n = nums.size();
        if(n==0) {
            return 0;
        }
        unordered_map<int, int> m;
        for(auto num : nums) {
            m[num] ++;
        }
        int ret = 0, curr = 0;
        for(unordered_map<int,int>::iterator iter = m.begin(); iter!=m.end(); iter++) {
            if(m.find(iter->first -1) != m.end()) {
                curr = m[iter->first] + m[iter->first-1];
                ret = max(curr, ret);
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    vector<int> nums = {1,3,2,2,5,2,3,7,6,6,6,8,8};
    cout << sln.findLHS(nums) << endl;
    system("pause");
    return 0;
}
