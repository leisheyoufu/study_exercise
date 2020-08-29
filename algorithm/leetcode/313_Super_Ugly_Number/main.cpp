/*
313. Super Ugly Number
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

Example:

Input: n = 12, primes = [2,7,13,19]
Output: 32
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
             super ugly numbers given primes = [2,7,13,19] of size 4.
Note:

1 is a super ugly number for any given primes.
The given numbers in primes are in ascending order.
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
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
    int nthSuperUglyNumber(int n, vector<int>& primes)
    {
        int sz = primes.size();
        if(n == 1 || sz == 0) {
            return 1;
        }
        vector<int> nums(n, 1);
        vector<int> indexs(sz, 0);
        for(int i=1; i<n; i++) {
            int curr = INT_MAX, min_j = 0;
            do {
                curr = INT_MAX;
                for(int j = 0; j<sz; j++) {
                    if(nums[indexs[j]] * primes[j] < curr) {
                        min_j = j;
                        curr = nums[indexs[j]] * primes[j];
                        //cout << curr << endl;
                    }
                }
                indexs[min_j]++;
            } while( curr == nums[i-1]);
            nums[i] = curr;
        }
        // for(int num : nums) {
        //     cout << num << " ";
        // }
        return nums[n-1];
    }
};
int main()
{
    Solution sln;
    vector<int> primes = {2,7,13,19};
    cout << sln.nthSuperUglyNumber(12, primes) << endl; //32
    cout << sln.nthSuperUglyNumber(190, primes) << endl; //46592
    system("pause");
    return 0;
}
