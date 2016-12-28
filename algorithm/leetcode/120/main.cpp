#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

using namespace std;

class Solution
{
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		if(triangle.empty()) {
			return 0;
		}
		if(triangle[0].empty()) {
			return 0;
		}
		int m = triangle.size();
		int *d = new int[m];
		for(int j=0;j<triangle[m-1].size();j++) {
			d[j] = triangle[m-1][j];
		}
		for(int i=m-2;i>=0;i--) {
			int temp = 0;
			int last;
			for(int j=triangle[i].size()-1;j>=0;j--) {				
				temp = triangle[i][j] + min(d[j], d[j+1]);
				if(j!=triangle[i].size()-1) {
					d[j+1] = last;					
				}
				last = temp;
			}
			d[0] = temp;
		}
		return d[0];
    }
};

int main()
{	
	Solution sln;
	int a[] = {-1};
	int b[] = {2,3};
	int c[] = {1,-1,-1};
	vector<vector<int>> v;
	vector<int> v1(a,a+1);
	vector<int> v2(b,b+2);
	vector<int> v3(c,c+3);

	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	cout << sln.minimumTotal(v) << endl;
    system("pause");
    return 0;
}