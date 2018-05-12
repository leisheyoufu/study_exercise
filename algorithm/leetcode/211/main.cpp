/*
211. Add and Search Word - Data structure design
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class TrieNode
{
private:
    TrieNode *node[26];
    bool mark;

public:
    TrieNode()
    {
        mark = false;
        memset(node, 0, sizeof(node));
    }
    void insert(string word)
    {
        TrieNode *curr = this;
        for(auto ch : word) {
            int i = ch - 'a';
            if(!curr->node[i]) {
                curr ->node[i] = new TrieNode();
            }
            curr = curr->node[i];
        }
        curr->mark = true;
    }
    bool search(TrieNode *curr, string word)
    {
        if(word.empty() && curr->mark) {
            return true;
        }
        int i;
        bool flag = true;
        for(i = 0; i<word.length(); i++) {
            char ch = word[i];
            if(ch == '.') {
                TrieNode *temp = curr;
                for(int k=0; k<26; k++) {
                    flag = false;
                    if(temp->node[k]) {
                        if(search(temp->node[k], word.substr(i+1, word.length() - i-1))) {
                            return true;
                        }
                        curr = temp->node[k];
                    }
                }
            } else {
                ch = ch - 'a';
                if(curr->node[ch]) {
                    curr = curr->node[ch];
                } else {
                    return false;
                }
            }
        }
        if(flag)
            return curr->mark;
        return false;
    }

};
class WordDictionary
{
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    WordDictionary()
    {
        root = new TrieNode();
    }

    /** Adds a word into the data structure. */
    void addWord(string word)
    {
        root->insert(word);
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word)
    {
        return root->search(root, word);
    }
};

int main()
{
    WordDictionary dict;
    dict.addWord("bad");
    dict.addWord("dad");
    dict.addWord("mad");
    cout << dict.search("pad") << endl;  // 0
    cout << dict.search("bad") << endl;  // 1
    cout << dict.search(".ad") << endl;  // 1
    cout << dict.search("b..") << endl;  // 1
    cout << dict.search("....") << endl; // 0
    system("pause");
    return 0;
}
