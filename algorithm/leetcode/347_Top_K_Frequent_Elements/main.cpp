/*
347. Top K Frequent Elements

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note:
You may assume k is always valid, 1 ¡Ü k ¡Ü number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include <functional>
#include<queue>

using namespace std;

class Solution
{
public:

    vector<int> topKFrequent(vector<int>& nums, int k)
    {
        int n = nums.size();
        vector<int> freqs;
        vector<int> ret;
        unordered_map<int, int> maps;
        for(int i=0; i<n; i++) {
            int num = nums[i];
            if(maps.find(num) == maps.end()) {
                maps[num] = 1;
            } else {
                maps[num] ++;
            }
        }
        for(unordered_map<int,int>::iterator iter=maps.begin(); iter !=maps.end(); iter++) {
            freqs.push_back(iter->second);
        }
        vector<int> heap(k, 0);
        for(int i=0; i<k; i++) {
            heap[i] = freqs[i];
        }
        make_heap(heap.begin(), heap.end(),greater<int>());
        int heap_size = heap.size();
        for(int i=k; i<freqs.size(); i++) {
            if(heap[0] < freqs[i]) {
                pop_heap(heap.begin(),heap.end(), greater<int>());
                heap[heap_size-1] = freqs[i];
                push_heap(heap.begin(), heap.end(), greater<int>());
            }
        }
        for(unordered_map<int,int>::iterator iter=maps.begin(); iter !=maps.end(); iter++) {
            if(iter->second >= heap[0]) {
                ret.push_back(iter->first);
            }
        }
        return ret;
    }

    // chenglch priority_queue is slower than heap
    /*
    vector<int> topKFrequent(vector<int>& nums, int k)
    {
    	int n = nums.size();
    	vector<int> freqs;
    	vector<int> ret;
    	unordered_map<int, int> maps;
    	priority_queue<int,vector<int>, greater<int>> q;
        for(int i=0; i<n; i++) {
    		int num = nums[i];
    		if(maps.find(num) == maps.end()) {
    			maps[num] = 1;
    		} else {
    			maps[num] ++;
    		}
    	}
    	for(unordered_map<int,int>::iterator iter=maps.begin(); iter !=maps.end(); iter++) {
    		freqs.push_back(iter->second);
    	}
    	for(int i=0; i<k; i++) {
    		q.push(freqs[i]);
    	}
    	for(int i=k; i<freqs.size();i++) {
    		if(q.top() < freqs[i]) {
    			q.pop();
    			q.push(freqs[i]);
    		}
    	}
    	for(unordered_map<int,int>::iterator iter=maps.begin(); iter !=maps.end(); iter++) {
    		if(iter->second >= q.top()) {
    			ret.push_back(iter->first);
    		}
    	}
    	return ret;
    }
    */
};
int main()
{
    Solution sln;
    int a[] = {1,1,1,2,2,3,3,4,4};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    sln.topKFrequent(v, 2);
    system("pause");
    return 0;
}
