/*
373. Find K Pairs with Smallest Sums

You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u,v) which consists of one element from the first array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:

Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The first 3 pairs are returned from the sequence:
             [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

Example 2:

Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [1,1],[1,1]
Explanation: The first 2 pairs are returned from the sequence:
             [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

Example 3:

Input: nums1 = [1,2], nums2 = [3], k = 3
Output: [1,3],[2,3]
Explanation: All possible pairs are returned from the sequence: [1,3],[2,3]

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;

class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k)
    {

        if(nums1.empty() || nums2.empty() || k == 0) {
            return vector<vector<int>> ();
        }
        int n1 = nums1.size(), n2 = nums2.size();
        vector<int> idx(n1, 0);
        int n = min(k, n1 * n2);
        vector<vector<int>> ret(n);
        for(int i=0; i<n; i++) {
            int sum = INT_MAX, curr = 0;
            for(int j = 0; j<n1; j++) {
                if(idx[j] < n2 && sum >= nums1[j] + nums2[idx[j]]) {
                    sum = nums1[j] + nums2[idx[j]];
                    curr = j;
                }
            }
            ret[i] = {nums1[curr], nums2[idx[curr]]};
            idx[curr] ++;
        }
        return ret;
    }
};


int main()
{
    Solution sln;
    vector<int> nums1 = {1,7,11};
    vector<int> nums2 = {2,4,6};
    vector<vector<int>> ret = sln.kSmallestPairs(nums1, nums2, 3);
    for(auto items : ret) {
        for(auto item : items) {
            cout << item << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
