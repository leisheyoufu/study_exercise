#include<vector>
#include<iostream>

using namespace std;

vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int getDay(int year, int month, int day)
{
    if(month <=0 || month > 12) {
        throw new exception();
    }
    // year < 0 ?
    if((year % 100 != 0 && year % 4 == 0) || (year % 100 == 0 && year % 400 == 0)) {
        months[1] = 29;
    }
    if(day > months[month-1] || day <=0) {
        throw new exception();
    }
    int ret = day;
    for(int i=0; i<month -1; i++) {
        ret += months[i];
    }
    return ret;
}

int main()
{
    int year, month, day;
    cin >> year >> month >> day;
    cout << getDay(year, month, day) << endl;
    return 0;
}