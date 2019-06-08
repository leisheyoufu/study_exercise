/*
354. Russian Doll Envelopes

You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Note:
Rotation is not allowed.

Example:

Input: [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>

using namespace std;

class Solution
{
public:
    struct Rectangle {
        int width;
        int height;
        Rectangle()
        {
            width = 0;
            height = 0;
        }
        Rectangle(int w, int h)
        {
            width = w;
            height = h;
        }
        bool operator<(Rectangle r) const
        {
            return width < r.width || width == r.width && height < r.height;
        }
    };

    int maxEnvelopes(vector<vector<int>>& envelopes)
    {
        int n = envelopes.size();
        if(n==0 || n==1) {
            return n;
        }
        vector<Rectangle> rects(envelopes.size());
        for(int i=0; i<envelopes.size(); i++) {
            rects[i] = Rectangle(envelopes[i][0], envelopes[i][1]);
        }
        sort(rects.begin(), rects.end());
        /*
        for(auto rect: rects) {
            cout << rect.width << " " << rect.height << endl;
        }
        */
        vector<int> dp(n, 1);
        int ret = 1;
        for(int i=1; i<n; i++) {
            for(int j=i-1; j>=0; j--) {
                if(rects[i].width > rects[j].width && rects[i].height > rects[j].height) {
                    dp[i] = max(dp[i], dp[j] +1);
                    ret = max(ret, dp[i]);
                }
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    //vector<vector<int>> envelopes = { {5,4},{6,4},{6,7},{2,3}};  // 3
    vector<vector<int>> envelopes = {{46,89},{50,53},{52,68},{72,45},{77,81}};  // 3
    cout << sln.maxEnvelopes(envelopes) << endl;
    system("pause");
    return 0;
}
