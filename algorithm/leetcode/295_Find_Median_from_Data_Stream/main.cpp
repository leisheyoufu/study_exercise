/*
295. Find Median from Data Stream

Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
For example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2
Credits:
Special thanks to @Louis1992 for adding this problem and creating all test cases.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class MedianFinder
{
public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        minH.push(num);
        int n = minH.top();
        minH.pop();
        maxH.push(n);
        int len1 = maxH.size();
        int len2 = minH.size();
        if (len1 > len2) {
            n = maxH.top();
            maxH.pop();
            minH.push(n);
        }
    }

    // Returns the median of current data stream
    double findMedian()
    {
        int len1 = maxH.size();
        int len2 = minH.size();
        if (len1 == len2) {
            return (maxH.top() + minH.top()) / 2.0;
        } else {
            return len1 > len2 ? maxH.top() : minH.top();
        }
    }

private:
    priority_queue<int, vector<int>, less<int>> maxH;
    priority_queue<int, vector<int>, greater<int>> minH;
};

int main()
{
    Solution sln;
    int a[] = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> v(a, a + sizeof(a)/sizeof(int));
    cout << sln.lengthOfLIS(v) << endl; // 4
    system("pause");
    return 0;
}
