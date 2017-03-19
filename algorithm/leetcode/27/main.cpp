/* 27. Remove Element
Given an array and a value, remove all instances of that value in place and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

Example:
Given input array nums = [3,2,2,3], val = 3

Your function should return length = 2, with the first two elements of nums being 2.
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
    int removeElement(vector<int>& nums, int val)
    {
        int n = nums.size();
        int count = 0;
        for(int i=0; i<n; i++) {
            if(nums[i] == val) {
                count ++;
            } else {
                nums[i-count] = nums[i];
            }
        }
        return n-count;
    }
};
int main()
{
    Solution sln;
    int nums[] = {1,2,2,2,3,3,4};
    vector<int> v(nums, nums + sizeof(nums)/sizeof(int));
    cout << sln.removeElement(v, 2) << endl;
    system("pause");
    return 0;
}
