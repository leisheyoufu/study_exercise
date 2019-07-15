/*
374. Guess Number Higher or Lower

We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number is higher or lower.

You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):

-1 : My number is lower
 1 : My number is higher
 0 : Congrats! You got it!

Example :

Input: n = 10, pick = 6
Output: 6

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_set>
#include<set>

using namespace std;

int guess(int num);

class Solution
{
public:
    int guessNumber(int n)
    {
        if(n<=0) {
            return -1;
        }
        if(n==1) {
            return 1;
        }
        int low = 1, high = n;
        while(low<=high) {
            int mid = low +  (high - low) /2;
            int ret = guess(mid);
            if(ret == 0) {
                return mid;
            } else if(ret== 1) {
                low = mid+1;
            } else {
                high = mid-1;
            }
        }
        return -1;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
