/*
341. Flatten Nested List Iterator
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:

Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,1,2,1,1].
Example 2:

Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,4,6].
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>

using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedInteger
{
private:
    vector<NestedInteger> nestes;
    int val;
    bool isInt;
public:
    NestedInteger(int val)
    {
        this->val = val;
        isInt = true;
    }
    NestedInteger(vector<NestedInteger> nestes)
    {
        this->nestes = nestes;
        isInt = false;
    }
    void Add(NestedInteger elem)
    {
        if(isInteger()) {
            isInt = false;
            NestedInteger curr(this->val);
            nestes.push_back(curr);
        }
        nestes.push_back(elem);
    }
    bool isInteger()
    {
        return isInt;
    }
    int getInteger() const
    {
        return val;
    }
    const vector<NestedInteger> &getList() const
    {
        return nestes;
    }
};

class NestedIterator
{
public:
    NestedIterator(vector<NestedInteger> &nestedList)
    {
        for(int i = nestedList.size()-1; i>=0; i--) {
            s.push(nestedList[i]);
        }
    }

    int next()
    {
        if(s.empty()) {
            throw;
        }
        int val;
        while(!s.empty()) {
            NestedInteger nested = s.top();
            if(nested.isInteger()) {
                val = nested.getInteger();
                s.pop();
                return val;
            }
            s.pop();
            vector<NestedInteger> nestedList = nested.getList();
            for(int i=nestedList.size()-1; i>=0; i--) {
                s.push(nestedList[i]);
            }
        }
        return val;
    }

    bool hasNext()
    {
        while(!s.empty()) {
            NestedInteger nested = s.top();
            if(nested.isInteger()) {
                return true;
            }
            s.pop();
            vector<NestedInteger> nestedList = nested.getList();
            for(int i=nestedList.size()-1; i>=0; i--) {
                s.push(nestedList[i]);
            }
        }
        return false;
    }
private:
    stack<NestedInteger> s;
};

int main()
{
    // [1,[4,[6]]]
    NestedInteger elem6(6);
    NestedInteger elem4(4);
    elem4.Add(elem6);
    NestedInteger elem1(1);
    vector<NestedInteger> nestedList = {elem1, elem4};
    NestedIterator iterator(nestedList);
    while(iterator.hasNext()) {
        cout << iterator.next() << " ";
    }
    cout << endl;  // 1 4 6
    system("pause");
    return 0;
}
