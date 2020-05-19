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

struct CacheValue {
public:
    int val;
    list<int>::iterator iter;
    int freq;

    CacheValue(int val, list<int>::iterator iter, int freq)
    {
        this->val = val;
        this->iter = iter;
        this->freq = freq;
    }
    CacheValue() {

    }
};

class LFUCache {
private:
    unordered_map<int, CacheValue> m;  
    unordered_map<int, list<int>> freqs;  // freq, list<key>
    int minFreq;
    int cap;
    int size;
public:
    LFUCache(int capacity) {
        cap = capacity;
        size = 0;
        minFreq = 0;
    }
    
    int get(int key) {
        if(m.find(key) == m.end()) {
            return -1;
        }
        CacheValue v = m[key];
        freqs[v.freq].erase(v.iter);
        v.freq++;
        freqs[v.freq].push_back(key);
        v.iter = --freqs[v.freq].end();
        if(freqs[minFreq].size() == 0) {
            minFreq++;
        }
        m[key] = v;
        return v.val;
    }
    
    void put(int key, int value) {
        if(cap <= 0) {
            return;
        } 
        // if(m.find(key) != m.end()) {
        //     m[key].val = value;
        //     return;
        // }
        if(get(key) != -1) {
            m[key].val = value;
            return;
        }
        if(size == cap) {
            int key = freqs[minFreq].front();
            freqs[minFreq].pop_front();
            m.erase(key);
            size--;
        }
        freqs[1].push_back(key);
        m[key] = CacheValue(value, --freqs[1].end(), 1);
        minFreq = 1;
        size++;
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
