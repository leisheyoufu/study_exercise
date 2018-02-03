/* 26. Remove Duplicates from Sorted Array
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    /*
        int removeDuplicates(vector<int>& nums)
    {
        int n = nums.size();
        if(n==0) {
            return 0;
        }
        int i = 1, j=1;
        while(i<n) {
            if( nums[i] != nums[i-1]) {
                nums[j++] = nums[i];
            }
            i++;
        }
        return j;
    }
    */
    int removeDuplicates(vector<int>& nums)
    {
        if(nums.empty()) {
            return 0;
        }
        int n = nums.size();
        int i = 1, j =1;
        while(i<n) {
            if(nums[i] == nums[i-1]) {
                ++i;
                continue;
            }
            nums[j++] = nums[i++];
        }
        return j;
    }
};
int main()
{
    Solution sln;
    int nums[] = {1,2,2,2,3,3,4};
    vector<int> v(nums, nums + sizeof(nums)/sizeof(int));
    cout << sln.removeDuplicates(v) << endl;
    system("pause");
    return 0;
}
