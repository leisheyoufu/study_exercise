/*

440. K-th Smallest in Lexicographical Order

Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.

Note: 1 ≤ k ≤ n ≤ 109.

Example:

Input:
n: 13   k: 2

Output:
10

Explanation:
The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int findKthNumber(int n, int k)
    {
        int result = 1;
        int lastSteps = k - 1; //默认走了一步，走到第一个数
        while (lastSteps > 0) {
            long left = result; //用 long 类型，防止 n 达到 2的32次方附近时，left * 10 会溢出
            long right = result + 1;
            int count = 0;
            while(left <= n) { //向下或向右探索，计算需要跨过的节点数
                count += min((int)right, n+1) - left;
                left *= 10;
                right *= 10;
            }

            if (count > lastSteps) { //节点太多，跨不过去，只能向下走一层
                lastSteps --;
                result *= 10;
            } else { //节点不足，当前剩余步数足够走完全部节点，直接跨过这个节点以及他的子节点，向右走一步
                lastSteps -= count;
                result ++;
            }
        }
        return result;
    }
};

int main()
{
    Solution sln;
    cout << sln.findKthNumber(9999999,98765) << endl;  // 1088886
    system("pause");
    return 0;
}
