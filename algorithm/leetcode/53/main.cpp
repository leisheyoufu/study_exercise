#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int>& nums)
    {
        int part_max_sum = nums[0];
        int max_sum = part_max_sum;
        for(int i=1; i<nums.size(); i++) {
            if(part_max_sum < 0 && nums[i] > part_max_sum) {
                part_max_sum = nums[i];
            } else if(part_max_sum + nums[i] >0) {
                part_max_sum += nums[i];
            } else {
                part_max_sum = INT_MIN;
            }
            if(part_max_sum > max_sum) {
                max_sum = part_max_sum;
            }
        }
        return max_sum;
    }
};
int main()
{
    Solution sln;
    int a[] = {-2,1,-3,4,-1,2,1,-5,4};
    int size = sizeof(a)/sizeof(int);
    vector<int> v(a,a+size);
    printf("%d\n", sln.maxSubArray(v));
    system("pause");
    return 0;
}