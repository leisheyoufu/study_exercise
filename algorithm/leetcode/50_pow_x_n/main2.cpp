/*

50. Pow(x, n)

Implement pow(x, n).
*/
#include<iostream>
#include<unordered_map>
#include<algorithm>

using namespace std;

class Solution
{
public:
    double pow(double x, unordered_map<int, double> &m, int n)
    {
        if(n==1) {
            return x;
        } else if(n==0) {
            return 1;
        } else if( m.find(n) != m.end()) {
            return m[n];
        }
        double ret;
        if (n & 0x1 == 1) {
            ret = x * pow(x, m, n/2) * pow(x, m, n/2);
        } else {
            ret = pow(x, m, n/2) * pow(x, m, n/2);
        }
        m[n] = ret;
        return ret;
    }

    double myPow(double x, int n)
    {
        unordered_map<int, double> m;
        if(n == 0) {
            return 1;
        } else if(n < 0) {
            if( n<INT_MIN) {
                return 0;
            } else if (n==INT_MIN) {
                return 1.0 / (pow(x, m, INT_MAX)*x);
            }
            return 1/ pow(x, m, n);
        }
        if (n>INT_MAX) {
            return 0;
        }
        return pow(x, m, n);
    }
};
int main()
{
    Solution sln;
    cout << sln.myPow(2.0, 3) << endl;
    cout << sln.myPow(1.0,-2147483648) << endl;
    //printf("%f\n", sln.myPow(1.0,-2147483648));
    system("pause");
    return 0;
}
