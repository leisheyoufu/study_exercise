/*
299. Bulls and Cows

You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.

Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows.

Please note that both secret number and friend's guess may contain duplicate digits.

Example 1:

Input: secret = "1807", guess = "7810"

Output: "1A3B"

Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.
Example 2:

Input: secret = "1123", guess = "0111"

Output: "1A1B"

Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.
Note: You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;



class Solution
{
public:
    string getHint(string secret, string guess)
    {
        if(secret.length() == 0) {
            return "A0B0";
        }
        if(secret.length() != guess.length()) {
            return "A0B0";
        }
        int n = guess.length();
        int b = 0, a = 0;
        int bits[10] = {0};  // 1,2,... 9,0
        for(int i=0; i<n; i++) {
            bits[guess[i] - '0']++;
        }
        for(int i=0; i<n; i++) {
            int ch = secret[i] - '0';
            if(secret[i] == guess[i]) {
                if(bits[ch] > 0) {
                    bits[ch] --;
                } else {
                    b--;
                }
                a++;
            } else if(bits[ch] > 0) {
                bits[ch] --;
                b++;
            }
        }
        return to_string(a) + "A" +  to_string(b) + "B";
    }
};

int main()
{
    Solution sln;
    cout << sln.getHint("1807", "7810") << endl;
    cout << sln.getHint("1123", "0111") << endl;
    system("pause");
    return 0;
}
