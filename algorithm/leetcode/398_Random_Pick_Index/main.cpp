/*
398. Random Pick Index

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<sys/time.h>

using namespace std;

class Solution
{
public:
    /*
        Solution(vector<int>& nums)
        {
            for(int i=0; i<nums.size(); i++) {
                int num = nums[i];
                if(m.find(num) == m.end()) {
                    m[num] = {i};
                } else {
                    m[num].push_back(i);
                }
            }
        }

        int pick(int target)
        {
            int n = m[target].size();
            return m[target][rand()%n];
        }
    */
    Solution(vector<int>& nums) : nums(nums)
    {
        srand(time(0) );
    }
    int pick(int target)
    {
        int count = 0;
        int ret = -1;
        for(int i=0; i<nums.size(); i++) {
            if(target == nums[i]) {
                count ++;
                if (rand()%count == count -1) {
                    ret = i;
                }
            }
        }
        return ret;
    }
private:
    vector<int> nums;
};


int main()
{
    vector<int> nums = {1,2,3,3,3};
    Solution sln(nums);
    cout << sln.pick(3) << endl;
    system("pause");
    return 0;
}
