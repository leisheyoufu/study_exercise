/*
179. Largest Number
Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.
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
    string largestNumber(vector<int>& nums)
    {
        int n = nums.size();
        if(n == 0) {
            return "";
        }
        sort(nums.begin(), nums.end(), comp);
        string ret;
        for(int num : nums) {
            if(ret == "0" && num == 0) {
                break;
            }
            ret += to_string(num);
        }
        return ret;
    }
    static bool comp(int a, int b)
    {
        string s1 = to_string(a);
        string s2 = to_string(b);
        return s1+s2 > s2+s1;
    }
};

int main()
{
    Solution sln;
    // int a[] = {3, 30, 34, 5, 9};
    // int a[] = {0,0,0, 1,1,23,32};
    //int a[] = {8308, 830};
    //int a[] = {2, 2060};
    //int a[] = {121,12};
    int a[] = {824, 8247};
    //int a[] = {824,938,1399,5607,6973,5703,9609,4398,8247};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    cout << sln.largestNumber(v) << endl;
    system("pause");
    return 0;
}
