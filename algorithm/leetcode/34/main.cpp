#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
		vector<int> ret;
		int left = 0, right = n-1;
		while(left <=right) {
			int mid = (left + right)/2;
			if(nums[mid] == target) {
				int l_ret = mid;
				while(l_ret >=0 && nums[l_ret] == target) {
					l_ret --;
				}
				int r_ret = mid;
				while(r_ret <n && nums[r_ret] == target) {
					r_ret ++;
				}
				ret.push_back(l_ret+1);
				ret.push_back(r_ret-1);
				break;
			}
			if(target > nums[mid]) {
				left = mid+1;
			} else {
				right = mid-1;
			}
		}
		if(ret.empty()) {
			ret.push_back(-1);
			ret.push_back(-1);
		}
		return ret;
    }
};
int main()
{
    Solution sln;
	int a[] = {5, 7, 7, 8, 8, 10};
	vector<int> nums(a, a+sizeof(a)/sizeof(int));
    sln.searchRange(nums,8);
    system("pause");
    return 0;
}
