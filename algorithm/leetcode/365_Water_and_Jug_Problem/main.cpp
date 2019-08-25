/*
365. Water and Jug Problem

ou are given two jugs with capacities x and y litres. There is an infinite amount of water supply available. You need to determine whether it is possible to measure exactly z litres using these two jugs.

If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end.

Operations allowed:

    Fill any of the jugs completely with water.
    Empty any of the jugs.
    Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.

Example 1: (From the famous "Die Hard" example)

Input: x = 3, y = 5, z = 4
Output: True

Example 2:

Input: x = 2, y = 6, z = 5
Output: False

*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool canMeasureWater(int x, int y, int z)
    {
        if(z == 0) {
            return true;
        }
        if(z > x+y)
            return false;
        int c = gcd(max(x, y), min(x, y));
        return (z % c) == 0;
    }

    int gcd(int x, int y)
    {
        return y == 0 ? x : gcd(y, x % y);
    }
};
int main()
{
    Solution sln;
    cout << sln.canMeasureWater(2, 6, 4) << endl;
    cout << sln.canMeasureWater(2, 6, 5) << endl;
    cout << sln.canMeasureWater(0, 0, 0) << endl;
    system("pause");
    return 0;
}
