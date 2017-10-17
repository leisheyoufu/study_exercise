/* MinAbsSum
For a given array A of N integers and a sequence S of N integers from the set {−1, 1}, we define val(A, S) as follows:

val(A, S) = |sum{ A[i]*S[i] for i = 0..N−1 }|
(Assume that the sum of zero elements equals zero.)

For a given array A, we are looking for such a sequence S that minimizes val(A,S).

Write a function:

int solution(vector<int> &A);
that, given an array A of N integers, computes the minimum value of val(A,S) from all possible values of val(A,S) for all possible sequences S of N integers from the set {−1, 1}.

For example, given array:

  A[0] =  1
  A[1] =  5
  A[2] =  2
  A[3] = -2
your function should return 0, since for S = [−1, 1, −1, 1], val(A, S) = 0, which is the minimum possible value.

Assume that:

N is an integer within the range [0..20,000];
each element of array A is an integer within the range [−100..100].
Complexity:

expected worst-case time complexity is O(N*max(abs(A))2);
expected worst-case space complexity is O(N+sum(abs(A))), beyond input storage (not counting the storage required for input arguments).
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;


int solution(vector<int> &A)
{
    int n = A.size();
    int M = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] < 0) {
            A[i] = -A[i];
        }
        M = max(M, A[i]);
        sum += A[i];
    }
    if (M == 0) {
        return 0;
    }
    vector<int> cnt(M + 1, 0);
    for (int i = 0; i < n; i++) {
        cnt[A[i]] ++;
    }
    int s = sum / 2 + 1;
    vector<int> dp(s, -1);
    dp[0] = 0;
    int best = 0;
    for (int i = 1; i <= M; i++) {
        if (cnt[i]) {
            for (int j = 0; j < s; j++) {
                if (dp[j] >= 0) {
                    dp[j] = cnt[i];
                    if (j > best) {
                        best = j;
                    }
                } else if (j >= i && dp[j - i] > 0) {
                    dp[j] = dp[j - i] - 1;
                    if (j > best) {
                        best = j;
                    }
                }
            }
        }
    }
    return sum - best * 2;
}

int main()
{
    int a[] = {1, 5, 2, -2};
    vector<int> v(a, a + sizeof(a) / sizeof(int));
    cout << solution(v) << endl;
    system("pause");
    return 0;
}
