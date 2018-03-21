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
    /*
    a better way:
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
    */
    vector<int> plusOne(vector<int>& digits)
    {
        int n = digits.size();
        if(n == 0 ) {
            return vector<int>();
        }
        vector<int> ret(n,0);
        int c = 1;
        for(int i= n-1; i>=0; i--) {
            ret[n-i-1] = c + digits[i];
            if(ret[n-i-1] > 9) {
                ret[n-i-1] = ret[n-i-1] % 10;
                c = 1;
            } else {
                break;
            }
        }
        if(c != 0) {
            ret.push_back(1);
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = { 9,9,9};
    vector<int> v(a, a +sizeof(a)/sizeof(int));
    sln.plusOne(v);
    system("pause");
    return 0;
}
