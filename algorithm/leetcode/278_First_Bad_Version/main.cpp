/*
278. First Bad Version

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

Example:

Given n = 5, and version = 4 is the first bad version.

call isBadVersion(3) -> false
call isBadVersion(5) -> true
call isBadVersion(4) -> true

Then 4 is the first bad version.
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
    // fake
    bool isBadVersion(int n)
    {
        if (n ==3) {
            return true;
        }
        return false;
    }
    int firstBadVersion(int n)
    {
        if(n<=0) {
            return -1;
        }
        int left = 1, right = n;
        while(left <= right) {
            int mid = left + (right - left)/2;
            if(isBadVersion(mid)) {
                right = mid -1;
            } else {
                left = mid + 1;
            }
        }
        return left;
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
