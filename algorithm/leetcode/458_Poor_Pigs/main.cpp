/*
458. Poor Pigs

There are 1000 buckets, one and only one of them is poisonous, while the rest are filled with water. They all look identical. If a pig drinks the poison it will die within 15 minutes. What is the minimum amount of pigs you need to figure out which bucket is poisonous within one hour?

Answer this question, and write an algorithm for the general case.



General case:

If there are n buckets and a pig drinking poison will die within m minutes, how many pigs (x) you need to figure out the poisonous bucket within p minutes? There is exactly one bucket with poison.



Note:

A pig can be allowed to drink simultaneously on as many buckets as one would like, and the feeding takes no time.
After a pig has instantly finished drinking buckets, there has to be a cool down time of m minutes. During this time, only observation is allowed and no feedings at all.
Any given bucket can be sampled an infinite number of times (by an unlimited number of pigs).
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<stack>
#include<cmath>

using namespace std;

class Solution
{
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest)
    {
        if(minutesToTest < minutesToDie)
            return 0;
        return ceil(log(buckets) / log(floor(minutesToTest/minutesToDie) + 1));
    }
};
int main()
{
    Solution sln;
    cout << sln.poorPigs(1000, 15, 60);
    system("pause");
    return 0;
}
