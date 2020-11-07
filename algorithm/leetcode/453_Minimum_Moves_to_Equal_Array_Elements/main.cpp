/*
453. Minimum Moves to Equal Array Elements

Given a non-empty integer array of size n, find the minimum number of moves required to make all array elements equal, where a move is incrementing n - 1 elements by 1.

Example:

Input:
[1,2,3]

Output:
3

Explanation:
Only three moves are needed (remember each move increments two elements):

[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
[1,2,3,5] => [2,3,4,5] => [3,4,5,5] =? [4,5,6,5] => [5,6,6,6] => [6,7,7,6] => [7,8,7,7] => [8,8,8,8]
[1,1,3] => [2,2,3] => [3,3,3]
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Solution
{
public:
    int minMoves(vector<int>& nums)
    {
        int minimal = INT_MAX;
        for(auto num: nums) {
            minimal = min(minimal, num);
        }
        int ret = 0;
        for(auto num: nums) {
            ret += num - minimal;
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<int> nums = {1,2,3};
    cout << sln.minMoves(nums) << endl; // 3
    system("pause");
    return 0;
}
