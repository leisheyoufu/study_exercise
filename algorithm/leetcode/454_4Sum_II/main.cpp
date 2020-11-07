/*
454. 4Sum II

Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500. All integers are in the range of -228 to 228 - 1 and the result is guaranteed to be at most 231 - 1.

Example:

Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Solution
{
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
    {
        int n = A.size();
        if(n == 0) {
            return 0;
        }
        unordered_map<int, int> m;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int val = C[i] + D[j];
                if(m.count(val) == 0) {
                    m[val] = 1;
                } else {
                    m[val]++;
                }
            }
        }
        int ret = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                int val = A[i] + B[j];
                if (m.count(-val) !=0) {
                    ret += m[-val];
                }

            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<int> A = {-1,-1};
    vector<int> B = {-1, 1};
    vector<int> C = {-1, 1};
    vector<int> D = {1,-1};
    cout << sln.fourSumCount(A, B, C, D) << endl; // 6
    system("pause");
    return 0;
}
