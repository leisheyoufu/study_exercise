/*
380. Insert Delete GetRandom O(1)

Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
Example:

// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;

class RandomizedSet
{
public:
    /** Initialize your data structure here. */
    RandomizedSet()
    {

    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        if(hash.find(val) != hash.end()) {
            return false;
        }
        hash[val] = vec.size();
        vec.push_back(val);
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        if(hash.find(val) == hash.end()) {
            return false;
        }
        int pos = hash[val];
        hash[vec.back()] = pos;
        swap(vec[pos], vec[vec.size()-1]);
        hash.erase(val);
        vec.pop_back();
        return true;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        return vec[rand()%vec.size()];
    }
private:
    unordered_map<int, int> hash;
    vector<int> vec;
};

int main()
{
    RandomizedSet rset;
    cout << rset.insert(1) << endl;
    cout << rset.remove(2) << endl;
    cout << rset.insert(3) << endl;
    cout << rset.getRandom() << endl;
    cout << rset.getRandom() << endl;
    cout << rset.getRandom() << endl;
    system("pause");
    return 0;
}
