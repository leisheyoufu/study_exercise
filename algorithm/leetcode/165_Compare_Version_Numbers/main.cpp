/*
165. Compare Version Numbers
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int com_int_str(string a, string b)
    {
        int n1 = a.length();
        int n2 = b.length();
        int s1 = 0, s2 = 0;
        while(s1 < n1 && a[s1] == '0') {
            s1 ++;
        }
        while(s2 < n2 && b[s2] == '0') {
            s2 ++;
        }
        a = a.substr(s1, n1-s1);
        b = b.substr(s2, n2-s2);
        n1 = a.length();
        n2 = b.length();
        if (n1<n2) {
            return -1;
        } else if (n1>n2) {
            return 1;
        }
        for(int i=s1; i<n1; i++) {
            if(a[i] > b[i]) {
                return 1;
            } else if(a[i] < b[i]) {
                return -1;
            }
        }
        return 0;
    }
    int compareVersion(string version1, string version2)
    {
        vector<string> nums1;
        vector<string> nums2;
        int pos1, pos2, start1 = 0, start2 =0;
        bool end1=false, end2 = false;
        do {
            pos1 = version1.find(".", start1);
            if(pos1 != string::npos) {
                nums1.push_back(version1.substr(start1, pos1-start1));
                start1= pos1 + 1;
            } else if (!end1) {
                nums1.push_back(version1.substr(start1, version1.length()-start1));
                end1 = true;
            } else {
                nums1.push_back("0");
            }

            pos2 = version2.find(".", start2);
            if(pos2 != string::npos) {
                nums2.push_back(version2.substr(start2, pos2-start2));
                start2= pos2 + 1;
            } else if (!end2) {
                nums2.push_back(version2.substr(start2, version2.length()-start2));
                end2 = true;
            } else {
                nums2.push_back("0");
            }
        } while(pos1 != string::npos || pos2 != string::npos);
        int n = nums1.size();
        for(int i=0; i<n; i++) {
            int ret = com_int_str(nums1[i], nums2[i]);
            if(  ret != 0 ) {
                return ret;
            }
        }
        return 0;
    }
};

int main()
{
    Solution sln;
    // cout << sln.compareVersion("1.0","1");
    //cout << sln.compareVersion("1.2","13.7");
    cout << sln.compareVersion("01","1.0");
    system("pause");
    return 0;
}
