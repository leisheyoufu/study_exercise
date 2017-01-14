#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    void permute(vector<int> &nums, int start, set<vector<int>> &ret)
    {
        if(start >= nums.size()) {
            ret.insert(nums);
            return;
        }
        for(int i=start; i< nums.size(); i++) {
            if(i != start && nums[i] == nums[start]) {
                continue;
            }
            swap(nums[i], nums[start]);
            permute(nums, start+1, ret);
            swap(nums[i], nums[start]);
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums)
    {
        set<vector<int>> ret;
        permute(nums, 0, ret);
        return vector<vector<int>> (ret.begin(), ret.end());
    }
};
int main()
{
    Solution sln;
    int a[] = {3,3,0,0,2,3,2};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    sln.permuteUnique(v);
    system("pause");
    return 0;
}
