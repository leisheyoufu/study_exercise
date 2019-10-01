#include "SortList.h"

template<class T>
SortList<T>::SortList(int size)
{
    array= new T*[size];
    this->size = 0;

}

template<class T>
SortList<T>::~SortList(void)
{
    delete []array;
}

template<class T>
void SortList<T>::insert(T *item)
{
    int i=0;
    while(i<size &&*(this->array[i])<*item) {
        i++;
    }
    this->size++;
    for(int j=size-1; j>i; j--) {
        array[j] = array[j-1];
    }
    this->array[i]=item;

}

template<class T>
T* SortList<T>::remove(int index)
{
    T *temp = array[index];
    while(index<size-1) {
        array[index] = array[index+1];
        index++;
    }
    this->size--;
    return temp;
}

template<class T>
T* SortList<T>::front()
{
    return array[0];
}

template<class T>
T* SortList<T>::pop()
{
    return remove(0);
}

template<class T>
bool SortList<T>:: isEmpty()
{
    if(size>0)
        return false;
    return true;
}

template<class T>
bool SortList<T>:: inList(T item)
{
    for(int i=0; i<this->size; i++) {
        if(item == *array[i]) {
            return true;
        }
    }
    return false;
}

template<class T>
int SortList<T>:: getItem(T item)
{
    for(int i=0; i<this->size; i++) {
        if(*array[i]==item)
            return i;
    }
    return -1;
}