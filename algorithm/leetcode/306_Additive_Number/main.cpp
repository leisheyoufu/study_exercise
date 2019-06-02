/*
306. Additive Number

Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.

Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Example 1:

Input: "112358"
Output: true
Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
             1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
Example 2:

Input: "199100199"
Output: true
Explanation: The additive sequence is: 1, 99, 100, 199.
             1 + 99 = 100, 99 + 100 = 199
Follow up:
How would you handle overflow for very large input integers?
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
    bool isAdditiveNumber(string num)
    {
        vector<long long> nums;
        int n = num.length();
        if(n<3) {
            return false;
        }
        return dfs(nums, num, 0, n-1);
    }

    bool isValid(vector<long long> &nums)
    {
        if (nums.size() < 3)
            return false;
        for (int i = 2; i < nums.size(); i++) {
            long long a = nums[i - 2];
            long long b = nums[i - 1];
            long long c = nums[i];
            if (a + b != c)
                return false;
        }
        return true;
    }

    bool dfs(vector<long long> &nums, string &num, int start, int end)
    {
        if(start > end) {
            return isValid(nums);
        }
        for(int i=start; i<=end; i++) {
            if(num[start] == '0' && i>start) {
                break;
            }
            string sub = num.substr(start, i-start+1);

            if (sub.size() > to_string(LLONG_MAX).size() || sub.size() == to_string(LLONG_MAX).size() && sub.compare(to_string(LLONG_MAX)) > 0) {
                break;
            }
            nums.push_back(stoll(sub));
            if(nums.size() > 2 && !isValid(nums) || !dfs(nums,num, i + 1, end)) {
                nums.pop_back();
            } else {
                return true;
            }
        }
        return false;
    }
};
int main()
{
    Solution sln;
    cout << sln.isAdditiveNumber("112358") << endl;  // true
    cout << sln.isAdditiveNumber("199100199") << endl;  // true
    cout << sln.isAdditiveNumber("101") << endl;  // true
    cout << sln.isAdditiveNumber("1023") << endl;  // false
    system("pause");
    return 0;
}
