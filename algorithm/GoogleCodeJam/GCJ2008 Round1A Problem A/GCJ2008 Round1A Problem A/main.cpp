#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <map>

using namespace std;

int main()
{
ofstream fout("A-largeout.txt");
ifstream fin("A-large-practice.in");
int T,N,M,temp;
fin >> T;

for(int caseId = 1; caseId <= T; caseId++)
{
   fin >> N;
   vector<__int64> a,b;
   for(int i = 0; i < N; i++)
   {
    int temp;
    fin >> temp;
    a.push_back(temp);
   }
   for(int i = 0; i < N; i++)
   {
    int temp;
    fin >> temp;
    b.push_back(temp);
   }
   sort(a.begin(), a.end());
   sort(b.begin(), b.end());
   __int64 res = 0;
   for(int i = 0; i < N; i++)
    res += a[i] * b[N-i-1];
   fout << "Case #" << caseId << ": " << res << endl;  
}
return 0;
}
