#include<iostream>
#include<string>
#include<algorithm>
#include<conio.h>

using namespace std;

#define N 1001

char c[1001][1001];
class Solution
{
public:

    string convert(string s, int numRows)
    {
        if (numRows == 1) {
            return s;
        }
        string r;
        int i=0, j=0, k = 0;
        while(k<s.size()) {
            while(i<numRows && k<s.size()) {
                c[i++][j] = s[k++];
            }
            i--;
            while(i>0 && k<s.size()) {
                c[--i][++j] = s[k++];
            }
            i++;
        }
        for(int p=0; p <=i; p++) {
            for(int q=0; q<=j; q++) {
                if(c[p][q] != '\0') {
                    r+=c[p][q];
                }
            }
        }
        return r;
    }
};
int main()
{
    Solution sln;
    cout<< sln.convert("ABCD", 2)<< endl;
    //cout<< sln.convert("PAYPALISHIRING", 3)<< endl;
    //sln.convert("PAYPALISHIRING", 3);
    getch();
    return 0;
}
