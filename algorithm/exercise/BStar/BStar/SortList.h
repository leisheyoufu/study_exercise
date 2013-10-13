#pragma once
#include <stdlib.h>
template<class T>
class SortList
{
public:
	SortList(int size);
	~SortList(void);
	void insert(T *item);
	T* remove(int index);
	T* front();
	T* pop();
	bool isEmpty();
	bool inList(T item);
	int getItem(T item);
	
	T **array;
	int size;

};

