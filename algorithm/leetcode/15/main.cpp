/*
3Sum

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdlib>
using namespace std;
/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        int size = nums.size();
        for(int i=0; i<size-2; i++) {
            int j = i+1, k=size-1;
            if( j==k) {
                continue;
            }
            if(nums[i] + nums[j] >0) {
                break;
            }
            if(nums[k] < 0) {
                break;
            }
            if(i>0 && nums[i] == nums[i-1]) {
                continue;
            }

            while(j<k) {
                if(nums[i] + nums[j] +nums[k] == 0) {
                    vector<int> result;
                    result.push_back(nums[i]);
                    result.push_back(nums[j]);
                    result.push_back(nums[k]);
                    ret.push_back(result);
                    while(j<k && nums[j]== nums[j+1]) j++;
                    while(j<k && nums[k] == nums[k-1]) k--;
                    j++;
                    k--;
                } else if(nums[i] + nums[j] + nums[k] > 0) {
                    k--;
                } else if(nums[i] + nums[j] + nums[k] <0) {
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
    int a[] = {0};
    vector<int> v(a, a + sizeof(a)/sizeof(int));
    sln.threeSum(v);
    system("pause");
    return 0;
}
