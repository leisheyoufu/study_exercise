/*
208. Implement Trie (Prefix Tree)

Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class TrieNode
{
private:
    TrieNode *child[26];
    bool flag;
public:
    TrieNode()
    {
        flag = false;
        memset(child, 0, sizeof(child));
    }
    bool existChild(int index)
    {
        return child[index]? true : false;
    }
    void addChild(TrieNode *node, int index)
    {
        child[index] = node;
    }
    TrieNode *getChild(int index)
    {
        return child[index];
    }
    void setFlag()
    {
        flag = true;
    }
    bool isFlag()
    {
        return flag;
    }
};

class Trie
{
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    Trie()
    {
        root = new TrieNode();
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        TrieNode *curr = root;
        for(auto ch : word) {
            int i = ch - 'a';
            if(!curr->getChild(i)) {
                TrieNode *child = new TrieNode();
                curr->addChild(child, i);
            }
            curr = curr->getChild(i);
        }
        curr->setFlag();
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        TrieNode *curr = root;
        for(auto ch : word) {
            int i = ch - 'a';
            if(curr->getChild(i)) {
                curr = curr->getChild(i);
            } else {
                return false;
            }
        }
        if(curr->isFlag()) {
            return true;
        }
        return false;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        TrieNode *curr = root;
        for(auto ch : prefix) {
            int i = ch - 'a';
            if(curr->getChild(i)) {
                curr = curr->getChild(i);
            } else {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Trie *tree = new Trie();
    tree->insert("hello");
    tree->insert("hi");
    tree->insert("ab");

    cout << tree->search("hell") << endl; // false
    cout << tree->startsWith("hel") << endl; // true
    cout << tree->search("hi") << endl; // true
    cout << tree->search("a") << endl; // false
    cout << tree->startsWith("a") << endl; // true
    system("pause");
    return 0;
}
