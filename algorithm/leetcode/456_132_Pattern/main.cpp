/*
456. 132 Pattern

Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.

Follow up: The O(n^2) is trivial, could you come up with the O(n logn) or the O(n) solution?



Example 1:

Input: nums = [1,2,3,4]
Output: false
Explanation: There is no 132 pattern in the sequence.
Example 2:

Input: nums = [3,1,4,2]
Output: true
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:

Input: nums = [-1,3,2,0]
Output: true
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].


Constraints:

n == nums.length
1 <= n <= 104
-109 <= nums[i] <= 109
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<stack>

using namespace std;

class Solution
{
public:
    bool find132pattern(vector<int>& nums)
    {
        stack<int> stk;
        int n = nums.size();
        if(n <3) {
            return false;
        }
        int third = INT_MIN;
        for(int i = n-1; i>=0; i--) {
            if(nums[i] < third) {
                return true;
            }
            while(!stk.empty() && stk.top() < nums[i]) {
                third = stk.top();
                stk.pop();
            }
            stk.push(nums[i]);
        }
        return false;
    }
};
int main()
{
    Solution sln;
    vector<int> nums = {3,1,4,2};
    cout << sln.find132pattern(nums) << endl; // true
    nums = {1,2,3,4};
    cout << sln.find132pattern(nums) << endl; // false
    system("pause");
    return 0;
}
