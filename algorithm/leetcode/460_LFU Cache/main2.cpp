/*

460. LFU Cache

Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Note that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted. This number is set to zero when the item is removed.

 

Follow up:
Could you do both operations in O(1) time complexity?

 

Example:

LFUCache cache = new LFUCache( 2  //capacity );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<list>
#include<unordered_map>

using namespace std;

struct CacheItem {
public:
    int value;
    list<int>::iterator iter;
    int freq;
    CacheItem(int value, list<int>::iterator iter, int freq) {
        this->value = value;
        this->iter = iter;
        this->freq = freq;
    }
    CacheItem(){}
};

class LFUCache {
    private:
    unordered_map<int, CacheItem> cache;
    unordered_map<int, list<int>> freqs;
    int size;
    int cap;
    int minFreq;

public:
    LFUCache(int capacity) {
        cap = capacity;
        size = 0;
        minFreq = 0;
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        CacheItem item = cache[key];
        freqs[item.freq].erase(item.iter);
        if (freqs[minFreq].size() == 0) {
            minFreq ++;
        }
        item.freq++;
        freqs[item.freq].push_back(key);
        item.iter = --freqs[item.freq].end();
        cache[key] = item;
        return item.value;
    }
    
    void put(int key, int value) {
        if(cap <= 0) {
            return;
        }
        if(get(key) != -1) {
            cache[key].value = value;
            return;
        }
        if(size == cap) {
            int tempKey = freqs[minFreq].front();
            cache.erase(tempKey);
            freqs[minFreq].pop_front();
            size --;
        }
        freqs[1].push_back(key);
        CacheItem item = CacheItem(value, --freqs[1].end(), 1);
        cache[key] = item;
        minFreq = 1;
        size ++;
    }
};

int main()
{
    LFUCache cache = LFUCache( 2 /* capacity */ );
    
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;     // returns 1
    cache.put(3, 3);    // evicts key 2
    cout << cache.get(2) << endl;    // returns -1 (not found)
    cout << cache.get(3) << endl;    // returns 3.
    cache.put(4, 4);    // evicts key 1.
    cout << cache.get(1) << endl;     // returns -1 (not found)
    cout << cache.get(3) << endl;   // returns 3
    cout << cache.get(4) << endl;    // returns 4
    
   /*
    cache.put(2,1);
    cache.put(1,1);
    cache.put(2,3);
    cache.put(4,1);
    cout << cache.get(1) << endl;    // returns -1
    cout << cache.get(2) << endl;    // returns 3
    */
    system("pause");
    return 0;
}
