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
    int capacity;
    unordered_map<int, pair<int,list<int>::iterator>> maps;
    list<int> l;

    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }

    int get(int key)
    {
        auto iter = this->maps.find(key);
        if(iter == this->maps.end()) {
            return -1;
        }
        int value = iter->second.first;
        this->l.erase(iter->second.second);
        this->l.push_front(key);
        iter->second.second=this->l.begin();
        return value;
    }

    void put(int key, int value)
    {
        auto iter = maps.find(key);
        if(iter != this->maps.end()) {
            this->l.erase(iter->second.second);
            this->l.push_front(key);
            iter->second.second = this->l.begin();
            iter->second.first = value;
        } else {
            if(maps.size() == this->capacity) {
                maps.erase(l.back());
                this->l.pop_back();
            }
            this->l.push_front(key);
            this->maps[key] = make_pair(value,this->l.begin());
        }
    }
};

int main()
{
    LRUCache cache(10);

    system("pause");
    return 0;
}
