#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

using namespace std;

class Solution
{
public:
    int minCut(string s)
    {
        int size = s.size();
        if(size==0) {
            return 0;
        }
        vector<vector<bool>> is_palind(size,vector<bool>(size, false));
        vector<int> min_parts(size+1,-1);
        for(int i=0; i<size; i++) {
            is_palind[i][i] = true;
        }
        for(int i=size-1; i>=0; i--) {
            min_parts[i] = min_parts[i+1] +1;
            for(int j=i+1; j<size; j++) {
                if(s[i] == s[j]) {
                    if(j==i+1 || is_palind[i+1][j-1]) {
                        is_palind[i][j] = true;
                        if(j==size-1) {
                            min_parts[i]=0;
                        } else if(min_parts[i] > min_parts[j+1] +1) {
                            min_parts[i] = min_parts[j+1]+1;
                        }
                    }
                }
            }
        }
        return min_parts[0];
    }
};

int main()
{
    Solution sln;
    string s="";
    cout << sln.minCut(s) << endl;
    system("pause");
    return 0;
}