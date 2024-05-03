#include<map>
#include<algorithm>
#include<iostream>

using namespace std;

int main() {
    map<char, int> nums;
    nums['a'] = 10;
    nums['b'] = 20;
    nums['c'] = 30;
    nums['d'] = 40;
    nums['e'] = 50;

    map<char, int>::iterator up, low;
    low = nums.lower_bound('b');
    up = nums.upper_bound('d');
    nums.erase(low, up);
    for(map<char, int>::iterator  iter = nums.begin(); iter != nums.end(); iter++) {
        cout << (*iter).second << " ";
    }
    cout << endl;
    /*
    10 50
    */


    map<char, int> nums2;
    nums2['a'] = 10;
    nums2['b'] = 20;
    nums2['c'] = 30;
    nums2['d'] = 40;
    nums2['e'] = 50;
    low = nums2.lower_bound('b');
    up = nums2.lower_bound('d');
    nums2.erase(low, up);
    for(map<char, int>::iterator iter = nums2.begin(); iter != nums2.end(); iter++) {
        cout << (*iter).second << " ";
    }
    /*
    10 40 50 
    */
    cout << endl;
    system("pause");
}

