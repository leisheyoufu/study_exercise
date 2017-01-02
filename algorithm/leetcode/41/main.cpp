#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

    int firstMissingPositive(vector<int>& A)
    {
        int n = A.size();
        for(int i=0; i<n; i++) {
            while(A[i] != i+1) {
                if(A[i]<=0 || A[i] >= n || A[i] == A[A[i]-1]) {
                    break;
                }
                int temp = A[i];
                A[i] = A[temp-1];
                A[temp-1] = temp;
            }
        }
        for(int i=0; i<n; i++) {
            if(A[i] != i+1) {
                return i+1;
            }
        }
        return n+1;
    }
};
int main()
{
    Solution sln;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(0);

    printf("%d\n",sln.firstMissingPositive(nums));
    getch();
    return 0;
}
