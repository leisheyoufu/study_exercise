#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution
{
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> ret;
		if(!root) {
			return ret;
		}
		queue<TreeNode*> queue;
		queue.push(root);
		int last = 1;
		int curr = 0;
		int level = 1;
		vector<int> line;
		stack<int> stack;
		while(!queue.empty()) {			
			TreeNode *node = queue.front();
			queue.pop();
			if(node->left) {
				queue.push(node->left);
				curr++;
			}
			if(node->right) {
				queue.push(node->right);
				curr++;
			}
			if(level %2 == 1) {
				line.push_back(node->val);
			} else {
				stack.push(node->val);
			}
			last --;
			if(!last) {
				if(level %2 == 1) {
					ret.push_back(line);
					line.clear();
				} else {
					vector<int> temp;
					while(!stack.empty()) {
						int val = stack.top();
						temp.push_back(val);
						stack.pop();
					}
					ret.push_back(temp);
				}
				last = curr;
				curr = 0;
				level++;
			}
		}
		return ret;
    }
};

int main()
{	
	Solution sln;
    system("pause");
    return 0;
}