#include<iostream>
#include<string>
#include<algorithm>
#include<conio.h>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

    int reverse(int x)
    {
        long long r=0;
        while(x) {
            r *=10;
            int b = x % 10;
            x/=10;
            r+=b;
            if (r > MAX || r < MIN) {
                return 0;
            }
        }
        return r;
    }
};
int main()
{
    Solution sln;
    cout<< sln.reverse(1534236469)<< endl;
    getch();
    return 0;
}
