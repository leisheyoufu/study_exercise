/*
187. Repeated DNA Sequences
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_set>
using namespace std;

class Solution
{
public:
    /*
    vector<string> findRepeatedDnaSequences(string s)
    {
    	set<string> ret;
    	set<string> st;
    	for(int i=0; i+9 <s.size(); i++) {
    		string sub = s.substr(i, 10);
    		if(st.count(sub)) {
    			ret.insert(sub);
    		} else {
    			st.insert(sub);
    		}
    	}
    	return vector<string>(ret.begin(), ret.end());
    }
    */
    vector<string> findRepeatedDnaSequences(string s)
    {
        unordered_set<string> ret;
        unordered_set<int> st;
        if (s.size() < 11) {
            return vector<string>();
        }
        int curr = 0, i = 0;
        while(i<9) {
            curr = curr << 3 | (s[i++] & 7);
        }
        while( i<s.length()) {
            curr = ((curr & 0x7ffffff) << 3) | (s[i++] & 7);
            if(st.find(curr) != st.end()) {
                ret.insert(s.substr(i-10,10));
            } else {
                st.insert(curr);
            }
        }
        return vector<string>(ret.begin(), ret.end());
    }



    /*
    bool compare(string s, int start, int pst
    {
    	for(int i = 0; i<10; i++) {
    		if(s[i+start] != s[i+pstart]) {
    			return false;
    		}
    	}
    	return true;
    }

    vector<string> findRepeatedDnaSequences(string s)
    {
    	unordered_set<string> vis;
    	vector<string> ret;
    	int pstart = 0;
    	while(pstart+ 10 < s.length()) {
    		string sub = s.substr(pstart, 10);
    		if (vis.find(sub) != vis.end()) {
    			pstart ++;
    			continue;
    		}
    		int start = pstart + 1;
    		bool found = false;
    		while(start + 10 <= s.length()) {
    			if (compare(s, start, pstart)) {
    				vis.insert(sub);
    				ret.push_back(sub);
    				found = true;
    				break;
    			}
    			start++;
    		}
    		if (found) {
    			pstart ++;
    			continue;
    		}
    		vis.insert(sub);
    		pstart ++;
    	}
    	return ret;
    }
    */
};

int main()
{
    Solution sln;
    sln.findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTTTTTTTTTT");
    system("pause");
    return 0;
}
