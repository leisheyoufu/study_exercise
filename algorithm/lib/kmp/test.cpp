#include <stdio.h>
#include "kmp.h"

int main()
{
	char *t = "ABRACADABRA";
	char *p = "CAD";
	int f[80];

	int index = find(t,p,f);
	printf("Found at index %d",index);
}