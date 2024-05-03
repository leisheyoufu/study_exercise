#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

int main() {
    vector<int> nums = {10, 20, 30, 10, 20, 10, 20, 30};
    sort(nums.begin(), nums.end());
    vector<int>::iterator up, low;
    low = lower_bound(nums.begin(), nums.end(), 20);
    up = upper_bound(nums.begin(), nums.end(), 20);
    cout << "lower bound of 20 at position " << low - nums.begin() << endl;
    cout << "upper bound of 20 at position " << up - nums.begin() << endl;
    system("pause");
}
/*
lower bound of 20 at position 3
upper bound of 20 at position 3
*/