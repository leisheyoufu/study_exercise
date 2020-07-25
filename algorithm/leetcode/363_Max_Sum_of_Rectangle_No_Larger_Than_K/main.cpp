/*
363. Max Sum of Rectangle No Larger Than K
Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

Example:

Input: matrix = [[1,0,1],[0,-2,3]], k = 2
Output: 2
Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
             and 2 is the max number no larger than k (k = 2).
Note:

The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?

*/

#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Solution
{
public:

    int maxSumSubmatrix(vector<vector<int>>& matrix, int k)
    {
        int m = matrix.size();
        if(m == 0) {
            return INT_MIN;
        }
        int n = matrix[0].size();
        if(n == 0) {
            return INT_MIN;
        }
        int ret = INT_MIN;
        for(int j=0; j<n; j++) {
            vector<int> rows(m, 0);
            for(int c = j; c<n; c++) {
                for(int i=0; i<m; i++) {
                    rows[i] += matrix[i][c];
                }
                int sum = 0, maxCurr = INT_MIN;
                set<int> s;
                s.insert(0);
                for(int i=0; i<m; i++) {
                    sum += rows[i];
                    // lower_bount return a value that >= (sum -k), this means set has a value >= (sum - k), then (sum - value) is the number which is very close to k
                    set<int>::iterator it = s.lower_bound(sum - k);
                    if(it != s.end()) {
                        ret = max(ret, sum - *it);
                    }
                    s.insert(sum);
                }
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<vector<int>>matrix = {{1,0,1},{0,-2,3}};
    cout << sln.maxSumSubmatrix(matrix, 2) << endl; // 2
    matrix = {{1,0,1,4},{0,-2,3,-3},{6,3,-1,9}};
    cout << sln.maxSumSubmatrix(matrix, 24) << endl;  // 21
    matrix = {{1,0,1,4},{0,-2,3,-3},{2,3,-5,9}};
    cout << sln.maxSumSubmatrix(matrix, 17) << endl;  // 13
    matrix = {{2,2,-1}};
    cout << sln.maxSumSubmatrix(matrix, 0) << endl; // -1
    matrix = {{7,7,4,-6,-10},{-7,-3,-9,-1,-7},{9,6,-3,-7,7},{-4,1,4,-3,-8},{-7,-4,-4,6,-10},{1,3,-2,3,-10},{8,-2,1,1,-8}};
    cout << sln.maxSumSubmatrix(matrix, 12) << endl; // 12
    matrix = {{7,7,4,-6,-10},{-7,-3,-9,-1,-7},{9,6,-3,-7,7},{-4,1,4,-3,-8},{-7,-4,-4,6,-10},{1,3,-2,3,-10},{8,-2,1,1,-8}};
    cout << sln.maxSumSubmatrix(matrix, 12); // 23
    system("pause");
    return 0;
}
