#include<set>
#include<algorithm>
#include<iostream>

using namespace std;

int main() {
    set<int> nums = {10, 20, 30, 40, 50, 60, 70, 80};

    set<int>::iterator up, low;
    low = lower_bound(nums.begin(), nums.end(), 30); // >=30 
    up = upper_bound(nums.begin(), nums.end(), 60);  // > 60
    nums.erase(low, up);
    for(set<int>::iterator  iter = nums.begin(); iter != nums.end(); iter++) {
        cout << *iter << " ";
    }
    /*
    10 20 70 80
    */
    cout << endl;

    nums = {10, 20, 30, 40, 50, 60, 70, 80};
    low = lower_bound(nums.begin(), nums.end(), 30);
    up = upper_bound(nums.begin(), nums.end(), 59);
    nums.erase(low, up);

    for(set<int>::iterator  iter = nums.begin(); iter != nums.end(); iter++) {
        cout << *iter << " ";
    }
    /*
    10 20 60 70 80
    */
    cout << endl;
    system("pause");
}

