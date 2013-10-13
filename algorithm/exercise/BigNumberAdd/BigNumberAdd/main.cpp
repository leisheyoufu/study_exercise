#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int CharToInt(char *str,int start,int end);
void IntToChar(char *str,int start,int end,int num);
char *BigAdd1(char *str1,char *str2);

char *BigAdd2(char *str1,char *str2);

int main()
{
	//char *result = BigAdd1("99999234","898973748374321");
//	int num = CharToInt("987",0,0);
//	char str[4];
//	IntToChar(str,0,3,8970);
	char *result = BigAdd1("99999234","898973748374321");
	printf("result1 %s\n",result);
	result = BigAdd2("1","1");
	printf("result2 %s\n",result);
	getch();
	return 0;
}

char *BigAdd1(char *str1,char *str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int max = len1;
	if(len2>max)
	{
		max = len2;
	}
	char *result = (char*)malloc(max+2);
	int temp = max+1;
	
	int a;
	int b;
	int c = 0;
	while(len1 != 0 || len2 !=0 )
	{
		if(len1 >0)
		{
			len1--;
			a = *(str1+len1)-'0';
		}
		else
		{
			a=0;
		}
		if(len2 >0)
		{
			len2--;
			b = *(str2+len2)-'0';
		}
		else
		{
			b=0;
		}
		temp--;
		
	
		*(result+temp) = (a+b+c)%10 +'0';
		if(a+b+c>=10)
		{
			c=1;
		}
		else
		{
			c=0;
		}


	}
	if(c>0)
	{
		*result = c+'0';
		temp --;
	}
	*(result+max+1) = '\0';
	return result+temp;  //temp 为1 浪费内存 且无法释放
}

char *BigAdd2(char *str1,char *str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int a,b;
	int c =0;
	int num =0;
	
	int max = len1;
	if(len2>max)
	{
		max = len2;
	}
	int temp = max;
	char *result = (char*)malloc(max+2);
	while(len1 >0 || len2 >0)
	{
		if(len1 >0)
		{
			if(len1 -4 >0)
			{
				a = CharToInt(str1,len1-4,len1-1);
				len1-=4;
			}
			else
			{
				a= CharToInt(str1,0,len1-1);
				len1-=4;
			}		
		}
		else
		{
			a=0;
		}

		if(len2>0)
		{
			if(len2-4>0)
			{
				b = CharToInt(str2,len2-4,len2-1);
				len2-=4;
			}
			else
			{
				b= CharToInt(str2,0,len2-1);
				len2-=4;
			}
		}
		else
		{
			b=0;
		}
		num = a+b+c;
		if(num >=10000)
		{
			c=1;
		}
		else
		{
			c=0;
		}
		IntToChar(result,temp-3,temp,num);
		temp -=4;
	}
	
		*result = c+'0';
	//	temp --;
	
	*(result+max+1) = '\0';
	return result;
}

void IntToChar(char *str,int start,int end,int num)  //end 是数字最后1位
{
	if(start<1)
	{
		start =1;
	}
	for(int i=end;i>=start;i--)
	{
		*(str+i) = num%10 +'0';
		num/=10;
	}
	//*(str+end+1) = '\0';
}


int CharToInt(char *str,int start,int end)  //start 从0开始
{
	int result = 0;	
	while(start <=end)
	{
		result +=*(str+start)-'0';
		if(start !=end)
		{
			result*=10;
		}
		start++;
	}
	return result;
}