/*
546. Remove Boxes

Given several boxes with different colors represented by different positive numbers.
You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
Find the maximum points you can get.



Example 1:

Input: boxes = [1,3,2,2,2,3,4,3,1]
Output: 23
Explanation:
[1, 3, 2, 2, 2, 3, 4, 3, 1]
----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
----> [1, 3, 3, 3, 1] (1*1=1 points)
----> [1, 1] (3*3=9 points)
----> [] (2*2=4 points)


Constraints:

1 <= boxes.length <= 100
1 <= boxes[i] <= 100
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
    int removeBoxes(vector<int>& boxes)
    {
        int len = boxes.size();
        int dp[100][100][100] = {0};
        for (int i = 0; i < len; i++) {
            for (int k = 0; k <= i; k++) {
                dp[i][i][k] = (k + 1) * (k + 1);
            }
        }
        for (int l = 1; l < len; l++) {
            for (int j = l; j < len; j++) {
                int i = j - l;
                for (int k = 0; k <= i; k++) {
                    int res = (k + 1) * (k + 1) + dp[i + 1][j][0];
                    for (int m = i + 1; m <= j; m++) {
                        if (boxes[m] == boxes[i]) {
                            res = max(res, dp[i + 1][m - 1][0] + dp[m][j][k + 1]);
                        }
                    }
                    dp[i][j][k] = res;
                }
            }
        }
        return dp[0][len - 1][0];
    }

}
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
