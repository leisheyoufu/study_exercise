/*
443. String Compression

Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:

If the group's length is 1, append the character to s.
Otherwise, append the character followed by the group's length.
The compressed string s should not be returned separately, but instead be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.


Follow up:
Could you solve it using only O(1) extra space?



Example 1:

Input: chars = ["a","a","b","b","c","c","c"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
Example 2:

Input: chars = ["a"]
Output: Return 1, and the first character of the input array should be: ["a"]
Explanation: The only group is "a", which remains uncompressed since it's a single character.
Example 3:

Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
Example 4:

Input: chars = ["a","a","a","b","b","a","a"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","3","b","2","a","2"].
Explanation: The groups are "aaa", "bb", and "aa". This compresses to "a3b2a2". Note that each group is independent even if two groups have the same character.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int set_char(vector<char>& chars, int i, char ch, int count)
    {
        chars[i++] = ch;
        if(count == 1) {
            return i;
        }
        int temp = count, moder = 1, len = 1;
        while(temp >= 10) {
            moder *= 10;
            temp /= 10;
            len ++;
        }
        while(len > 0) {
            int bit = count / moder;
            count -= moder *bit;
            chars[i++] = bit + '0';
            moder /= 10;
            len--;
        }
        return i;
    }
    int compress(vector<char>& chars)
    {
        int n = chars.size();
        if(n == 0) {
            return 0;
        }
        int j=0, count = 1;
        char last = chars[0];
        for(int i=1; i<n; i++) {
            if(chars[i] != last) {
                j = set_char(chars, j, last, count);
                count = 1;
                last = chars[i];
            } else {
                count ++;
            }
        }

        j = set_char(chars, j, last, count);
        return j;
    }
};

int main()
{
    Solution sln;
    vector<char> chars = {'a','a','b','b','c','c','c'}; // 6
    cout << sln.compress(chars) << endl;
    chars = {'a'};
    cout << sln.compress(chars) << endl; // 1
    chars = {'a','b','b','b','b','b','b','b','b','b','b','b','b'};
    cout << sln.compress(chars) << endl; // 4
    chars = {'a','a','a','b','b','a','a'};
    cout << sln.compress(chars) << endl; // 6
    chars = {'o','o','o','o','o','o','o','o','o','o'};
    cout << sln.compress(chars) << endl; // 3
    system("pause");
    return 0;
}
