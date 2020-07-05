/*
381. Insert Delete GetRandom O(1) - Duplicates allowed

Design a data structure that supports all following operations in average O(1) time.

Note: Duplicate elements are allowed.
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
Example:

// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
collection.getRandom();
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std;

class RandomizedCollection
{
public:
    /** Initialize your data structure here. */
    RandomizedCollection()
    {

    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        hash[val].insert(vec.size());
        vec.push_back(val);
        return hash[val].size() == 1;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        if(hash[val].size() == 0) {
            return false;
        }
        int pos = *hash[val].begin();
        hash[val].erase(pos);
        if(vec.size() -1 != pos) {
            int back = vec.back();
            swap(vec[pos], vec[vec.size()-1]);
            //vec[pos] = back;
            hash[back].erase(vec.size()-1);
            hash[back].insert(pos);
        }

        vec.pop_back();
        return true;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        if (vec.size() == 0) {
            return NULL;
        }
        return vec[rand()%vec.size()];
    }
private:
    unordered_map<int, unordered_set<int> >hash;
    vector<int> vec;
};

int main()
{
    RandomizedCollection rset;
    cout << rset.insert(0) << endl;
    cout << rset.remove(0) << endl;
    cout << rset.insert(-1) << endl;
    cout << rset.insert(3) << endl;
    cout << rset.remove(0) << endl;
    cout << rset.remove(1) << endl;
    cout << rset.insert(2) << endl;
    cout << rset.getRandom() << endl;
    cout << rset.getRandom() << endl;
    cout << rset.getRandom() << endl;
    system("pause");
    return 0;
}
