/*
433. Minimum Genetic Mutation

A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations. A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be valid.
You may assume start and end string is not the same.


Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1


Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2


Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<queue>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int minMutation(string start, string end, vector<string>& bank)
    {
        string convert = "ACGT";
        unordered_set<string> s(bank.begin(), bank.end());
        unordered_set<string> vis;
        queue<string> q;
        q.push(start);
        int ret = 0;
        while(!q.empty()) {
            int n = q.size();
            while(n > 0) {
                n--;
                string word = q.front();
                if (word == end) {
                    return ret;
                }
                q.pop();
                string newword = word;
                for(int i=0; i<word.length(); i++) {
                    for(auto c : convert) {
                        char ch = newword[i];
                        if (ch != c) {
                            newword[i] = c;
                            if(!s.count(newword) || vis.count(newword)) {
                                newword[i] = ch;
                                continue;
                            }
                            q.push(newword);
                            vis.insert(newword);
                            newword[i] = ch;
                        }
                    }
                }
            }
            ret ++;
        }
        return -1;
    }
};
int main()
{
    Solution sln;
    vector<string> bank = {"AACCGGTA", "AACCGCTA", "AAACGGTA"};
    cout << sln.minMutation("AACCGGTT", "AAACGGTA", bank) << endl; // 2
    bank = {"AACCGGTA"};
    cout << sln.minMutation("AACCGGTT", "AACCGGTA", bank) << endl; // 1
    bank = {"AAAACCCC", "AAACCCCC", "AACCCCCC"};
    cout << sln.minMutation("AAAAACCC", "AACCCCCC", bank) << endl; // 3
    system("pause");
    return 0;
}
