/*
66. Plus One

Given a non-negative integer represented as a non-empty array of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.
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
    vector<int> plusOne(vector<int>& digits)
    {
        vector<int> ret = digits;
        int size = ret.size();
        ret[size-1] +=1;
        for(int i=size-1; i>=0; i--) {
            if(ret[i] >9 && i!=0) {
                ret[i-1] +=1;
                ret[i] = 0;
            } else {
                break;
            }
        }
        if(ret[0] > 9) {
            ret.push_back(0);
            ret[0] = 1;
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
