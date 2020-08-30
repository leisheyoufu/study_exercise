/*
307. Range Sum Query - Mutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8


Constraints:

The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
0 <= i <= j <= nums.length - 1
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class NumArray
{
public:
    NumArray(vector<int>& nums)
    {
        n = nums.size();
        if(n == 0) {
            return;
        }
        tree = vector<int>(4*n);
        buildTree(0, 0, n-1, nums);
    }

    void update(int i, int val)
    {
        if(i >=n || i < 0) {
            throw;
        }
        updateTree(0, 0, n-1, i, val);
    }

    int sumRange(int i, int j)
    {
        if(i<0 || j >=n || j<i) {
            throw;
        }
        return sumRangeHelper(0, 0, n-1, i, j);
    }
private:
    vector<int> tree;
    int n;
    void buildTree(int index, int left, int right, vector<int> &nums)
    {
        if(left == right) {
            tree[index] = nums[left];
            return;
        }
        int mid = (left + right) /2;
        int lc = leftChild(index);
        int rc = rightChild(index);
        buildTree(lc, left, mid, nums);
        buildTree(rc, mid+1, right, nums);
        tree[index] = tree[lc] + tree[rc];
    }
    void updateTree(int index, int left, int right, int target, int val)
    {
        if (left == right) {
            tree[index] = val;
            return;
        }
        int mid = (left + right) / 2;
        int lc = leftChild(index);
        int rc = rightChild(index);
        if(target >= mid + 1) {
            updateTree(rc, mid + 1, right, target, val);
        } else {
            updateTree(lc, left, mid, target, val);
        }
        tree[index] = tree[lc] + tree[rc];
    }
    int sumRangeHelper(int index, int left, int right, int queryL, int queryR)
    {
        if(left == queryL && right == queryR) {
            return tree[index];
        }
        int mid = (left + right) / 2;
        int lc = leftChild(index);
        int rc = rightChild(index);
        if(queryL >= mid+1) {
            return sumRangeHelper(rc, mid+1, right, queryL, queryR);
        }
        if(queryR <= mid) {
            return sumRangeHelper(lc, left, mid, queryL, queryR);
        }
        int leftVal = sumRangeHelper(lc, left, mid, queryL, mid);
        int rightVal = sumRangeHelper(rc, mid+1, right, mid+1, queryR);
        return leftVal + rightVal;
    }
    int leftChild(int index)
    {
        return 2*index +1;
    }
    int rightChild(int index)
    {
        return 2*index + 2;
    }
};
int main()
{
    vector<int> nums = {1, 3, 5};
    NumArray numArray = NumArray(nums);
    cout << numArray.sumRange(0,2) << endl; // 9
    numArray.update(1,2);
    cout << numArray.sumRange(0,2) << endl; // 8


    nums = {1,3,4,-90,7,12,5};
    numArray = NumArray(nums);
    cout << numArray.sumRange(0, 2) << endl; // 8
    numArray.update(1,2);
    cout << numArray.sumRange(0, 2) << endl; // 7
    cout << numArray.sumRange(5, 6) << endl; // 17
    numArray.update(4,100);
    cout << numArray.sumRange(0, 6) << endl; // 34
    system("pause");
    return 0;
}
