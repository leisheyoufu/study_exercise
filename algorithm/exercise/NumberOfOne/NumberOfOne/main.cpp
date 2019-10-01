#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

int GetNumberOneBit1(int num);
int GetAllNumberOne1(int to);

int GetNumberBit(int num,int *first);
int GetAllNumberOne2(int num);




int main()
{
    int n = GetAllNumberOne1(6280);
    printf("old algorithm %d\n",n);

    n = GetAllNumberOne2(6280);
    printf("new algorithm %d\n",n);

    getch();
    return 0;
}

int GetAllNumberOne2(int num)
{
    int count  =0;
    int factor = 1;
    int cur_num = 0;
    int high_num = 0;
    int low_num = 0;

    while(num/factor !=0) {
        low_num = num %factor;
        high_num = num / factor /10;
        cur_num = num /factor%factor;
        if(high_num == 0) {
            cur_num = num /factor;
        }
        switch(cur_num) {
        case 1:
            count +=high_num *factor+(low_num+1);

            break;
        case 0:
            count +=high_num*factor;
            break;
        default:
            count +=(high_num+1)*factor;

        }

        factor*=10;
    }
    return count;
}

/*  数组指针
int GetNumberBit(int num,int **first)
{
	int m=0;
	int temp = num;
	while(num !=0)
	{

		num/=10;
		m++;
	}
	*first = (int*)malloc(sizeof(int)*m);  //*first 是指向 int类型数组的指针  不是指针数组

	int i=0;
	while(temp !=0)
	{
		(*first)[i++] = temp%10;

		temp/=10;
	}
	return m;
}
*/
/* 算法错误  但数组指针的运用成功  */
/*
int GetAllNumberOne2(int num)
{
	int *first;
	int m=0;
	int len = GetNumberBit(num,&first);
	for(int i=0;i<len;i++)
	{
		if(first[len -i -1]>1)
		{
			int temp =1;

			for(int j=0;j<len;j++)
			{
				if(j<i)
				{
					if( i-j==1)
					{
						temp*=(first[len-j-1]+1);
					}
					else
					{
						temp= temp *first[len-j-i]*10;
					}

				}
				if(j>i)
				{
					temp *=10;
				}
			}
			m+=temp;
		}
		else if(first[len -i -1]==1)
		{
			int temp = 0;
			for(int j=0;j<len;j++)
			{
				double f = 0;
				if(j!=i)
				{
					//double f = pow((double)2,3);
					//temp+=*first[j]*pow(((double)10,(double)2);
						//pow(((double)10,(double)(len-j-1));

					if( i-j <= 1)
					{
						f =(first[len-j-1]+1)*pow((double)10,(len-j-1));
					}
					else
					{
						f = first[len-j-1]*pow((double)10,(len-j-1));
						if(j==len -1)
						{
							f+=1;
						}
					}
					temp +=(int)f;
				}
			}
			m+=temp;
		}

		else if(first[len - i -1] == 0)
		{
			int temp = 0;
			for(int j=0;j<len;j++)
			{
				if(i!=j)
				{
					double f = 0;
					if( i-j == 1)
					{
						f =(first[len-j-1]+1)*pow((double)10,(len-j-1 -1));
					}
					else
					{
						f = first[len-j-1]*pow((double)10,(len-j-1-1));

					}
					temp +=(int)f;
				}

			}
			m+=temp;
		}

	}
	return m;

}
*/



int GetNumberOneBit1(int num)
{
    int m =0;
    while(num !=0) {
        if(num % 10 == 1) {
            m++;
        }
        num /=10;

    }
    return m;
}

int GetAllNumberOne1(int to)
{
    int all = 0;
    for(int i=1; i<=to; i++) {
        all += GetNumberOneBit1(i);
    }
    return all;
}