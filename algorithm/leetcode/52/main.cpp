#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

class Solution
{
public:
	bool valid(int a[], int k)
	{
		int last_item = a[k];
		for(int i=0;i<k;i++) {
			if(last_item == a[i]) {
				return false;
			}
			if( abs(last_item - a[i]) == abs(k-i)) {
				return false;
			}
		}
		return true;
	}
			
	void backtrack(int a[], int k, int n, int& total)
	{
		if (k==n) {
			total++;
			return;
		}
		for(int i=0;i<n;i++) {
			a[k] = i;
			if(valid(a, k)) {
				backtrack(a, k+1, n, total);
			}
		}
	}
	int totalNQueens(int n) {
        int *a = new int[n];
		int total = 0;
		backtrack(a, 0, n, total);
		delete [] a;
		return total;
    }
};
int main()
{
	Solution sln;	
	cout << sln.totalNQueens(7) << endl;
    system("pause");
    return 0;
}