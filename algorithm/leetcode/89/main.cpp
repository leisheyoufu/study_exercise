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
    int setBit(int num, int n)
    {
        return num | 1<<(n-1);
    }

    vector<int> grayCode(int n)
    {
        vector<int> ret;
        if(n<0) {
            return ret;
        }
        ret.push_back(0);
        for(int i=1; i<=n; i++) {
            int size = ret.size();
            for(int k=size-1; k>=0; k--) {
                ret.push_back(setBit(ret[k], i));
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    vector<int> ret;
    ret=sln.grayCode(1);
    for(int i=0; i<ret.size(); i++) {
        printf("%d ", ret[i]);
    }
    system("pause");
    return 0;
}
