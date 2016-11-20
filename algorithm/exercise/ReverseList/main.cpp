#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int val;
} Node;

void print_list(Node *head)
{
    while(head !=NULL) {
        printf("%d -->",head->val);
        head = head->next;
    }
}


void reverse(Node *head)
{
    Node *curr =head->next;
    head->next = NULL;
    while(curr != NULL) {
        Node *temp = curr->next;
        curr->next = head;
        head = curr;
        curr = temp;
    }
}

void del_node(Node **head)
{
    for(Node **curr=head; *curr;) {
        Node *entry = *curr;
        Node *temp = entry->next;
        if(entry->val ==3) {
            *curr = temp;
            //free(entry);  // not malloc node
        }
        curr = &temp->next;
    }
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
    printf("\n");
    Node *del = &n1;
    del_node(&del);
    print_list(&n1);
    reverse(&n1);
    printf("\n");
    print_list(&n6);
    getch();
    return 0;
}
