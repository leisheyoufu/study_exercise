/*
3Sum Closest
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

class Solution
{
public:

    /*
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
    */
    int threeSumClosest(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int diff = INT_MAX;
        int ret = 0;
        for(int i=0; i<n-2; i++) {
            if(i>0 && nums[i] == nums[i-1]) {
                continue;
            }
            int j = i+1, k=n-1;
            if (j == k) {
                continue;
            }
            if(nums[i] + nums[j] - target > diff) {
                break;
            }
            while( j < k) {
                int value = nums[i] + nums[j] + nums[k];
                if (value == target) {
                    return value;
                }
                if(abs(value - target) < diff) {
                    diff = abs(value - target);
                    ret = value;
                }
                if ( value < target) {
                    j++;
                } else if(value > target) {
                    k--;
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
