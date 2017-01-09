class Solution
{
public:
    int jump(vector<int>& nums)
    {
        int n = nums.size();
        if(n<=1) {
            return 0;
        }
        int curmax =0, curstep = 0, ret = 0;
        for(int i=0; i<n; i++) {
            if(curstep<i) {
                ret++;
                curstep = curmax;
            }
            curmax=max(curmax, nums[i] +i);
        }
        return ret;
    }
};