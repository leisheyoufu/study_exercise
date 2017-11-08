/*
167. Two Sum II - Input array is sorted
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution and you may not use the same element twice.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
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
    int binary_search(vector<int> &numbers, int start, int end, int target)
    {
        while( start <= end) {
            int mid = (start + end) /2;
            if(numbers[mid] == target) {
                return mid;
            } else if (numbers[mid] > target) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return -1;
    }

    vector<int> twoSum(vector<int>& numbers, int target)
    {
        vector<int> ret;
        if(numbers.size() < 2) {
            return ret;
        }
        int n = numbers.size();
        for(int i=0; i < n-1; i++) {
            int num = binary_search(numbers, i+1, n-1, target - numbers[i]);
            if( num != -1) {
                ret.push_back(i+1);
                ret.push_back(num +1);
                return ret;
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    int a[] = { 2,3,4 };
    vector<int> v(a, a + sizeof(a) / sizeof(int));
    sln.twoSum(v, 6);
    system("pause");
    return 0;
}
