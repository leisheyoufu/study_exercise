#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:
    /*
    bool isIn(string s1, int start1, string s2, int start2, string s3, int start3) {
    	if( s3.size() == start3 && s1.size() == start1 && s2.size() == start2) {
    		return true;
    	}
    	if(start1 < s1.size() && s3[start3] == s1[start1]) {
    		if (isIn(s1,start1+1,s2,start2,s3,start3+1)) {
    			return true;
    		}
    	}
    	if(start2< s2.size() && s3[start3] == s2[start2]) {
    		if (isIn(s1,start1,s2,start2+1,s3,start3+1)) {
    			return true;
    		}
    	}
    	return false;
    }

    bool isInterleave(string s1, string s2, string s3) {
        return isIn(s1,0,s2,0,s3,0);
    }*/
    bool dp[101][101];
    bool isInterleave(string s1, string s2, string s3)
    {
        int n1 = s1.length();
        int n2 = s2.length();
        int n3 = s3.length();
        if (n1+n2 != n3) {
            return false;
        }
        memset(dp,0,sizeof(dp));
        dp[0][0] = true;
        for(int i=1; i<=n1; i++) {
            if(s3[i-1] == s1[i-1])
                dp[i][0] = true&& dp[i-1][0];
        }
        for(int j=1; j<=n2; j++) {
            if(s3[j-1] == s2[j-1])
                dp[0][j] = true && dp[0][j-1];
        }

        for(int i=1; i<=n1; i++) {
            for(int j=1; j<=n2; j++) {
                int k = i +j-1;
                if(dp[i-1][j] && s1[i-1] == s3[k]) {
                    dp[i][j] = true;
                }
                if(dp[i][j-1] && s2[j-1] == s3[k]) {
                    dp[i][j] = true;
                }
            }
        }
        for(int i=0; i<=n1; i++) {
            for(int j=0; j<=n2; j++) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
        return dp[n1][n2];
    }
};
int main()
{
    Solution sln;
    string s1 = "db";
    string s2 = "b";
    string s3="cbb";

    printf("%d\n",sln.isInterleave(s1,s2,s3));
    getch();
    return 0;
}
