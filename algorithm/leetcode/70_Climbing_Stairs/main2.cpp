/*
70. Climbing Stairs

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Note: Given n will be a positive integer.

Subscribe to see which companies asked this question.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    /*
    int climbStairs(int n)
    {
    	if(n<=0) {
    		return 0;
    	} else if(n==1) {
    		return 1;
    	} else if(n==2) {
    		return 2;
    	}
    	return climbStairs(n-1) + climbStairs(n-2);
    }
    */
    int climbStairs(int n)
    {
        if(n <=0) {
            return 0;
        }
        vector<int> f(n, 0);
        f[0] = 1;
        f[1] = 2;
        for(int i=2; i<n; i++) {
            f[i] = f[i-1] + f[i-2];
        }
        return f[n-1];
    }
};
int main()
{
    Solution sln;
    cout << sln.climbStairs(9) << endl;  // 55
    cout << sln.climbStairs(60) << endl;  // 764848393
    system("pause");
    return 0;
}
