/*
204. Count Primes

Description:

Count the number of prime numbers less than a non-negative number, n.
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
    int countPrimes(int n)
    {
        vector<bool> not_prime(n, false);
        int count = 0;
        for(int i=2; i<n; i++) {
            if(!not_prime[i]) {
                count ++;
            }
            for(int j=2; i*j <n; j++) {
                not_prime[i*j] = true;
            }
        }
        return count;
    }
};
int main()
{
    Solution sln;
    cout << sln.countPrimes(5);
    system("pause");
    return 0;
}
