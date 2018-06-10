/*

4Sum
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<cstdlib>
using namespace std;
/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

*/

class Solution
{
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        unordered_map<int, vector<pair<int, int> > >pairs;
        int size = nums.size();
        for(int i=2; i<size-1; i++) {
            for(int j=i+1; j<size; j++) {
                pairs[nums[i] + nums[j]].push_back(make_pair(i,j));
            }
        }
        for(int i=0; i<size-3; i++) {
            if(i>0 && nums[i] == nums[i-1]) {
                continue;
            }
            for(int j=i+1; j<size-2; j++) {
                if(j>i+1 && nums[j] == nums[j-1]) {
                    continue;
                }
                if(pairs.find(target-nums[i]-nums[j]) != pairs.end()) {
                    vector<pair<int,int>> &v = pairs[target-nums[i]-nums[j]];
                    bool is_first = true;
                    for(int k=0; k<v.size(); k++) {
                        if(v[k].first <= j) {
                            continue;
                        }
                        if( is_first || (ret.back())[2] != nums[v[k].first]) {
                            is_first = false;
                            vector<int> temp;
                            temp.push_back(nums[i]);
                            temp.push_back(nums[j]);
                            temp.push_back( nums[v[k].first]);
                            temp.push_back(nums[v[k].second]);
                            ret.push_back(temp);
                        }
                    }
                }
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {-3,-2,-1,0,0,1,2,3};
    //int a[] = {1,2,3,4,5};
    vector<int> v(a, a + sizeof(a)/sizeof(int));
    sln.fourSum(v,0);
    system("pause");
    return 0;
}
