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
    bool isPrime(int num)
    {
        if(num == 1) {
            return false;
        }
        for(int i=2; i*i < num +1; i++) {
            if(num % i == 0) {
                return false;
            }
        }
        return true;
    }
    int countPrimes(int n)
    {
        int count = 0;
        for(int i=2; i < n; i++) {
            count = isPrime(i) ? count+1: count;
        }
        return count;
    }
};
int main()
{
    Solution sln;
    cout << sln.countPrimes(4);
    system("pause");
    return 0;
}
