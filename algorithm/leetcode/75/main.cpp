/*
Sort Colors

Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

class Solution
{
public:
    /*
    void sortColors(vector<int>& nums) {
        int n = nums.size();
    	vector<int> a(3,0);
    	for(int i=0;i<n;i++) {
    		a[nums[i]]++;
    	}
    	int k=0;
    	for(int i=0;i<3;i++) {
    		for(int j=0;j<a[i];j++) {
    			nums[k++] = i;
    		}
    	}
    }
    */

    void sortColors(vector<int>& nums)
    {
        int n = nums.size();
        int left = 0, right = n-1, i =0;
        while(i<=right) {
            if(nums[i] == 0) {
                swap(nums[i], nums[left]);
                i++;
                left++;
            } else if( nums[i] == 1) {
                i++;
            } else if(nums[i] == 2) {
                swap(nums[i], nums[right]);
                right--;
            }
        }
    }

};
int main()
{
    Solution sln;
    int a[] = {1,2,0};
    vector<int> v(a, a+ sizeof(a)/sizeof(int));
    sln.sortColors(v);
    for(int i =0; i<v.size(); i++) {
        cout << v[i] << " ";
    }
    system("pause");
    return 0;
}
