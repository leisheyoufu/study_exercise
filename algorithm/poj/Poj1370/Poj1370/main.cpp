#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define NOID -9999
#define NOSTOP -9999

void input();
int Gcd(int a,int b);
int getLoop();
void know(int station[],int m);
void add_know(int a[],int num);
void init_driver();
int get_driver_index( int driver_id);
void next_stop(int index);
void init_station();
bool answer();
void get_known_num();

struct Line{
	int stop[50];
	int n;
	Line()
	{
		n=0;
		for(int i=0;i<50;i++)
		{
			stop[i] = NOSTOP;
		}
	}
};

struct Driver {
	int line;
	int dirverid;
	int start;
	int know[30];
	int knownum;
	int current;

};

struct Station {
	int stop;
	int driver_id[30];
	int m;  //当前车站driver 的个数
	Station()
	{
		stop = NOSTOP;
		clear();
	}
	void clear()
	{
		for(int i=0;i<30;i++)
		{
			driver_id[i]=NOID;
		}
		m=0;
	}
	void add_id(int d_id)
	{
		for(int i=0;i<30;i++)
		{
			if( driver_id[i] ==NOID)
			{
				driver_id[i] = d_id;
				break;
			}
		}

	}
};

struct Line line[20];
struct Driver driver[30];
struct Station station[50];

int n,d,s;

int main()
{
	bool allknow = false;
	scanf("%d%d%d",&n,&d,&s);
	getchar();
	
	input();
	init_driver();
	init_station();

	int loop = getLoop();
	
	for( int time=0;time< loop;time++)
	{		
			
		for(int i=0;i<d;i++)
		{
			for(int j=0;j<s;j++)
			{
				if(driver[i].current == station[j].stop)
				{
					station[j].add_id(driver[i].dirverid);
					station[j].m++;
					
				}
			}
		}
	
		for( int p=0;p<s;p++)
		{
			know(station[p].driver_id,station[p].m);
		}
		get_known_num();
		allknow = answer();
		if(allknow == true)
		{
			printf("Yes");
			return 0;
		}
		

		for(int i=0;i<d;i++)
		{
			next_stop(i);
		}

		for(int j=0;j<s;j++)
		{
			station[j].clear();
		}
		
	}
	


	
	printf("No");
			
	getch();
	return 0;
}

bool answer()
{
	bool allknow = true;
	for(int i=0;i<d;i++)
	{
			if(driver[i].knownum < d)
			{
				allknow = false;
			}
	}
	return allknow;
}
void init_station()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<s;j++)
		{
			int stop = line[i].stop[j];
			if(stop !=NOSTOP)
			{
				for(int k = 0;k<s;k++)
				{
					if(station[k].stop == stop )
					{
						break;
					}
					if(station[k].stop ==NOSTOP)
					{
						station[k].stop = stop;
						break;
					}
				}
			}
		}
	}

}

void next_stop(int index)  //参数driver的序号
{
	int current = driver[index].current;
	int driver_line = driver[index].line;
	int i=0;
	for(i=0;i<line[driver_line].n;i++)
	{
		if( line[driver_line].stop[i] == current)
		{
			i++;
			break;
		}
	}
	if(i>= line[driver_line].n )
	{
		i=0;
	}
	current = line[driver_line].stop[i];
	driver[index].current = current;

}

void input()
{
	
		char str[80];
		int j=0;
		int i=0;
		int s=0;
		int d=0;
		
		while(  fgets(str, sizeof str, stdin),strcmp(str,"0 0 0")!= 0)
		{
			if( str[0] == '0' && str[2] == '0' && str[4] == '0')
			{
				break;
			}
			if(i%2==0)
			{
				int m=0;
				int k=0;
				char ch[10];
				j=0;
				while(str[k] !='\0')
				{
					while(str[k] !=' ' && str[k]!='\0')
					{
						ch[m] = str[k];
						m++;
						k++;
					}
					if(m!=0)
					{
						ch[m]='\0';
						line[s].stop[j] = atoi(ch);
						line[s].n++;
						m=0;
						j++;
						
					}
					if( str[k]=='\0')
					{
						break;
					}
					k++;
				}
				i++;
				s++;
			}
			else
			{
				int m=0;
				j=0;
				int k=0;
				char ch[10];
				while(str[k] !='\0')
				{

					while(str[k] !=' ' && str[k]!='\0')
					{
						ch[m] = str[k];
						m++;
						k++;
					}
					if(m!=0)
					{
						ch[m]='\0';		
						
						if(j%2 == 0)
						{
							driver[d].line = i/2;
							driver[d].start = atoi(ch);
							j++;
						}
						else
						{
							
							driver[d].dirverid = atoi(ch);
							j++;
							d++;
						}
						m=0;
					}
				
					if( str[k]=='\0')
					{
						break;
					}
					k++;


					
					
				}
				i++;
			}
			
		}

	}

int Gcd(int a,int b)
{
	int min=a;
	int max=b;
	if(a>b)
	{
		min=b;
		max =a;
	}
	while( max %min!=0)
	{
		int temp =max % min;
		min = temp;
		max = min;
	}
	return min;
}

int getLoop()
{
	int result = 1;
	for(int i=0;i<n;i++)
	{
		result *= line[i].n;
	}
	return result+1;
}

void init_driver()
{
	for(int i=0;i<d;i++)
	{
		driver[i].know[0] = driver[i].dirverid;
		driver[i].current = driver[i].start;
		driver[i].knownum = 1;
		for(int j=1;j<30;j++)
		{
			driver[i].know[j] = NOID;
		}
	}
}
void know(int station[],int m)  //station[] 是driverid  m 是在这个station的车辆个数
{
	int know[30];
	for(int i=0;i<d;i++)
	{
		know[i] = NOID;
	}

	for(int i=0;i<m;i++)
	{
		int index = get_driver_index(station[i]);
		for(int j=0;j<d;j++)
		{
			if(driver[index].know[j]!=NOID)
			{
				add_know(know,driver[index].know[j]);
			}
		}
		
	}
	for(int i=0;i<m;i++)
	{
		int index = get_driver_index(station[i]);
		for(int j=0;j<d;j++)
		{
			if(know[j]!=NOID)
			{
				add_know(driver[index].know,know[j]);
				

			}
		}
	}
}

void add_know(int a[],int num)
{
	bool exsit = false;
	int i=0;
	for(i=0;i<d;i++)
	{
		if( a[i] == num )
		{
			exsit = true;
		}
		if( a[i]==NOID)
		{
			break;
		}
	}
	if( !exsit)
	{
		a[i] = num;
	}
}

int get_driver_index( int driver_id)
{
	for(int i=0;i<d;i++)
	{
		if(driver[i].dirverid == driver_id)
		{
			return i;
		}
	}
	return -1;
}

void get_known_num()
{
	for(int i=0;i<d;i++)
	{
		for(int k=0;k<d+1;k++)
					{
						if(driver[i].know[k] ==NOID)
						{
							driver[i].knownum = k;
							break;
						}
					}
	}
}