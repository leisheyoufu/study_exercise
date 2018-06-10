/*

164. Maximum Gap
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:

    int maximumGap(vector<int>& nums)
    {
        if(nums.size() < 2) {
            return 0;
        }
        int min_val = INT_MAX;
        int max_val = INT_MIN;
        for(int i=0; i<nums.size(); i++) {
            min_val = min(min_val, nums[i]);
            max_val = max(max_val, nums[i]);
        }
        double len = double(max_val - min_val)*1.0 / (nums.size() -1);
        if (len == 0) {
            return 0;
        }
        int count = floor(double(max_val - min_val) / len + 1);
        vector<int> max_array(count, INT_MIN);
        vector<int> min_array(count, INT_MAX);
        for(int i=0; i <nums.size(); i++) {
            int id = floor((nums[i] - min_val) / len);
            max_array[id] = max(max_array[id], nums[i]);
            min_array[id] = min(min_array[id], nums[i]);
        }
        int premax = max_array[0];
        int max_diff = 0;
        for(int i=1; i<count; i++) {
            if (min_array[i] != INT_MAX) {
                max_diff = max(max_diff, min_array[i] - premax);
                premax = max_array[i];
            }
        }
        return max_diff;
    }
};

int main()
{
    Solution sln;
    int a[] = {15252,16764,27963,7817,26155,20757,3478,22602,20404,6739,16790,10588,16521,6644,20880,15632,27078,25463,
               20124,15728,30042,16604,17223,4388,23646,32683,23688,12439,30630,3895,7926,22101,32406,21540,31799,3768,26679,21799,23740
              };
    vector<int> v(a, a + sizeof(a) / sizeof(int));
    cout << sln.maximumGap(v);
    system("pause");
    return 0;
}
