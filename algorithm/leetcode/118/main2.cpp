/*
118. Pascal's Triangle

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
    vector<vector<int> > generate(int numRows)
    {
        vector<vector<int> > ret;
        if (numRows < 1) {
            return ret;
        }
        for(int i=0; i<numRows; i++) {
            vector<int> temp(i+1, 1);
            for(int j=1; j<i; j++) {
                temp[j] = ret[i-1][j-1] + ret[i-1][j];
            }
            ret.push_back(temp);
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
