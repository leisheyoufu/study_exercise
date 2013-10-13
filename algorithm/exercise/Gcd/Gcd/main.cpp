#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//#define print(x) printf(＂the no, ＂#x\n＂,is ＂) 

#define print(x) printf("%x\n",x)

void getmemory(char **p, int num) 
{ *p=(char *) malloc(num);} 
void test(void) 
{ char *str=NULL; 
getmemory(&str,100); 
strcpy(str,"hello"); 
printf(str); 
} 




int GetGCD(int a,int b);
int main()
{
	char str1[] = "hello";
	char *str2 = "hello";
	printf("sizeof str1 %d\n",sizeof(str1));
	printf("sizeof str2 %d\n",sizeof(str2));

	printf("%d\n",GetGCD(101,20));
	print(100);
	test();

	int arr[]={6,7,8,9,10}; 
	int *ptr=arr; 
	*(ptr++)+=123; 
	printf("%d,%d\n",*ptr,*(++ptr));  //8,8

	printf("%d,%d\n",*ptr,*(ptr++)); //8,8

	int aptr = *(ptr++), bptr = *(ptr++);

	printf("%d,%d\n",aptr,bptr); //9,10

	getch();
	return 0;
}
// 获取最大公约数  辗转相除法
int GetGCD(int a,int b)
{
  int c = a%b;
  if(c !=0)
  {
	    return GetGCD(b,c);
  }
  return b;
}