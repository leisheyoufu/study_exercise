/*
146. LRU Cache

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 capacity );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
#include<list>
using namespace std;

class LRUCache
{
public:
    list<pair<int,int>> l;
    unordered_map<int, list<pair<int,int>>::iterator> m;
    int capacity;
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }

    int get(int key)
    {
        if(m.find(key) == m.end()) {
            return -1;
        }
        list<pair<int,int>>::iterator iter = m[key];
        int val = iter->second;
        l.erase(iter);
        l.push_front(make_pair(key, val));
        m[key] = l.begin();
        return val;
    }

    void put(int key, int value)
    {
        if(m.find(key) != m.end()) {
            list<pair<int,int>>::iterator iter = m[key];
            l.erase(iter);
            l.push_front(make_pair(key, value));
            m[key] = l.begin();
            return;
        }
        if(l.size() == capacity) {
            m.erase(l.back().first);
            l.pop_back();
        }
        l.push_front(make_pair(key, value));
        m[key] = l.begin();
    }
};

int main()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);       // returns 1
    cache.put(3, 3);    // evicts key 2
    cache.get(2);       // returns -1 (not found)
    cache.put(4, 4);    // evicts key 1
    cache.get(1);       // returns -1 (not found)
    cache.get(3);       // returns 3
    cache.get(4);       // returns 4

    system("pause");
    return 0;
}
