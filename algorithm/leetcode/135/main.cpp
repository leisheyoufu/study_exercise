/*
Candy

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int candy(vector<int>& ratings)
    {
        int ret = 0;
        int n = ratings.size();
        vector<int> nums(n,1);
        for(int i=1; i<n; i++) {
            if(ratings[i]>ratings[i-1]) {
                nums[i] = nums[i-1] +1;
            }
        }
        for(int i=n-2; i>=0; i--) {
            if(ratings[i]> ratings[i+1]) {
                nums[i] = max(nums[i+1]+1, nums[i]);
            }
        }
        for(int i=0; i<nums.size(); i++) {
            ret+=nums[i];
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {0,1,2,3,0};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    cout << sln.candy(v) << endl;
    system("pause");
    return 0;
}
