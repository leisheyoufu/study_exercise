/*
80. Remove Duplicates from Sorted Array II

Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    int removeDuplicates(vector<int>& nums)
    {
        int n = nums.size();
        if(n<2) {
            return n;
        }
        int j=1;
        for(int i=2; i<n; i++) {
            if(!(nums[i] == nums[j] && nums[i] == nums[j-1])) {
                nums[++j] = nums[i];
            }
        }
        return j+1;
    }
};

int main()
{
    Solution sln;
    int a[] = {1,1,1,2,2,3};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    cout << sln.removeDuplicates(v) << endl;
    system("pause");
    return 0;
}
