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
    int jump(vector<int>& nums)
    {
        int n = nums.size();
        if(n <2) {
            return 0;
        }
        int cap = nums[0] + 0;
        int curr = nums[0] + 0;
        int count = 1;
        for(int i=1; i<n; i++) {
            if(cap >= n-1) {
                return count;
            }
            curr = max(i+nums[i], curr);
            if(cap == i) {
                cap = curr;
                count++;
            }
        }
        return count;
    }
};

int main()
{
    Solution sln;
    int A[] = {2,3,1,1,4};
    vector<int> v(A, A + sizeof(A)/sizeof(int));
    cout << sln.jump(v) << endl; // 2
    vector<int> b = {1,2};
    cout << sln.jump(b) << endl;  // 1
    vector<int> c = {1,2,3};
    cout << sln.jump(c) << endl;  // 2
    system("pause");
}
