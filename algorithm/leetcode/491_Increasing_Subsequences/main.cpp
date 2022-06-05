/*
491. Increasing Subsequences

Given an integer array nums, return all the different possible increasing subsequences of the given array with at least two elements. You may return the answer in any order.

The given array may contain duplicates, and two equal integers should also be considered a special case of increasing sequence.



Example 1:

Input: nums = [4,6,7,7]
Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
Example 2:

Input: nums = [4,4,3,2,1]
Output: [[4,4]]


Constraints:

1 <= nums.length <= 15
-100 <= nums[i] <= 100
Accepted
75,948
Submissions
148,560
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<set>
#include<cmath>

using namespace std;

class Solution
{
public:
    vector<vector<int> > findSubsequences(vector<int>& nums)
    {
        set<vector<int> > ret;
        vector<int> curr;
        dfs(nums, ret, curr, 0);
        return vector<vector<int> > (ret.begin(), ret.end());
    }

    void dfs(vector<int> &nums, set<vector<int> > &ret, vector<int> &curr, int start)
    {
        if (curr.size() > 1) {
            ret.insert(curr);
            if (start == nums.size()) {
                return;
            }
        }
        for(int i=start; i<nums.size(); i++) {
            if (curr.size() == 0) {
                curr.push_back(nums[i]);
            } else if (curr[curr.size()-1] <= nums[i]) {
                curr.push_back(nums[i]);
            }
            dfs(nums, ret, curr, i+1);
            if (curr[curr.size()-1] == nums[i]) {
                curr.pop_back();
            }
        }
    }
};

void print(vector<vector<int> > nums)
{
    for(int i=0; i<nums.size(); i++) {
        for(int j=0; j<nums[i].size(); j++) {
            cout << nums[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    Solution sln;
    vector<int> nums = {4,6,7,7};
    vector<vector<int> > ret = sln.findSubsequences(nums);
    print(ret);
    system("pause");
    return 0;
}
