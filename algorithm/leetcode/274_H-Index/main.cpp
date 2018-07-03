/*
274. H-Index

Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

Example:

Input: citations = [3,0,6,1,5]
Output: 3
Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had
             received 3, 0, 6, 1, 5 citations respectively.
             Since the researcher has 3 papers with at least 3 citations each and the remaining
             two with no more than 3 citations each, her h-index is 3.
Note: If there are several possible values for h, the maximum one is taken as the h-index.
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int hIndex(vector<int>& citations)
    {
        int n = citations.size();
        if(n == 0) {
            return 0;
        }
        unordered_map<int, int> m;
        int high = INT32_MIN;
        for(int i=0; i<n; i++) {
            m[citations[i]] ++;
            if(citations[i] > high) {
                high = citations[i];
            }
        }
        int last = 0;
        for(int i=high; i>0; i--) {
            m[i] += last;
            if(m[i] >= i) {
                return i;
            }
            last = m[i];
        }
        return 0;
    }
};
int main()
{
    Solution sln;
    int a[] = {3,0,6,1,5};
    vector<int> v(a, a+ sizeof(a)/sizeof(int));
    cout << sln.hIndex(v) << endl;
    system("pause");
    return 0;
}
