/*
410. Split Array Largest Sum

Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

Note:
If n is the length of array, assume the following constraints are satisfied:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
Examples:

Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool valid(vector<int> &nums, int m, int target)
    {
        int curr = 0, parts = 1;
        for(int num : nums) {
            if(curr + (long long)num > target) {
                curr = num;
                parts ++;
                if (parts > m) {
                    return false;
                }
            } else {
                curr += num;
            }
        }
        return true;
    }
    int splitArray(vector<int>& nums, int m)
    {
        long long high = 0, low = 0;
        for(auto num : nums) {
            high = high + num;
            low = max((long long)num, low);
        }
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(valid(nums, m, mid)) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};
int main()
{
    // [1,2147483646] 1
    Solution sln;
    vector<int> v= {7,2,5,10,8};
    int m = 2;
    cout << sln.splitArray(v, m) << endl; // 18
    v = {1,2147483647};
    cout << sln.splitArray(v, 2) << endl;
    system("pause");
    return 0;
}
