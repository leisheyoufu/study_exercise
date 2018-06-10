/*
41 First Missing Positive
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;
class Solution
{
public:

    int firstMissingPositive(vector<int>& nums)
    {
        int n = nums.size();
        if(n==0) {
            return 1;
        }
        for(int i=0; i<n; i++) {
            while(nums[i] != i+1) {
                if(nums[i] <=0 || nums[i] >=n || nums[i] == nums[nums[i]-1]) {
                    break;
                }
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        for(int i=0; i<n; i++) {
            if(nums[i] != i + 1) {
                return i+1;
            }
        }
        return n+1;
    }
};
int main()
{
    Solution sln;
    int nums[] = {3,4,-1,1};
    vector<int> v(nums, nums + sizeof(nums)/sizeof(int));
    printf("%d\n",sln.firstMissingPositive(v));
    system("pause");
    return 0;
}
