#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct node {
	struct node *next;
	int val;
} Node;

void print_list(Node *head)
{
	while(head !=NULL)
	{
		printf("%d -->",head->val);
		head = head->next;
	}
}


void invert_list(Node *head)
{
	Node *n_head = head->next;
	Node *curr=  head;
	curr->next = NULL;
	Node *tmp;
	while((tmp = n_head->next)!=NULL)
	{		
		n_head->next = curr;
		curr=n_head;
		n_head = tmp;
	}
	n_head->next = curr;
	head = n_head;

	
}


int main()
{
	Node n1,n2,n3,n4,n5,n6;
	n1.val =1;
	n1.next=&n2;
	n2.val =2;
	n2.next=&n3;
	n3.val =3;
	n3.next=&n4;
	n4.val =4;
	n4.next=&n5;
	n5.val =5;
	n5.next=&n6;
	n6.val =6;
	n6.next=NULL;

	print_list(&n1);
	invert_list(&n1);
	printf("\n");
		print_list(&n6);

	

	
	getch();
	return 0;
}