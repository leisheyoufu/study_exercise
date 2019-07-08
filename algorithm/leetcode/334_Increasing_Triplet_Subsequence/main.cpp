/*
334. Increasing Triplet Subsequence
Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

Formally the function should:

    Return true if there exists i, j, k
    such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.

Note: Your algorithm should run in O(n) time complexity and O(1) space complexity.

Example 1:

Input: [1,2,3,4,5]
Output: true

Example 2:

Input: [5,4,3,2,1]
Output: false
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_set>
#include<set>

using namespace std;

class Solution
{
public:
    bool increasingTriplet(vector<int>& nums)
    {
        int n =nums.size();
        if(n<3) {
            return false;
        }
        int a = nums[0], b = nums[1];
        for(int i=2; i<n; i++) {
            //cout << a << " " << b << endl;
            if(a >= b && nums[i] > b) {
                a = b;
                b = nums[i];
                continue;
            } else if(a >= b && nums[i] < b) {
                a = b;
                b = nums[i];
                continue;
            }
            if(nums[i] > b) {
                return true;
            } else if(nums[i] < b && nums[i] > a) {
                b = nums[i];
            } else if(nums[i] < a) {
                a = nums[i];
            }
        }
        return false;
    }
};

int main()
{
    Solution sln;
    //vector<int> nums = {1,2,3,4,5};
    //vector<int> nums = {5,4,3,2,1};
    //vector<int> nums = {1,3,2,4,5};
    //vector<int> nums = {2,1,5,0,3};
    //vector<int> nums = {2,1,5,0,4,6};  // 1
    vector<int> nums = {1,1,-2,6};  // false
    cout << sln.increasingTriplet(nums) << endl;
    system("pause");
    return 0;
}
