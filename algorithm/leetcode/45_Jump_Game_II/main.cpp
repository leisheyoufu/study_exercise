/*
Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/

class Solution
{
public:
    int jump(vector<int>& nums)
    {
        int n = nums.size();
        if(n<=1) {
            return 0;
        }
        int curmax =0, curstep = 0, ret = 0;
        for(int i=0; i<n; i++) {
            if(curstep<i) {
                ret++;
                curstep = curmax;
            }
            curmax=max(curmax, nums[i] +i);
        }
        return ret;
    }
};
