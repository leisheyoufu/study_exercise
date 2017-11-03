/*

599. Minimum Index Sum of Two Lists
Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. If there is a choice tie between answers, output all of them with no order requirement. You could assume there always exists an answer.

Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).
Note:
The length of both lists will be in the range of [1, 1000].
The length of strings in both lists will be in the range of [1, 30].
The index is starting from 0 to the list length minus 1.
No duplicates in both lists.


*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

class Solution
{
public:
    vector<string> findRestaurant(vector<string> &list1, vector<string> &list2)
    {
        int index_sum = INT_MAX;
        vector<int> indexs;
        vector<string> ret;
        unordered_map<string, int> maps;
        for (int i = 0; i < list1.size(); i++) {
            maps[list1[i]] = i;
        }
        for (int i = 0; i < list2.size(); i++) {
            if (maps.find(list2[i]) != maps.end()) {
                int index1 = maps[list2[i]];
                if (index1 + i < index_sum) {
                    indexs.clear();
                    indexs.push_back(index1);
                    index_sum = index1 + i;
                } else if (index1 + i == index_sum) {
                    indexs.push_back(index1);
                }
            }
        }
        if (!indexs.empty()) {
            for (int i = 0; i < indexs.size(); i++) {
                ret.push_back(list1[indexs[i]]);
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    string s1[] = {"Shogun", "Piatti", "Tapioca Express", "Burger King", "KFC"};
    string s2[] = {"Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"};
    vector<string> list1(s1, s1 + sizeof(s1) / sizeof(string));
    vector<string> list2(s2, s2 + sizeof(s2) / sizeof(string));
    vector<string> ret = sln.findRestaurant(list1, list2);
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i] << " ";
    }
    system("pause");
    return 0;
}
