/*
71. Simplify Path

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
*/
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

class Solution
{
public:
    string simplifyPath(string path)
    {
        stack<string> s;
        int n = path.length();
        if (n == 0) {
            return "/";
        }
        if(path[0] != '/') {
            return "/";
        }
        int i = 1;
        string temp = "";
        for(int i=0; i<n; i++) {
            if(path[i] == '/') {
                if(temp.empty()) {
                    continue;
                } else if(temp == ".") {
                    temp = "";
                } else if(temp == "..") {
                    if (!s.empty()) {
                        s.pop();
                    }
                    temp="";
                } else {
                    s.push(temp);
                    temp = "";
                }
            } else {
                temp += path[i];
            }
        }
        if (!temp.empty()) {
            if(temp == "..") {
                if (!s.empty()) {
                    s.pop();
                }
            } else if(temp == ".") {

            } else {
                s.push(temp);
            }
        }
        string ret = "";
        while(!s.empty()) {
            ret = "/" + s.top() + ret;
            s.pop();
        }
        if(ret.empty()) {
            return "/";
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    cout << sln.simplifyPath("/abc/../a") << endl; // /a
    cout << sln.simplifyPath("/a/./b/../../c/") << endl; // /c
    system("pause");
    return 0;
}
