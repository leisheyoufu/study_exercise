/*
401. Binary Watch

A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

Each LED represents a zero or one, with the least significant bit on the right.


For example, the above binary watch reads "3:25".

Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

Example:

Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
Note:
The order of output does not matter.
The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_set>
#include<set>

using namespace std;

class Solution
{
public:
    vector<string> readBinaryWatch(int num)
    {
        vector<string> ret;
        if (num <0 || num >10) {
            return ret;
        }
        set<string> s;
        vector<pair<int,int> > pairs;
        dfs(num, pairs, 0, 0);
        for (auto item : pairs) {
            string h = to_string(item.first);
            string m = to_string(item.second);
            if (item.second < 10) {
                m = "0" + m;
            }
            s.insert(h + ":" + m);
        }
        ret = {s.begin(), s.end()};
        return ret;
    }

    void dfs(int n, vector<pair<int, int> > &ret, int hour, int minute)
    {
        if(n == 0) {
            ret.push_back(make_pair(hour, minute));
            return;
        }
        for(int i = 0; i< 4; i++) {
            if ((hour & (1 << i)) == 0 && (hour | (1 << i)) <=11) {
                dfs(n-1, ret, hour | (1 << i), minute);
            }
        }
        for(int i=0; i< 6; i++) {
            if ((minute & (1 << i)) == 0 && (minute | (1 << i)) <= 59) {
                dfs(n-1, ret, hour, minute | (1 << i));
            }
        }
    }
};

int main()
{
    Solution sln;
    vector<string> ret;
    ret = sln.readBinaryWatch(1);
    for(string s : ret) {
        cout << s << " "; // ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
    }
    cout << endl;
    system("pause");
    return 0;
}
