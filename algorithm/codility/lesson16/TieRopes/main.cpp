/* TieRopes
The ropes are shown in the figure below.



We can tie:

rope 1 with rope 2 to produce a rope of length A[1] + A[2] = 5;
rope 4 with rope 5 with rope 6 to produce a rope of length A[4] + A[5] + A[6] = 5.
After that, there will be three ropes whose lengths are greater than or equal to K = 4. It is not possible to produce four such ropes.

Write a function:

int solution(int K, vector<int> &A);

that, given an integer K and a non-empty zero-indexed array A of N integers, returns the maximum number of ropes of length greater than or equal to K that can be created.

For example, given K = 4 and array A such that:

    A[0] = 1
    A[1] = 2
    A[2] = 3
    A[3] = 4
    A[4] = 1
    A[5] = 1
    A[6] = 3
the function should return 3, as explained above.

Assume that:

N is an integer within the range [1..100,000];
K is an integer within the range [1..1,000,000,000];
each element of array A is an integer within the range [1..1,000,000,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;


int solution(int K, vector<int> &A)
{
    if (A.empty()) {
        return 0;
    }
    int ret = 0;
    int curr = 0;
    for (int i = 0; i < A.size(); i++) {
        curr += A[i];
        if (curr >= K) {
            ret++;
            curr = 0;
        }
    }
    return ret;
}

int main()
{
    int a[] = {1, 2, 3, 4, 1, 1, 3};
    vector<int> v(a, a + sizeof(a) / sizeof(int));
    cout << solution(4, v) << endl;
    system("pause");
    return 0;
}
