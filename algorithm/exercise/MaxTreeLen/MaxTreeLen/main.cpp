#include <stdio.h>
#include <conio.h>



struct Node {
    struct Node *left;
    struct Node *right;
    char val;
    int max_left;
    int max_right;
};

void FindMaxLen(struct Node *node,int *max_len);

int main()
{
    struct Node node1;

    struct Node node2;
    struct Node node3;
    struct Node node4;
    struct Node node5;
    struct Node node6;
    struct Node node7;
    struct Node node8;
    struct Node node9;
    node1.val =1;
    node1.max_left = 0;
    node1.max_right = 0;

    node2.val =2;
    node2.max_left = 0;
    node2.max_right = 0;

    node3.val =3;
    node3.max_left = 0;
    node3.max_right = 0;

    node4.val =4;
    node4.max_left = 0;
    node4.max_right = 0;

    node5.val =5;
    node5.max_left = 0;
    node5.max_right = 0;

    node6.val =6;
    node6.max_left = 0;
    node6.max_right = 0;

    node7.val =7;
    node7.max_left = 0;
    node7.max_right = 0;

    node8.val =8;
    node8.max_left = 0;
    node8.max_right = 0;

    node9.val =9;
    node9.max_left = 0;
    node9.max_right = 0;

    node1.left = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;

    node3.right = &node7;
    node3.left = &node6;
    node4.left = &node8;
    node6.right = &node9;

    node4.right = NULL;
    node5.left = NULL;
    node5.right = NULL;

    node6.left = NULL;
    node7.left = NULL;
    node7.right = NULL;

    node8.left = NULL;
    node8.right = NULL;

    node9.left = NULL;
    node9.right = NULL;

    int max_len = 0;

    FindMaxLen(&node1,&max_len);
    printf("max len %d\n",max_len);
    getch();
    return 0;
}

void FindMaxLen(struct Node *node,int *max_len)
{

    if(node == NULL) {
        return;
    }
    printf("%d\n",node->val);
    if(node->left== NULL) {
        node->max_left = 0;
    }
    if(node->right == NULL) {
        node->max_right = 0;
    }
    FindMaxLen(node->left,max_len);
    FindMaxLen(node->right,max_len);
    if(node->left!=NULL && node->left->max_left > node->left->max_right) {
        node->max_left = node->left->max_left +1;
    } else if(node->left!=NULL) {
        node->max_left = node->left->max_right +1;
    }

    if(node->right!=NULL &&node->right->max_left>node->right->max_right) {
        node->max_right = node->right->max_left+1;
    } else if(node->right !=NULL) {
        node->max_right = node->right->max_right+1;
    }



    if(node->max_left + node->max_right > *max_len) {
        *max_len = node->max_right+node->max_left;
    }

}