/*
432. All O`one Data Structure

mplement a data structure supporting the following operations:

Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1. If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".
Challenge: Perform all these in O(1) time complexity.

*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<list>
#include<algorithm>
using namespace std;

class AllOne
{
private:
    unordered_map<string, list<pair<string, int> >::iterator> m;
    list<pair<string, int> >l;
public:
    /** Initialize your data structure here. */
    AllOne()
    {

    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key)
    {
        if(m.find(key) == m.end()) {
            l.push_front(make_pair(key, 1));
            m[key] = l.begin();
        } else {
            list<pair<string, int> >::iterator curr = m[key];
            list<pair<string, int> >::iterator iter = curr;
            iter = next(iter);
            while (iter != l.end() && iter->second < curr->second + 1 ) {
                iter = next(iter);
            }
            iter = l.insert(iter, make_pair(key, curr->second + 1));
            l.erase(curr);
            m[key] = iter;
        }
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key)
    {
        if(m.find(key) == m.end()) {
            return;
        }
        list<pair<string, int> >::iterator curr = m[key];
        list<pair<string, int> >::iterator iter = curr;
        if (curr->second == 1) {
            m.erase(curr->first);
            l.erase(curr);
        } else {
            while(iter !=l.begin() && iter->second > curr->second - 1) {
                iter = prev(iter);
            }
            iter = l.insert(++iter, make_pair(key, curr->second - 1));
            l.erase(curr);
            m[key] = iter;
        }
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey()
    {
        if(m.empty()) {
            return "";
        }
        pair<string, int> item = l.back();
        return item.first;
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey()
    {
        if(m.empty()) {
            return "";
        }
        pair<string, int> item = l.front();
        return item.first;
    }
};
int main()
{
    AllOne* obj = new AllOne();
    obj->inc("a");
    obj->inc("b");
    obj->inc("b");
    obj->inc("b");
    obj->inc("b");
    obj->dec("b");
    obj->dec("b");
    cout << "max " << obj->getMaxKey() << endl;
    cout << "min " << obj->getMinKey() << endl;
    /*
     obj->inc("hello");
     obj->inc("hello");
     obj->inc("world");
     obj->inc("world");
     obj->inc("hello");
     obj->dec("world");
     cout << "max " << obj->getMaxKey() << endl;
     cout << "min " << obj->getMinKey() << endl;
     obj->inc("world");
     obj->inc("world");
     obj->inc("leet");
     cout << "max " << obj->getMaxKey() << endl;
     cout << "min " << obj->getMinKey() << endl;
     obj->inc("leet");
     obj->inc("leet");
     cout << "min " << obj->getMinKey() << endl;
     */
    /*
    ["AllOne","inc","inc","inc","inc","inc","dec","getMaxKey","getMinKey","inc","inc","inc","getMaxKey","getMinKey","inc","inc","getMinKey"]
    [[],["hello"],["hello"],["world"],["world"],["hello"],["world"],[],[],["world"],["world"],["leet"],[],[],["leet"],["leet"],[]]
    output:
    [null,null,null,null,null,null,null,"hello","world",null,null,null,"world","leet",null,null,"world"]
    */
    system("pause");
    return 0;
}
