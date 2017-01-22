#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdlib>
using namespace std;
/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

class Solution
{
public:
    int threeSumClosest(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());
        int size = nums.size();
        int min_diff = INT_MAX;
        int ret = 0;

        for(int i=0; i<size-2; i++) {
            int j = i+1, k=size-1;
            if( j==k) {
                continue;
            }
            if(i>0 && nums[i] == nums[i-1]) {
                continue;
            }

            while(j<k) {
                int value = nums[i] + nums[j] +nums[k];
                int diff = target - value;
                if(abs(diff) < abs(min_diff)) {
                    ret = value;
                    min_diff = diff;
                }
                if(value == target) {
                    return ret;
                } else if(value> target) {
                    k--;
                } else if(value <target) {
                    j++;
                }
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {1,1,1,0};
    vector<int> v(a, a + sizeof(a)/sizeof(int));
    cout << sln.threeSumClosest(v, -100) << endl;
    system("pause");
    return 0;
}
