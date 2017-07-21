/*
96. Unique Binary Search Trees

Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<cmath>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    int numTrees(int n)
    {
        vector<int> ret(n+1, 0);
        ret[0] = 1;
        ret[1] = 1;
        for(int i=2; i<=n; i++) {
            for(int j=0; j<i; j++) {
                ret[i] = ret[i] + ret[i-j-1]*ret[j];
            }
        }
        return ret[n];
    }
};
int main()
{
    Solution sln;
    cout << sln.numTrees(3);
    system("pause");
    return 0;
}
