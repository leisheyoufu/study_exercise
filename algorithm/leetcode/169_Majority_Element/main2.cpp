/*
169. Majority Element
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <sstream>

using namespace std;

class Solution
{
public:
    int majorityElement(vector<int>& nums)
    {
        int n = nums.size();
        if(n == 0) {
            return -1;
        }
        int num, count =0;
        for(int i=0; i<n; i++) {
            if(count == 0) {
                num = nums[i];
                count = 1;
            } else {
                if(nums[i] == num) {
                    count++;
                } else {
                    count --;
                }
            }
        }
        if(count == 0) {
            return -1;
        }
        return num;
    }
};

int main()
{
    Solution sln;
    int a[] = {1,2,2,2,3,3};
    vector<int> v(a, a+sizeof(a) / sizeof(int));
    cout << sln.majorityElement(v) << endl;
    system("pause");
    return 0;
}
