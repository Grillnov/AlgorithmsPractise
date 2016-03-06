#include <queue>
struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution
{
public:
	TreeNode* invertTree(TreeNode* root)
	{
		std::queue<TreeNode*> Q;
		if (root != NULL)
			Q.push(root);
		while (!Q.empty())
		{
			TreeNode* Cur = Q.front();
			Q.pop();
			TreeNode* temp = Cur->left;
			Cur->left = Cur->right;
			Cur->right = temp;
			if (Cur->left != NULL)
				Q.push(Cur->left);
			if (Cur->right != NULL)
				Q.push(Cur->right);
		}
		return root;
	}
};