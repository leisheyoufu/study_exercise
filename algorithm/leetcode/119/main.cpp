/*
Pascal's Triangle II

Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?

Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?

*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    /*
    int f(int n) {
    	if(n==0) {
    		return 1;
    	}
    	int ret = 1;
    	for(int i=1;i<=n;i++) {
    		ret *=i;
    	}
    	return ret;
    }
    vector<int> getRow(int rowIndex) {
    	vector<int> ret;
    	for(int i=0;i<=rowIndex;i++) {
    		ret.push_back(f(rowIndex)/f(rowIndex-i)/f(i));
    	}
    	return ret;
    }
    */
    vector<int> getRow(int rowIndex)
    {
        if(rowIndex < 0) {
            return vector<int>();
        }
        rowIndex++;
        vector<int> ret(rowIndex, 0);
        for(int i=0; i<rowIndex; i++) {
            ret[rowIndex-1] = 1;
            for(int k=rowIndex-2; k>0; k--) {
                ret[k] = ret[k-1] + ret[k];
            }
            ret[0] = 1;
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<int> v = sln.getRow(14);
    system("pause");
    return 0;
}
