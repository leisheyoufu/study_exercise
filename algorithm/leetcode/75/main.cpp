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