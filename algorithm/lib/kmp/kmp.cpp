#include <cstring>
#include "kmp.h"

void get_fail(char *p, int *f)
{
	int m = strlen(p);
	f[0] = 0;
	f[1] =0;
	for(int i=1;i<m;i++)
	{
		int j = f[i];
		while(j&&p[i]!=p[j])
		{
			j = f[j];
		}
		f[i+1] = p[i] == p[j] ? j+1:0;
	}
}

/*
param: t: ËÑË÷µÄ×Ö·û´®
param  p:  Ä£Ê½´®
return -1 not found
       other  index from 1
*/
int  find(char *t, char *p, int *f)
{
	int n =strlen(t);
	int m = strlen(p);
	get_fail(p,f);
	int j = 0;
	for( int i=0;i<n;i++)
	{
		while( j && p[j] != t[i] )
		{
			j = f[j];
		}
		if( p[j] == t[i] )
		{
			j++;
		}
		if( j==m )
		{
			return i-m+1;   // i-m from index 0, +1 from index 1
		}
	}
	return -1;
}
			 

