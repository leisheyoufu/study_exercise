/*
388. Longest Absolute File Path

Suppose we abstract our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
    subdir1
    subdir2
        file.ext
The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext
The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the longest absolute path to file in the abstracted file system. If there is no file in the system, return 0.

Note:
The name of a file contains at least a . and an extension.
The name of a directory or sub-directory will not contain a ..
Time complexity required: O(n) where n is the size of the input string.

Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path aaaaaaaaaaaaaaaaaaaaa/sth.png.
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
    int lengthLongestPath(string input)
    {
        vector<int> paths;
        int curr = 0, max_path = 0, level = 0;
        bool isFile = false;
        int n = input.length();
        if(n == 0) {
            return 0;
        }
        for(int i=0; i<n; i++) {
            if(input[i] == '\n') {
                if(!isFile) {
                    if(level == paths.size()) {
                        paths.push_back(curr+1);
                    } else {
                        paths[level] = curr +1;
                    }
                } else {
                    if(curr > max_path) {
                        max_path = curr;
                    }
                }
                isFile = false;
                curr = 0;
                level = 0;
                continue;
            }
            if(input[i] == '\t') {
                level ++;
                if(level > paths.size()) {
                    return 0;
                }
                curr = paths[level-1];
                continue;
            }

            if(input[i] == '.') {
                isFile = true;
            }
            curr++;
            //cout << "level = " << level << " paths size " << paths.size() << " curr " << curr <<  endl;
        }
        if(isFile && curr > max_path) {
            max_path = curr;
        }
        return max_path;
    }
};


int main()
{
    Solution sln;
    cout << sln.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext") << endl; // 32
    cout << sln.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") << endl;  // 20
    system("pause");
    return 0;
}
