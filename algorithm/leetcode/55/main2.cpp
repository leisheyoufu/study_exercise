/*
55. Jump Game

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    bool canJump(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1) {
            return true;
        }
        int cap = nums[0];
        if (cap < 1) {
            return false;
        }
        for(int i=1; i<n-1; i++) {
            cap = max(cap, nums[i] + i);
            if(cap == i) {
                return false;
            }
        }
        return true;
    }

};
int main()
{
    Solution sln;
    int a[] = {2,3,1,1,4};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    cout << sln.canJump(v) << endl;
    system("pause");
    return 0;
}
