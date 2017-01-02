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

    bool isPalindrome(int x)
    {
        int a[100];
        int k =0, i = 0;
        if (x<0) {
            return false;
        }
        while(x) {
            a[k++] = x%10;
            x/=10;
        }
        while( i< k/2) {
            if(a[i] != a[k-1-i]) {
                return false;
            }
            i++;
        }
        return true;
    }
};
int main()
{
    Solution sln;
    printf("%d\n",sln.isPalindrome(-2147447412));
    getch();
    return 0;
}
