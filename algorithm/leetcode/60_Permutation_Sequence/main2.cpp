/*

60. Permutation Sequence

The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int get_fac(int n)
    {
        if (n==1) {
            return 0;
        }
        int val = 1;
        for(int i=1; i<n; i++) {
            val *= i;
        }
        return val;
    }
    int get_index_val(int n, int index, vector<bool> &vis)
    {
        for(int i=1; i<=n; i++) {
            if(vis[i-1] == true) {
                continue;
            }
            if (index == 0) {
                vis[i-1] = true;
                return i;
            }
            if(vis[i-1] == false) {
                index--;
            }
        }
        vis[n-1] = true;
        return n;
    }

    string getPermutation(int n, int k)
    {
        vector<bool> vis(n, false);
        string ret(n, 0);
        for(int i=n; i>=1; i--) {
            int f = get_fac(i);
            int index;
            // cl index is started from 0
            if (f == 0) {
                index = 0;
            } else {
                index = (k-1)/f;
            }
            k -= index * f;
            ret[n-i] = get_index_val(n, index, vis) + '0';
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.getPermutation(1,1) << endl; // 1
    cout << sln.getPermutation(9,254) << endl; // "123645978"
    system("pause");
    return 0;
}
