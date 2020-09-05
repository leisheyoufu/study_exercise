/*
378. Kth Smallest Element in a Sorted Matrix

Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note:
You may assume k is always valid, 1 ≤ k ≤ n2.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_set>
#include<set>

using namespace std;
/*
lower_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于或等于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。



upper_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
*/
class Solution
{
public:
    int kthSmallest(vector<vector<int>>& matrix, int k)
    {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        if (n == 0) {
            return 0;
        }
        int l = matrix[0][0], r = matrix[m-1][n-1];
        int mid = l;
        while(l < r) {
            mid = (l+r)/2;
            int count = 0;
            for(int i=0; i<m; i++) {
                auto &a = matrix[i];
                count+=upper_bound(a.begin(), a.end(), mid) - a.begin();
            }
            if(count <k) {
                l = mid+1;
            } else {
                r = mid;
            }
        }
        return l;
    }
};

int main()
{
    Solution sln;
    vector<vector<int>> matrix = {
        {1,  5,  9},
        {10, 11, 13},
        {12, 13, 15}
    };
    cout << sln.kthSmallest(matrix, 8) << endl; // 13
    system("pause");
    return 0;
}
