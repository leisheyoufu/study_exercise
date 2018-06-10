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
    int majorityElement1(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> bak(nums);
        while(bak.size() > 1) {
            vector<int>::iterator first = bak.begin();
            vector<int>::iterator second = first + 1;
            for(; second != bak.end(); second++) {
                if(*first != *second) {
                    break;
                }
            }
            if(second != bak.end()) {
                bak.erase(second);
                bak.erase(first);
            } else {
                break;
            }
        }
        if(!bak.empty()) {
            return bak[0];
        }
        return -1;
    }
    int majorityElement(vector<int>& nums)
    {
        int count = 0;
        int majority;
        for(int i=0; i<nums.size(); i++) {
            if(count == 0) {
                majority = nums[i];
                count ++;
            } else if (majority != nums[i]) {
                count --;
            } else if(majority == nums[i]) {
                count ++;
            }
            if(count > nums.size()/2 +1) {
                return majority;
            }
        }
        return majority;
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
