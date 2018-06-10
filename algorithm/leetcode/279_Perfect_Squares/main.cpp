/*
279. Perfect Squares

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

Credits:
Special thanks to @jianchao.li.fighter for adding this problem and creating all test cases.


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

    int numSquares(int n)
    {
        vector<int> nums(n+1, INT_MAX);
        nums[0] = 0;
        for(int i=1; i*i<=n; i++) {
            nums[i*i] = 1;
        }
        for(int i=0; i<=n; i++) {
            for(int j=0; i+j*j<=n; j++) {
                nums[i+j*j] = min(nums[i]+1, nums[i+j*j]);
            }
        }
        return nums[n];
    }
};
int main()
{
    Solution sln;
    cout << sln.numSquares(8935);
    system("pause");
    return 0;
}
