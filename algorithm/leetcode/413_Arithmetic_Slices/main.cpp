/*
413. Arithmetic Slices

A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequences:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of the array A is called arithmetic if the sequence:
A[P], A[P + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.


Example:

A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution
{
public:
    // 1 2 3   （1） length = 3
    // 1 2 3 4  （3）  1 + 3 -1, length = 4
    // 1 2 3 4 5 （6）  3 + 4 -1, length = 5
    // 1 2 3 4 5 6 （10） 6 + 5 -1, length = 6
    int numberOfArithmeticSlices(vector<int>& A)
    {
        int n = A.size();
        if (n <3 ) {
            return 0;
        }
        int count = 0, lenth = 0;
        for(int i=2; i<n; i++) {
            if (A[i] - A[i-1] == A[i-1] - A[i-2]) {
                if(lenth == 0) {
                    lenth = 3;
                    count ++;
                } else {
                    count += lenth - 1;
                    lenth++;
                }
            } else {
                lenth = 0;
            }
        }
        return count;
    }
};
int main()
{
    Solution sln;
    vector<int> nums = {1, 2, 3, 4};
    cout << sln.numberOfArithmeticSlices(nums) << endl; // 3
    nums = {7, 7, 7, 7, 8, 9, 10, 12, 14, 16, 7, 8, 6, 5, 4, 3};
    cout << sln.numberOfArithmeticSlices(nums) << endl; // 12
    system("pause");
    return 0;
}
