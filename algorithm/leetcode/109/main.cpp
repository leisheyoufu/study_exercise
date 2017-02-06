/*

Convert Sorted List to Binary Search Tree
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

Subscribe to see which companies asked this question.
*/
class Solution
{
public:
    TreeNode *build(ListNode *&node, int start, int end)
    {
        if(start > end) {
            return NULL;
        }
        int mid = (start + end) /2;
        TreeNode * left = build(node, start,mid -1);
        TreeNode *root = new TreeNode(node->val);
        root->left = left;
        node = node->next;
        TreeNode * right = build(node, mid+1, end);
        root->right = right;
        return root;
    }
    TreeNode* sortedListToBST(ListNode* head)
    {
        ListNode *curr = head;
        int len = 0;
        while(curr) {
            curr = curr->next;
            len ++;
        }
        return build(head, 0, len-1);
    }
};
