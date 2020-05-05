/*
384. Shuffle an Array

Shuffle a set of numbers without duplicates.

Example:

// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
solution.shuffle();

// Resets the array back to its original configuration [1,2,3].
solution.reset();

// Returns the random shuffling of array [1,2,3].
solution.shuffle();
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
    Solution(vector<int>& nums)
    {
        orig = nums;
        ans = nums;
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset()
    {
        ans = orig;
        return ans;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle()
    {
        for(int i = ans.size()-1; i>=0; i--) {
            swap(ans[i], ans[rand()%(i+1)]);
        }
        return ans;
    }
private:
    vector<int> orig;
    vector<int> ans;
};

void print(vector<int> nums)
{
    for(int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> nums = {1,2,3};
    Solution sln(nums);
    print(sln.shuffle());
    print(sln.reset());
    print(sln.shuffle());
    system("pause");
    return 0;
}
