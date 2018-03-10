/*
45. Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

class Solution
{
public:
    /*
    int jump(vector<int>& nums)
    {
        int n = nums.size();
        if(n==0 || n== 1) {
            return 0;
        }
        vector<int> f(n, INT_MAX);
        f[0] = 0;
        for(int i=0; i<n-1; i++) {
            int j = min(n, nums[i] + i);
            for(int k=j; k>i; k--) {
                f[k] = min(f[k], f[i] + 1);
            }
        }
        return f[n-1];
    }
    */
    int jump(vector<int> &nums)
    {
        int n = nums.size();
        if(n==0 || n== 1) {
            return 0;
        }
        int curr = 0, ret = 1, cap = nums[0];
        for(int i=1; i<n; i++) {
            if(cap < i) {
                ret ++;
                cap = curr;
            }
            curr = max(curr, i + nums[i]);
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    int A[] = {2,3,1,1,4};
    vector<int> v(A, A + sizeof(A)/sizeof(int));
    cout << sln.jump(v) << endl;
    system("pause");
}
