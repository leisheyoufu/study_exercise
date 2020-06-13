/*
391. Perfect Rectangle

Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.

Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).


Example 1:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [3,2,4,4],
  [1,3,2,4],
  [2,3,3,4]
]

Return true. All 5 rectangles together form an exact cover of a rectangular region.




Example 2:

rectangles = [
  [1,1,2,3],
  [1,3,2,4],
  [3,1,4,2],
  [3,2,4,4]
]

Return false. Because there is a gap between the two rectangular regions.




Example 3:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [3,2,4,4]
]

Return false. Because there is a gap in the top center.




Example 4:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [2,2,4,4]
]

Return false. Because two of the rectangles overlap with each other.

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class Solution
{
public:
    bool isRectangleCover(vector<vector<int>>& rectangles)
    {
        unordered_map<string, int> m;
        for(int i=0; i<rectangles.size(); i++) {
            for(int j=0; j<4; j++) {
                // 0, 1 ; 0, 3,  2,1;  2,3
                string point = to_string(rectangles[i][j/2*2]) + ',' + to_string(rectangles[i][j%2*2+1]);
                if(m[point] & 1<<j) {
                    return false;
                }
                m[point] |= 1<<j;
            }
        }
        int corner = 0;
        for(auto &item : m) {
            int val = item.second;
            if(! (val & (val -1))) {
                corner++;
                if(corner > 4) {
                    return false;
                }
            } else {
                // 11, 1010, 101, 1010, 1111
                // two points merge and 4 points merge
                if(!(val==3||val==12||val==5||val==10||val==15)) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    Solution sln;
    vector<vector<int>> rectangles = {
        {1,1,3,3},
        {3,1,4,2},
        {3,2,4,4},
        {1,3,2,4},
        {2,3,3,4}
    };
    cout << sln.isRectangleCover(rectangles) << endl; // true
    rectangles = {
        {1,1,2,3},
        {1,3,2,4},
        {3,1,4,2},
        {3,2,4,4}
    };
    cout << sln.isRectangleCover(rectangles) << endl; // false
    system("pause");
    return 0;
}
