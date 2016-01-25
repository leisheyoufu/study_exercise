#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

#define DEFAULT_SIZE	50

class Stack
{
    int *a;
    int size;

public:
    Stack(int size);
    ~Stack();
    int top;
    bool Stack::push(int val);
    bool Stack::pop(int &val);
    bool Stack::topValue(int &val);
};

Stack::Stack(int sz= DEFAULT_SIZE)
{
    top = 0;
    size = sz;
    a = new int[size];
}
Stack::~Stack()
{
    delete []a;
}
bool Stack::push(int val)
{
    if (top ==size)
        return false;
    a[top++] = val;
    return true;
}
bool Stack::pop(int &val)
{
    if (top == 0 )
        return false;
    val = a[--top];
    return true;
}
bool Stack::topValue(int &val)
{
    if( top == 0)
        return false;
    val = a[top-1];
    return true;
}
int temp[1000];
int main()
{
    int num;
    freopen("test.txt","r",stdin);
    while( scanf("%d", &num)!= EOF) {
        bool flag = false;
        Stack s;
        int i=0;
        int top_val, t;
        for(i=0; i<num; i++) {
            scanf("%d", &temp[i]);
        }
        i=0;
        int j=1;
        s.push(j);
        while(i<num && j<=num) {
            if(s.topValue(top_val) && top_val== temp[i]) {
                s.pop(top_val);
                i++;
            } else {
                s.push(++j);
            }
        }
        if( j <=num)
            flag = true;
        if( flag)
            printf("%s\n", "Yes");
        else
            printf("%s\n", "No");
    }
    return 0;
}
