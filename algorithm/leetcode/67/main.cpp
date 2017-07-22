/*
67. Add Binary

Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<sstream>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    string addBinary(string a, string b)
    {
        if (a.length() < b.length()) {
            string temp = a;
            a = b;
            b = temp;
        }
        int size = b.size();
        vector<int> ret(a.size()+1, 0);
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        for(int i=0; i<size; i++) {
            ret[i] += a[i]-'0' + b[i] - '0';
            if(ret[i] >= 2) {
                ret[i+1] +=1;
                ret[i] = ret[i] %2;
            }
        }
        for(int i=size; i<a.size(); i++) {
            ret[i] += a[i] - '0';
            if(ret[i] >= 2) {
                ret[i+1] +=1;
                ret[i] = ret[i] %2;
            }
        }
        string retStr= "";
        stringstream ss;
        if(ret[a.size()] !=0) {
            ss << ret[a.size()];
        }
        for(int i=a.size()-1; i>=0; i--) {
            ss << ret[i];
        }
        ss >> retStr;
        return retStr;
    }
};
int main()
{
    Solution sln;
    cout << sln.addBinary("1", "11");
    system("pause");
    return 0;
}
