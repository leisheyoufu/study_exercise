/*
332. Reconstruct Itinerary
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:

If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
One must use all the tickets once and only once.
Example 1:

Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
Example 2:

Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
             But it is larger in lexical order.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<queue>
#include<stack>

using namespace std;

class Solution
{
public:
    vector<string> findItinerary(vector<vector<string>>& tickets)
    {
        vector<string> ret;
        if(tickets.size() == 0 || tickets[0].size() != 2) {
            return ret;
        }
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> m;
        for(auto ticket : tickets) {
            m[ticket[0]].push(ticket[1]);
        }
        stack<string> s;
        s.push("JFK");
        while(!s.empty()) {
            string from = s.top();
            if(m[from].empty()) {
                ret.push_back(from);
                s.pop();
            } else {
                string to = m[from].top();
                m[from].pop();
                s.push(to);
            }
        }
        return {ret.rbegin(), ret.rend()};
    }
};

void print(vector<string> tickets)
{
    for(string ticket : tickets) {
        cout << ticket << " ";
    }
    cout << endl;
}

int main()
{
    Solution sln;
    vector<vector<string>> tickets = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    vector<string> v = sln.findItinerary(tickets);
    print(v); // "JFK", "MUC", "LHR", "SFO", "SJC"
    tickets = {{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}};
    v = sln.findItinerary(tickets);
    print(v); // "JFK","ATL","JFK","SFO","ATL","SFO"
    tickets = {{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}};
    v = sln.findItinerary(tickets);
    print(v); // ["JFK","NRT","JFK","KUL"]
    system("pause");
    return 0;
}
