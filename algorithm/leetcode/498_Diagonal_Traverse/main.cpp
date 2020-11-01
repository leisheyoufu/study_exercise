/*
498. Diagonal Traverse

Given a matrix of M x N elements (M rows, N columns), return all elements of the matrix in diagonal order as shown in the below image.



Example:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

Output:  [1,2,4,7,5,3,6,8,9]

Explanation:



Note:

The total number of elements of the given matrix will not exceed 10,000.
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
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix)
    {
        vector<int> ret;
        int m = matrix.size();
        if(m == 0) {
            return ret;
        }
        int n = matrix[0].size();
        if(n== 0) {
            return ret;
        }
        int k = min(m, n);
        int dir = 0;  // 0: x+, y-;   1:x-, y+
        int count = m*n;
        int x = 0, y = 0;
        while(ret.size() < count) {
            cout << ret.size() << ":" << x << " " << y << endl;
            ret.push_back(matrix[y][x]);
            if(dir == 0) {
                if(y == 0 && x<n-1) {
                    x++;
                    dir = 1;
                } else if(x == n-1) {
                    y++;
                    dir = 1;
                } else {
                    x++;
                    y--;
                }
            } else {
                if(x == 0 && y<m-1) {
                    y++;
                    dir = 0;
                } else if(y == m-1) {
                    x++;
                    dir = 0;
                } else {
                    x--;
                    y++;
                }
            }

        }
        return ret;
    }
};

void print(vector<int> v)
{
    for(auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    Solution sln;
    vector<vector<int>> m = {{1,2,3},{4,5,6},{7,8,9}};
    vector<int> v = sln.findDiagonalOrder(m); // 1,2,4,7,5,3,6,8,9
    print(v);
    m = {{1,2},{3,4}};
    v = sln.findDiagonalOrder(m); // 1,2,3,4
    print(v);
    system("pause");
    return 0;
}
