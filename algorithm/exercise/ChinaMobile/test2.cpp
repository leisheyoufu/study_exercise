#include<vector>
#include<iostream>

using namespace std;

int getTotal(vector<int> marks)
{
    int n = marks.size();
    if(n==0) {
        return 0;
    }
    vector<int> a(n, 1);
    for(int i=1; i<n; i++) {
        if(marks[i] > marks[i-1]) {
            a[i] = a[i-1] + 1;
        }
    }
    for(int i=n-1; i>0; i--) {
        if(marks[i-1] > marks[i]) {
            a[i-1] = a[i] + 1;
        }
    }
    int ret = 0;
    for(int i=0; i<n; i++) {
        ret +=a[i];
    }
    return ret;
}

vector<int> getMarks(string s)
{
    vector<int> marks;
    int n = s.length();
    if(n == 0) {
        return marks;
    }
    int val = 0;
    for(int i=0; i<n; i++) {
        if(s[i] >= '0' && s[i] <='9') {
            val = 10 *val + s[i] - '0';
        } else if(s[i] == ',') {
            marks.push_back(val);
            val = 0;
        }
    }
    marks.push_back(val);
    return marks;
}

int main()
{
    string s;
    cin >> s;
    vector<int> marks = getMarks(s);
    cout << getTotal(marks) << endl;
    return 0;
}