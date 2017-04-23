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
        if( n == 0) {
    		return 0;
    	}
    	if( n ==1) {
    		return 1;
    	}
    	if (n ==2) {
    		return 2;
    	}
    	return climbStairs(n-2) + climbStairs(n-1);
    }
    */
    int climbStairs(int n)
    {
        if (n==0 || n == 1 || n==2) {
            return n;
        }
        vector<int> v(n);
        v[0] = 1;
        v[1] = 2;
        for(int i=2; i<n; i++) {
            v[i] = v[i-1]+ v[i-2];
        }
        return v[n-1];
    }

};
int main()
{
    Solution sln;
    cout << sln.climbStairs(90) << endl;
    system("pause");
    return 0;
}
