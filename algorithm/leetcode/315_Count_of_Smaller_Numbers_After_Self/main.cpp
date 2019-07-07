/*
315. Count of Smaller Numbers After Self
Hard

You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Input: [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.

*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    vector<int> countSmaller(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> ret(n);
        vector<int> sorted;
        for(int i=nums.size()-1; i>=0; i--) {
            int left = 0, right = sorted.size();
            while(left < right) {
                int mid = (left+right)/2;
                if(sorted[mid] >= nums[i]) {
                    right = mid;
                } else {
                    left = mid+1;
                }
            }
            ret[i] = right;
            sorted.insert(sorted.begin() + right, nums[i]);
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<int> nums = {5,2,6,1};
    vector<int> ret = sln.countSmaller(nums);
    for(auto item : ret) {
        cout << item << " ";
    }
    system("pause");
    return 0;
}
