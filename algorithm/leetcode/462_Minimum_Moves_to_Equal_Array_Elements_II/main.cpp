/*
462. Minimum Moves to Equal Array Elements II

Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.

In one move, you can increment or decrement an element of the array by 1.

Test cases are designed so that the answer will fit in a 32-bit integer.



Example 1:

Input: nums = [1,2,3]
Output: 2
Explanation:
Only two moves are needed (remember each move increments or decrements one element):
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
Example 2:

Input: nums = [1,10,2,9]
Output: 16


Constraints:

n == nums.length
1 <= nums.length <= 105
-109 <= nums[i] <= 109
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<stack>
#include<cmath>

using namespace std;

class Solution
{
public:
    int minMoves2(vector<int>& nums)
    {
        int n = nums.size();
        if (n <=1) {
            return 0;
        }
        int ret = 0;
        sort(nums.begin(), nums.end());
        int mid = nums[n/2];
        for(int num: nums) {
            ret += abs(num-mid);
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    vector<int> nums = {1,2,3};
    cout << sln.minMoves2(nums) << endl; // 2
    nums = {1,10,2,9};
    cout << sln.minMoves2(nums) << endl; // 16
    system("pause");
    return 0;
}
