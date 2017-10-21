/* FibFrog
The Fibonacci sequence is defined using the following recursive formula:

    F(0) = 0
    F(1) = 1
    F(M) = F(M - 1) + F(M - 2) if M >= 2
A small frog wants to get to the other side of a river. The frog is initially located at one bank of the river (position −1) and wants to get to the other bank (position N). The frog can jump over any distance F(K), where F(K) is the K-th Fibonacci number. Luckily, there are many leaves on the river, and the frog can jump between the leaves, but only in the direction of the bank at position N.

The leaves on the river are represented in a zero-indexed array A consisting of N integers. Consecutive elements of array A represent consecutive positions from 0 to N − 1 on the river. Array A contains only 0s and/or 1s:

0 represents a position without a leaf;
1 represents a position containing a leaf.
The goal is to count the minimum number of jumps in which the frog can get to the other side of the river (from position −1 to position N). The frog can jump between positions −1 and N (the banks of the river) and every position containing a leaf.

For example, consider array A such that:

    A[0] = 0
    A[1] = 0
    A[2] = 0
    A[3] = 1
    A[4] = 1
    A[5] = 0
    A[6] = 1
    A[7] = 0
    A[8] = 0
    A[9] = 0
    A[10] = 0
The frog can make three jumps of length F(5) = 5, F(3) = 2 and F(5) = 5.

Write a function:

int solution(vector<int> &A);
that, given a zero-indexed array A consisting of N integers, returns the minimum number of jumps by which the frog can get to the other side of the river. If the frog cannot reach the other side of the river, the function should return −1.

For example, given:

    A[0] = 0
    A[1] = 0
    A[2] = 0
    A[3] = 1
    A[4] = 1
    A[5] = 0
    A[6] = 1
    A[7] = 0
    A[8] = 0
    A[9] = 0
    A[10] = 0
the function should return 3, as explained above.

Assume that:

N is an integer within the range [0..100,000];
each element of array A is an integer that can have one of the following values: 0, 1.
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;

int solution(vector<int> &A)
{
    if (A.empty()) {
        return 1;
    }
    int n = A.size();
    int N = max(n, 4);
    vector<int> f(N + 2, 0);
    f[1] = f[2] = 1;
    for (int i = 3; i <= N + 1; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    vector<int> dp(n + 2, INT_MAX);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] == 1) {
            int step = i + 1;
            for (int j = 1; f[j] <= step; j++) {
                if (step == f[j]) {
                    dp[step] = 1;
                    continue;
                }
                if (step > f[j] && dp[step - f[j]] != INT_MAX) {
                    dp[step] = min(dp[step], dp[step - f[j]] + 1);
                }
            }
        }
    }
    int step = n + 1;
    for (int j = 1; f[j] <= step; j++) {
        if (step == f[j]) {

            dp[step] = 1;
            continue;
        }
        if (step > f[j] && dp[step - f[j]] != INT_MAX) {
            dp[step] = min(dp[step], dp[step - f[j]] + 1);
        }
    }
    if (dp[step] == INT_MAX) {
        return -1;
    }
    return dp[step];
}

int main()
{
    int a[] = {0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0};
    //int a[] = {0,0,0};
    //int a[] = {1,1};
    vector<int> A(a, a + sizeof(a) / sizeof(int));
    cout << solution(A) << endl;
    system("pause");
    return 0;
}
