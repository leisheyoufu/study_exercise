#include<iostream>
#include<string>
#include<algorithm>
#include<conio.h>

using namespace std;

#define N 1001

struct item {
	int start;
	int end;
	int val;
};
struct item dp[N][N];
class Solution {  
public:  
    string longestPalindrome(string s) {  
        const int n=s.size();
        memset(dp,0, sizeof(dp));
		for(int i=0; i<n; i++) {
			dp[i][i].val = 1;
			dp[i][i].start = i;
			dp[i][i].end = i;
		}
        for(int i=1;i<n;i++) {
			for(int j=0; j+i<n;j++) {
				int temp, start, end;
				
				if(s[j] == s[j+i] && (dp[j+1][j+i-1].val == 0 && i==1 || dp[j+1][j+i-1].val == i-1)) {
					start = j, end = j+i;
					temp = dp[j+1][j+i-1].val +2;
				}
				else {
					if(dp[j][j+i-1].val >= dp[j+1][j+i].val) {
						temp = dp[j][j+i-1].val;
						start = dp[j][j+i-1].start;
						end = dp[j][j+i-1].end;
					} else {
						temp = dp[j+1][j+i].val;
						start = dp[j+1][j+i].start;
						end =  dp[j+1][j+i].end;
					}
				}
				dp[j][j+i].val = temp;
				dp[j][j+i].start = start;
				dp[j][j+i].end = end;

			}
		}
		printf("%d\n", dp[0][n-1].val);
		return s.substr(dp[0][n-1].start,dp[0][n-1].end - dp[0][n-1].start + 1);  
    }  
};  
int main()
{
    string input = "cbbd";  
    Solution sln;
	cout<< sln.longestPalindrome(input) << endl;
  
    getch();
    return 0;
}
