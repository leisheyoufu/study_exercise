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
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    string simplifyPath(string path)
    {
        vector<string> paths;
        int n = path.length();
        int i = 1;
        bool mark = false;
        string s="";
        while(i<n) {
            if(path[i] == '/' && s.length() > 0) {
                paths.push_back(s);
                s.clear();
                i++;
                continue;
            }
            if (s.size()== 0 && path[i] == '.' && i+1<n && path[i+1] == '/') {
                s.clear();
                i+=2;
                continue;
            }
            if(s.size()== 0 && path[i] == '.' && i+2<n && path[i+1] == '.' && path[i+2] == '/') {
                s.clear();
                if(paths.size() > 0) {
                    paths.pop_back();
                }
                i+=3;
                continue;
            }
            if (path[i] == '/') {
                i++;
                continue;
            }
            s += path[i++];

        }
        if (s.length() >0 && s!="." && s!=".." && s!= "/") {
            paths.push_back(s);
        } else if ( s== ".." && paths.size()>0) {
            paths.pop_back();
        }
        string ret;
        if( paths.size() == 0) {
            ret= "/";
        }
        for(int i=0; i<paths.size(); i++) {
            ret = ret + '/' + paths[i];
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    cout << sln.simplifyPath("/..") << endl;
    system("pause");
    return 0;
}
