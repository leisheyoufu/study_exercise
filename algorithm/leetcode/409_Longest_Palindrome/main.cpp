/*
409. Longest Palindrome

Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome here.



Example 1:

Input: s = "abccccdd"
Output: 7
Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
Example 2:

Input: s = "a"
Output: 1
Example 3:

Input: s = "bb"
Output: 2

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Solution
{
public:
    int longestPalindrome(string s)
    {
        if (s.length() == 0) {
            return 0;
        }
        unordered_map<char, int> m;
        for(char c:s) {
            if (m.count(c) == 0) {
                m[c] = 1;
            } else {
                m[c] ++;
            }
        }
        int count = 0, max_count = 0;
        for (auto c: m) {
            if (c.second % 2 == 0) {
                count += c.second;
            } else {
                max_count = max(max_count, c.second);
            }
        }
        int odd = 0;
        for (auto c: m) {
            if (c.second % 2 != 0) {
                if (c.second != max_count) {
                    count += c.second - 1;
                } else if(c.second == max_count) {
                    odd ++;
                }
            }
        }
        if(odd ==0) {
            return count + max_count;
        }
        return count + max_count + (max_count-1)*(odd-1);
    }
};

int main()
{
    Solution sln;
    cout << sln.longestPalindrome("abccccdd") << endl; // 7
    cout << sln.longestPalindrome("a") << endl; // 1
    cout << sln.longestPalindrome("bb") << endl; // 2
    cout << sln.longestPalindrome("ibvjkmpyzsifuxcabqqpahjdeuzaybqsrsmbfplxycsafogotliyvhxjtkrbzqxlyfwujzhkdafhebvsdhkkdbhlhmaoxmbkqiwiusngkbdhlvxdyvnjrzvxmukvdfobzlmvnbnilnsyrgoygfdzjlymhprcpxsnxpcafctikxxybcusgjwmfklkffehbvlhvxfiddznwumxosomfbgxoruoqrhezgsgidgcfzbtdftjxeahriirqgxbhicoxavquhbkaomrroghdnfkknyigsluqebaqrtcwgmlnvmxoagisdmsokeznjsnwpxygjjptvyjjkbmkxvlivinmpnpxgmmorkasebngirckqcawgevljplkkgextudqaodwqmfljljhrujoerycoojwwgtklypicgkyaboqjfivbeqdlonxeidgxsyzugkntoevwfuxovazcyayvwbcqswzhytlmtmrtwpikgacnpkbwgfmpavzyjoxughwhvlsxsgttbcyrlkaarngeoaldsdtjncivhcfsaohmdhgbwkuemcembmlwbwquxfaiukoqvzmgoeppieztdacvwngbkcxknbytvztodbfnjhbtwpjlzuajnlzfmmujhcggpdcwdquutdiubgcvnxvgspmfumeqrofewynizvynavjzkbpkuxxvkjujectdyfwygnfsukvzflcuxxzvxzravzznpxttduajhbsyiywpqunnarabcroljwcbdydagachbobkcvudkoddldaucwruobfylfhyvjuynjrosxczgjwudpxaqwnboxgxybnngxxhibesiaxkicinikzzmonftqkcudlzfzutplbycejmkpxcygsafzkgudy") << endl; // 867
    system("pause");
    return 0;
}
