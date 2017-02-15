/*
Pascal's Triangle

Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret;
        if(numRows <1 ) {
            return ret;
        }
        vector<int> one(1,1);
        ret.push_back(one);
        for(int i=2; i<=numRows; i++) {
            vector<int> a (i, 1);
            for(int j=2; j<i; j++) {
                a[j-1] = ret[i-2][j-2] + ret[i-2][j-1];
            }
            ret.push_back(a);
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<vector<int>> r = sln.generate(5);
    system("pause");
    return 0;
}
