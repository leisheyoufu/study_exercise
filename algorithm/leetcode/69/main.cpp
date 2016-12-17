#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;


class Solution
{
public:
	int mySqrt(int x) {
		unsigned long long begin = 0;
		unsigned long long end = (x+1)/2;
		unsigned long long mid = begin + (end -begin)/2;
		while(begin <= end) {
			mid = begin + (end -begin)/2;
			unsigned long long value = mid*mid;
			if( value == x) {
				break;
			} else if (value >x) {
				end = mid-1;
			} else if (value < x) {
				begin = mid +1;
			}
		}
		if(mid*mid > x) {
			mid--;
		}
		return (int)mid;
    }
};

int main()
{	
	Solution sln;
	cout << sln.mySqrt(3) << endl;
    system("pause");
    return 0;
}