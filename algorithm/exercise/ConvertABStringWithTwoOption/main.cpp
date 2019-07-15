/* 
   op1: append A
   op2: reverse string then append B
*/

#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

/*
bool _is_convert(string from, string target)
{
    int step = target.length() - from.length();
    for(int i=0; i<step; i++) {
        if(target[target.length()-i-1] == 'B') {
            reverse(target.begin(), target.end() -i -1);
        }
    }
    //cout << target.substr(0, target.length()-step) << endl;
    if(target.substr(0, target.length()-step) == from) {
        return true;
    }
    return false;
}
*/

bool _is_convert(string from, string target)
{
    int step = target.length() - from.length();
    int start = 0, end = target.length() -1;
    bool flag = false;  // false tail, true head
    for(int i=0; i<step; i++) {
        if(!flag) {
            if(target[end] == 'B') {
                flag = true;
            }
            end --;
        } else {
            if(target[start] == 'B') {
                flag = false;
            }
            start++;
        }
    }
    target = target.substr(start, end - start +1);
    if(flag) {
        reverse(target.begin(), target.end());
    }
    if(target == from) {
        return true;
    }
    return false;
}


bool is_convert(string word1, string word2)
{
    if(word1.length() == word2.length()) {
        if(word1 == word2) {
            return true;
        }
        return false;
    }
    string from, target;
    if(word1.length() < word2.length()) {
        from = word1;
        target = word2;
    } else {
        from = word2;
        target = word1;
    }
    return _is_convert(from, target);
}


int main()
{
    cout << is_convert("", "") << endl;  // 1
    cout << is_convert("", "A") << endl;  // 1
    cout << is_convert("A", "ABB") << endl;  // 0
    cout << is_convert("BB", "A") << endl;  // 0
    cout << is_convert("BB", "AA") << endl;  // 0
    cout << is_convert("AB", "ABAB") << endl;  // 1
    cout << is_convert("AB", "BBAABBAAA") << endl;  // 0
    cout << is_convert("ABAAAB", "BBAABBAAA") << endl;  // 0
    return 0;
}