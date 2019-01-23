/*
319. Bulb Switcher

There are n bulbs that are initially off. You first turn on all the bulbs. Then, you turn off every second bulb. On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). For the i-th round, you toggle every i bulb. For the n-th round, you only toggle the last bulb. Find how many bulbs are on after n rounds.

Example:

Input: 3
Output: 1
Explanation:
At first, the three bulbs are [off, off, off].
After first round, the three bulbs are [on, on, on].
After second round, the three bulbs are [on, off, on].
After third round, the three bulbs are [on, off, off].

So you should return 1, because there is only one bulb is on.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include <functional>
#include<queue>

using namespace std;

class Solution
{
public:

    int bulbSwitch(int n)
    {
        int i = 1;
        while(i*i < n) {
            i++;
        }
        if(i*i == n) {
            return i;
        }
        return i-1;
    }
};
int main()
{
    Solution sln;
    cout << sln.bulbSwitch(8) << endl;
    system("pause");
    return 0;
}
