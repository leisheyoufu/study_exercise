/*
386. Lexicographical Numbers

Given an integer n, return 1 - n in lexicographical order.

For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space. The input size may be as large as 5,000,000.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;

class Solution
{
public:
    vector<int> lexicalOrder(int n)
    {
        vector<int> ret;
        if(n <=0) {
            return ret;
        }
        ret.push_back(1);
        int num = 1;
        for(int i=1; i<n; i++) {
            if(num * 10 <=n) {
                num*=10;
            } else {
                while(num %10 == 9 || num == n) {
                    num /= 10;
                }
                num++;
            }
            ret.push_back(num);
        }
        return ret;
    }
};

void print(vector<int> nums)
{
    for(int num: nums) {
        cout << num << " ";
    }
    cout << endl;
}
int main()
{
    Solution sln;
    vector<int> ret = sln.lexicalOrder(13);
    print(ret); // 1 10 11 12 13 2 3 4 5 6 7 8 9
    system("pause");
    return 0;
}
