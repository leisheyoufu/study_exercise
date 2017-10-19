/* Ladder
You have to climb up a ladder. The ladder has exactly N rungs, numbered from 1 to N. With each step, you can ascend by one or two rungs. More precisely:

with your first step you can stand on rung 1 or 2,
if you are on rung K, you can move to rungs K + 1 or K + 2,
finally you have to stand on rung N.
Your task is to count the number of different ways of climbing to the top of the ladder.

For example, given N = 4, you have five different ways of climbing, ascending by:

1, 1, 1 and 1 rung,
1, 1 and 2 rungs,
1, 2 and 1 rung,
2, 1 and 1 rungs, and
2 and 2 rungs.
Given N = 5, you have eight different ways of climbing, ascending by:

1, 1, 1, 1 and 1 rung,
1, 1, 1 and 2 rungs,
1, 1, 2 and 1 rung,
1, 2, 1 and 1 rung,
1, 2 and 2 rungs,
2, 1, 1 and 1 rungs,
2, 1 and 2 rungs, and
2, 2 and 1 rung.
The number of different ways can be very large, so it is sufficient to return the result modulo 2P, for a given integer P.

Write a function:

vector<int> solution(vector<int> &A, vector<int> &B);
that, given two non-empty zero-indexed arrays A and B of L integers, returns an array consisting of L integers specifying the consecutive answers; position I should contain the number of different ways of climbing the ladder with A[I] rungs modulo 2B[I].

For example, given L = 5 and:

    A[0] = 4   B[0] = 3
    A[1] = 4   B[1] = 2
    A[2] = 5   B[2] = 4
    A[3] = 5   B[3] = 3
    A[4] = 1   B[4] = 1
the function should return the sequence [5, 1, 8, 0, 1], as explained above.

Assume that:

L is an integer within the range [1..50,000];
each element of array A is an integer within the range [1..L];
each element of array B is an integer within the range [1..30].
Complexity:

expected worst-case time complexity is O(L);
expected worst-case space complexity is O(L), beyond input storage (not counting the storage required for input arguments).
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;

vector<int> solution(vector<int> &A, vector<int> &B)
{
    vector<int>::iterator iter;
    iter = max_element(A.begin(), A.end());
    int M = *iter;
    vector<int> f(M + 1);
    f[0] = f[1] = 1;
    for (int i = 2; i <= M; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    vector<int> ret;
    for (int i = 0; i < A.size(); i++) {
        ret.push_back(f[A[i]] & ((1 << B[i]) - 1));
    }
    return ret;
}

int main()
{
    int a[] = {4, 4, 5, 5, 1};
    int b[] = {3, 2, 4, 3, 1};
    vector<int> A(a, a + sizeof(a) / sizeof(int));
    vector<int> B(b, b + sizeof(b) / sizeof(int));
    vector<int> ret = solution(A, B);
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i] << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
