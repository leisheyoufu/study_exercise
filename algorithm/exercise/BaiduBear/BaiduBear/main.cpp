#include <iostream>
#include <set>
#include <algorithm>
#include <conio.h>
#include <queue>

using namespace std;
struct Hurt{
	int value;
	set<int> t;

	int n;
	bool operator<(const Hurt &a)const  //ÖØÔØ<ÔËËã·û
	{
		if(this->value < a.value)
			return true;
		return false;
	}
};

struct Weapon{
	int physic;
	int magic;
};
/*
bool cmp_hurt(Hurt a,Hurt b)
{
if(a.value <=b.value)
return true;
return false;
}
*/
void printQueue( priority_queue<struct Hurt,vector<Hurt>> q)
{
	/*
	priority_queue<struct Hurt,vector<Hurt>>::iterator iter;
	for(iter = hurt.begin();iter !=hurt.end();iter++)
	{
	cout << (*iter).value << " ";
	}
	*/
	while(!q.empty())
	{
		cout << q.top().value << " ";
		q.pop();
	}

}
void printSet(set<Hurt> hurt)
{

	//sort(hurt.begin(),hurt.end());
	set<Hurt>::iterator iter;
	for(iter = hurt.begin();iter !=hurt.end();iter++)
	{
		cout << (*iter).value << " ";
	}
}
bool exsit(set<Hurt> hurt,Hurt temp)
{
	set<Hurt>::iterator iter;
	set<int>::iterator tter1;
	set<int>::iterator tter2;
	bool ex;
	for(iter = hurt.begin();iter!=hurt.end();iter++)
	{
		if((*iter).value == temp.value )
		{
			/*
			for(tter1 = (*iter).t.begin();tter1 != (*iter).t.end();tter1++ )
			{
			for(tter2 = temp.t.begin();tter2!=temp.t.end();tter2++)
			{
			if((*tter2) != (*tter1))
			ex=false;
			}
			if(ex!=false)
			{
			return true;
			}
			}
			*/
			return true;
		}
	}
	return false;
}
bool equal(set<int> a,set<int> b)
{
	set<int>::iterator aiter;
	set<int>::iterator biter;
	for(aiter = a.begin();aiter!=a.end();aiter++)
	{
		for(biter = b.begin();biter!=b.end();biter++)
		{
			if((*aiter) == (*biter))
				return true;

		}
	}
	return false;
}

void addTail(set<Hurt> &hurt,Hurt temp)
{
	set<Hurt>::iterator iter;

	iter = hurt.end();
	iter --;

	if((*iter).value>temp.value)
	{
		hurt.erase(iter);
		hurt.insert(temp);
	}
}

int main()
{
	int k=8;
	struct Weapon weapon[2]={{1,3},{3,5}};
	set<Hurt> hurt;
	// priority_queue<struct Hurt,vector<Hurt>> q;

	for(int i=1;i<=k;i++)
	{		
		for(int j=0;j<2;j++)
		{
			Hurt temp;
			temp.t.insert(i);
			temp.value = weapon[j].physic+weapon[j].magic*i;
			if(hurt.size() == k)
			{
				addTail(hurt,temp);

			}
			if(hurt.size()<k)
			{
				hurt.insert(temp);
			}


		}
	}

	bool mark = true;

	while(mark)
	{
		set<Hurt>::iterator iter1;
		set<Hurt>::iterator iterend;
		mark = false;
		set<Hurt>::iterator iter;
		for(iter = hurt.begin();iter !=hurt.end();iter++)
		{
			iter1 = iter;
			iter1++;
			iterend = hurt.end();
			iterend--;

			while(iter1 !=hurt.end())
			{
				if(iter1 == iter)
				{
					continue;
				}
				if(((*iter).value + (*iter1).value )< (*iterend).value )
				{
					if(!equal((*iter).t,(*iter1).t) )
					{
						Hurt temp;
						temp.value = (*iter).value + (*iter1).value ;
						set<int>::iterator t1;
						set<int>::iterator t2;

						for(t1=(*iter).t.begin();t1!=(*iter).t.end();t1++)
						{
							temp.t.insert(*t1);
						}
						for(t2=(*iter1).t.begin();t2!=(*iter1).t.end();t2++)
						{
							temp.t.insert(*t2);
						}
						if(!exsit(hurt,temp))
						{s
							mark = true;

							addTail(hurt,temp);
							iterend = hurt.end();
							iterend--;

						}


					}		

				}
				iter1++;
			}

		}

	}



	//	printQueue(q);

	printSet(hurt);


	getch();
	return 0;
}