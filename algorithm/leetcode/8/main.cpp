/* String to Integer (atoi)
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button  to reset your code definition.
*/
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

    int myAtoi(string str)
    {
        long long r = 0;
        int i=0;
        bool nagative = false;
        if(str[i] == '-') {
            nagative = true;
            i++;
        } else if(str[i] == '+') {
            i++;
        }
        for(; i<str.size(); i++) {

            r*=10;
            if(str[i] - '0' < 0 || str[i] - '0' > 9) {
                return 0;
            }
            r+= str[i] - '0';
            if(r > MAX) {
                return 0;
            }
        }
        if(nagative) {
            r= -r;
        }
        return r;
    }
};
int main()
{
    Solution sln;
    printf("%d\n",sln.myAtoi("010"));
    getch();
    return 0;
}
