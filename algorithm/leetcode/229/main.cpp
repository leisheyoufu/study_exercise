/*
229. Majority Element II
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    vector<int> majorityElement(vector<int>& nums)
    {
        int n = nums.size();
        int num1, num2, count1 = 0, count2 = 0;
        for(int i=0; i<n; i++) {
            if(nums[i] == num1) {
                count1++;
                continue;
            }
            if(nums[i] == num2) {
                count2++;
                continue;
            }
            if(count1 == 0) {
                num1 = nums[i];
                count1++;
                continue;
            }
            if(count2 == 0) {
                num2= nums[i];
                count2++;
                continue;
            }
            // != num1 && != num2
            count1--;
            count2--;
        }
        count1 = 0;
        count2 = 0;
        for(auto num : nums) {
            if(num == num1) {
                count1++;
            } else if(num == num2) {
                count2++;
            }
        }
        vector<int> ret;
        if(count1 != 0 && n/count1 < 3) {
            ret.push_back(num1);
        }
        if(count2 != 0 && n/count2 < 3) {
            ret.push_back(num2);
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
