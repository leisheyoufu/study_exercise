/*

162. Find Peak Element
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ¡Ù num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -¡Þ.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

click to show spoilers.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int findPeakElement(vector<int>& nums)
    {
        if (nums.empty()) {
            return -1;
        }
        if (nums.size() == 1) {
            return 0;
        } else if(nums.size() > 1 && nums[0] > nums[1]) {
            return 0;
        }
        for(int i=1; i<nums.size()-1; i++) {
            if(nums[i] > nums[i-1] && nums[i] > nums[i+1]) {
                return i;
            }
        }
        int i = nums.size()-1;
        if (nums[i] > nums[i-1]) {
            return i;
        }
        return -1;
    }
};

int main()
{
    Solution sln;
    int a[] = {1, 2, 3, 1};
    vector<int> v(a, a + sizeof(a) / sizeof(int));
    cout << sln.findPeakElement(v);
    system("pause");
    return 0;
}
