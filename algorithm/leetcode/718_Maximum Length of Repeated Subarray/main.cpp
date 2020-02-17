/*
718. Maximum Length of Repeated Subarray

Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:

Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation: 
The repeated subarray with maximum length is [3, 2, 1].
 

Note:

1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class Solution
{
public:
    int findLength(vector<int>& A, vector<int>& B) 
    {
        int n1 = A.size();
        int n2 = B.size();
        if(n1 == 0 || n2 == 0) {
            return 0;
        }
        int ret = 0;
        vector<vector<int>> dp(n1, vector<int>(n2, 0));
        for(int i=0; i<n1; i++) {
            dp[i][0] = A[i] == B[0] ? 1 : 0;
            ret = max(ret, dp[i][0]);
        }
        for(int j=0; j<n2; j++) {
            dp[0][j] = A[0] == B[j] ? 1 : 0;
            ret = max(ret, dp[0][j]);
        }
        
        for(int i=1; i<n1; i++) {
            for(int j=1; j<n2; j++) {
                if(A[i] == B[j]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    ret = max(ret, dp[i][j]);
                }
            }
        }
        return ret;        
    }
};
int main()
{
    Solution sln;
    vector<int> A = {1,2,3,2,1};
    vector<int> B = {3,2,1,4,7};
    cout << sln.findLength(A, B) << endl; // 3
    system("pause");
    return 0;
}
