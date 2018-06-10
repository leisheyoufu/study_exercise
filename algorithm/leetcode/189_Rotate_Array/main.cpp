/*
189. Rotate Array

otate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

[show hint]

Hint:
Could you do it in-place with O(1) extra space?

Related problem: Reverse Words in a String II

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class Solution
{
public:
    void rotate(vector<int>& nums, int k)
    {
        int n = nums.size();
        if (n ==0 ) {
            return;
        }
        k = k % n;
        if(k == 0) {
            return;
        }
        reverse(nums.begin(), nums.begin()+n-k);
        reverse(nums.begin() + n - k, nums.end());
        reverse(nums.begin(), nums.end());
    }
};
int main()
{
    Solution sln;
    int a[] = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> v(a, a + sizeof(a)/sizeof(int));
    sln.rotate(v,3);
    for(int n : v) {
        cout << n << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
