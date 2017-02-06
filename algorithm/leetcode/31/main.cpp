/* Next Permutation
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

    void nextPermutation(vector<int>& nums)
    {
        int n = nums.size();
        int i= n-1;
        for(; i>0; i--) {
            if(nums[i] > nums[i-1]) {
                break;
            }
        }
        if (i==0) {
            reverse(nums.begin(),nums.end());
            return;
        }
        int k = i - 1;
        for(i=n-1; i>k; i--) {
            if(nums[i] > nums[k]) {
                swap(nums[i],nums[k]);
                break;
            }
        }
        reverse(nums.begin()+k+1,nums.end());
    }
};
int main()
{
    int arr[3] = { 1,3,2};
    vector<int> v(arr, arr + 3);

    Solution *s = new Solution();
    s->nextPermutation(v);

    for (int i = 0; i < 3; i++)
        cout << v[i] << "\t";
    cout << endl;
    system("pause");

    return 0;
}
