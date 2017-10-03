/*
216. Combination Sum III
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.


Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]

Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<vector<int>> ret;
        vector<int> cur;
        if (n > 45) {
            return ret;
        }
        trackback(ret, cur, 0, k, n);
        return ret;
    }
    int sum(vector<int> &cur)
    {
        int s = 0;
        for(int i=0; i< cur.size(); i++) {
            s += cur[i];
        }
        return s;
    }

    void trackback(vector<vector<int>> &ret, vector<int> cur, int c, int k, int n) // c start number
    {
        if( cur.size() == k) {
            if (sum(cur) == n) {
                ret.push_back(cur);
            }
            return;
        }
        if(sum(cur) >= n) {
            return;
        }

        for( int i = c+1; i<=9; i++) {
            cur.push_back(i);
            trackback(ret, cur, i, k, n);
            cur.pop_back();
        }
    }

};

int main()
{
    Solution sln;
    sln.combinationSum3(3,9);
    system("pause");
    return 0;
}
