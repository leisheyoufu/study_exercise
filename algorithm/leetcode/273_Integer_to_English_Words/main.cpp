/*
273. Integer to English Words

Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

Example 1:

Input: 123
Output: "One Hundred Twenty Three"
Example 2:

Input: 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Example 3:

Input: 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Example 4:

Input: 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Solution
{

public:
    vector<string> a = {"","Thousand", "Million", "Billion"};
    vector<string> b = {"Ten", "Twenty", "Thirty", "Forty",
                        "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
                       };
    vector<string> c = {"Ten", "Eleven", "Twelve", "Thirt1een",
                        "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
                       };
    vector<string> d = {"One", "Two", "Three", "Four",
                        "Five", "Six", "Seven", "Eight", "Nine"
                       };
    string join(vector<string> a)
    {
        if(a.size() == 0) {
            return "";
        }
        string ret = a[0];
        for(int i=1; i<a.size(); i++) {
            if(a[i] == "") {
                continue;
            }
            ret += " " + a[i];
        }
        return ret;
    }
    vector<string> convert(int num)
    {
        vector<string> ret;
        while(num) {
            int next = num / 1000;
            int curr = num % 1000;
            vector<string> strs;
            if( curr / 100) {
                strs.push_back(d[curr / 100 -1] + " Hundred");
            }
            curr %= 100;

            if(curr / 10 > 1) {
                strs.push_back(b[curr/10-1]);
                if(curr%10 >= 1) {
                    strs.push_back(d[curr%10 - 1]);
                }
            } else if(curr / 10 == 1) {
                strs.push_back(c[curr%10]);
            } else {
                strs.push_back(d[curr%10-1]);
            }
            num = next;
            string s = join(strs);
            ret.push_back(s);
        }
        return ret;
    }

    string numberToWords(int num)
    {
        if(num == 0) {
            return "Zero";
        }
        vector<string> ss = convert(num);
        int size = ss.size();
        vector<string> strs;
        for(int i=size-1; i>0; i--) {
            strs.push_back(ss[i] + " " + a[i]);
        }
        strs.push_back(ss[0]);
        return join(strs);
    }
};
int main()
{
    Solution sln;
    // cout << sln.numberToWords(123) << endl;  // "One Hundred Twenty Three"
    // cout << sln.numberToWords(1234567) << endl; // "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
    // cout << sln.numberToWords(1234567891) << endl; // "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
    //cout << sln.numberToWords(93902) << endl; // "Ninety Three Thousand Nine Hundred Two"
    cout << sln.numberToWords(300) << endl;
    system("pause");
    return 0;
}
