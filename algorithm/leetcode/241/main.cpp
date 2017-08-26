/*
241. Different Ways to Add Parentheses

Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.


Example 1
Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]


Example 2
Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]
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
    void parse(string input, vector<int> &nums, vector<char> &ops)
    {
        int temp = 0;
        for(int i=0; i<input.length(); i++) {
            if(input[i] == '+' || input[i] == '-' || input[i] == '*') {
                nums.push_back(temp);
                temp = 0;
                ops.push_back(input[i]);
            } else if(temp == 0) {
                temp = input[i] - '0';
            } else {
                temp = temp*10 + input[i] - '0';
            }
        }
        nums.push_back(temp);
    }

    vector<int> diffWaysToCompute(string input)
    {
        vector<int> nums;
        vector<char> ops;
        parse(input, nums, ops);
        int n = nums.size();
        vector<vector<vector<int>>> results(n, vector<vector<int>>(n, vector<int>()));
        for(int i=0; i<nums.size(); i++) {
            results[i][i].push_back(nums[i]);
        }
        dfs(results, ops, 0, n-1);
        return results[0][n-1];
    }
    void calc(vector<vector<vector<int>>> &results, int i, int j, int k, char op)
    {
        vector<int> *left;
        vector<int> *right;
        left = &results[i][k];
        right = &results[k+1][j];
        for(vector<int>::iterator iter1 = (*left).begin(); iter1!=(*left).end(); iter1++) {
            for(vector<int>::iterator iter2 = (*right).begin(); iter2!=(*right).end(); iter2++) {
                int val;
                if(op=='+') {
                    val = *iter1 + *iter2;
                } else if(op=='-') {
                    val = *iter1 - *iter2;
                } else if(op=='*') {
                    val = *iter1 * (*iter2);
                }
                results[i][j].push_back(val);
            }
        }
    }
    void dfs(vector<vector<vector<int>>> &results, vector<char> &ops, int i, int j)
    {
        if(!results[i][j].empty()) {
            return;
        }

        for(int k=i; k<j; k++) {
            dfs(results, ops, i, k);
            dfs(results, ops, k+1, j);
            char op = ops[k];
            calc(results, i, j, k, op);
        }
    }
};
int main()
{
    Solution sln;
    string input = "2*3-4*5";
    vector<int> ret = sln.diffWaysToCompute(input);
    for(int i=0; i<ret.size(); i++) {
        cout << ret[i] << " ";
    }
    system("pause");
    return 0;
}
