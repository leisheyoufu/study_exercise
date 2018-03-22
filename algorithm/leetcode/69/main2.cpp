/*
69. Sqrt(x)

Implement int sqrt(int x).

Compute and return the square root of x.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int mySqrt(int x)
    {
        if(x <=0) {
            return 0;
        }
        int left = 1;
        int right = x;
        while(left <= right) {
            int mid =  left + (right - left)/2;
            unsigned long long val = (unsigned long long)mid *mid;
            if( val == x) {
                return mid;
            }
            if( val < x && (unsigned long long)(mid+1) * (mid+1) >x) {
                return mid;
            }
            if(val < x) {
                left = mid+1;
            } else {
                right = mid-1;
            }
        }
        return 0;
    }
};

int main()
{
    Solution sln;
    cout << sln.mySqrt(3) << endl;  // 1
    cout << sln.mySqrt(8) << endl;  // 2
    cout << sln.mySqrt(2147395599) << endl;
    system("pause");
    return 0;
}
