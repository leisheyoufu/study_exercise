/*
89. Gray Code

The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
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
    int set_bit(int num, int n)
    {
        return num | 1 << (n-1);
    }
    vector<int> grayCode(int n)
    {
        if (n<0) {
            return vector<int>();
        }
        if(n == 0) {
            return vector<int>(1, 0);
        }
        vector<int> ret;
        ret.push_back(0);
        ret.push_back(1);
        int temp = n-1;
        while(temp) {
            int len = ret.size();
            for(int i=len-1; i>=0; i--) {
                ret.push_back(set_bit(ret[i], n-temp+1));
            }
            temp --;
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    vector<int> ret;
    ret=sln.grayCode(3);
    for(int r : ret) {
        cout << r << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
