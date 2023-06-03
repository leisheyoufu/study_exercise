/*
330. Patching Array

Given a sorted integer array nums and an integer n, add/patch elements to the array such that any number in the range [1, n] inclusive can be formed by the sum of some elements in the array.

Return the minimum number of patches required.

Example 1:

Input: nums = [1,3], n = 6
Output: 1
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
Example 2:

Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
Example 3:

Input: nums = [1,2,2], n = 5
Output: 0


Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 104
nums is sorted in ascending order.
1 <= n <= 231 - 1
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Solution
{
public:
    int minPatches(vector<int>& nums, int n)
    {
        long long miss = 1;
        int i =0, res = 0;
        while(miss <= n) {
            if (i<nums.size() && nums[i] <= miss) {
                miss += nums[i++];
            } else {
                miss += miss;
                res ++;
            }
        }
        return res;
    }
};
int main()
{
    Solution sln;
    vector<int> nums = {1, 3};
    cout << sln.minPatches(nums, 6) << endl;  // 1
    nums = {1,2,2};
    cout << sln.minPatches(nums, 5) << endl;  // 0
    nums = {1,5,10};
    cout << sln.minPatches(nums, 20) << endl; // 2
    nums = {1};
    cout << sln.minPatches(nums, 2) << endl; // 1
    nums = {1,2,31,33};
    cout << sln.minPatches(nums, 2147483647) << endl; // 28
    system("pause");
    return 0;
}
