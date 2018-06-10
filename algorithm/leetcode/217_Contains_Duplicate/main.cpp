/*
217. Contains Duplicate
Given an array of integers, find if the array contains any duplicates.

Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

Example 1:

Input: [1,2,3,1]
Output: true
Example 2:

Input: [1,2,3,4]
Output: false
Example 3:

Input: [1,1,1,3,3,4,3,2,4,2]
Output: true
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        unordered_set<int> s;
        for(auto num : nums) {
            if(s.find(num) == s.end()) {
                s.insert(num);
            } else {
                return true;
            }
        }
        return false;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
