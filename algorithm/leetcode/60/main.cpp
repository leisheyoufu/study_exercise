#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    /*
    void next(int *d, int n)
    {
    	int i= n-1;
    	for(; i>=1;i--) {
    		if(d[i] > d[i-1]) {
    			break;
    		}
    	}
    	if (i== 0 ) {
    		reverse(&d[0],&d[n]);
    	}
    	int k = i-1;
    	for(i=n-1; i>k;i--) {
    		if(d[i] > d[k]) {
    			swap(d[i], d[k]);
    			break;
    		}
    	}
    	reverse(&d[k+1], &d[n]);
    }
    string getPermutation(int n, int k) {
    	int *d = new int[n];
    	for(int i=0;i<n;i++) {
    		d[i] = i+1;
    	}
    	int c=1;
    	while(c<k) {
    		next(d, n);
    		c++;
    	}
    	string str(n, 0);
    	for(int i=0;i<n;i++) {
    		str[i] = d[i] +'0';
    	}
    	return str;
    }
    */
    int fac(int n)
    {
        int num = 1;
        for(int i=1; i<=n; i++) {
            num *=i;
        }
        return num;
    }
    string getPermutation(int n, int k)
    {
        string ret;
        int v[9];
        //k = k% fac(n);
        for(int i=0; i<n; i++) {
            int count = fac(n-i-1);
            int ind = (k-1)/ count;
            k -= ind*count;
            int p = 0;
            for(int j=0; j<n; j++) {
                if(v[j] != true) {
                    p++;
                    if(p == ind+1) {
                        v[j] = true;
                        ret += j+1 +'0';
                        break;
                    }
                }
            }
        }
        return ret;
    }

};
int main()
{
    Solution sln;
    cout << sln.getPermutation(1,1);
    system("pause");
    return 0;
}
