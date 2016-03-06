#include<stdio.h>
struct bin_Search_Node
{
	bin_Search_Node* parent;
	bin_Search_Node* left;
	bin_Search_Node* right;
	int val;
	bin_Search_Node()
	{
		parent = left = right = nullptr;
		val = 0;
	};
	bin_Search_Node(bin_Search_Node* p, bin_Search_Node* l, bin_Search_Node* r, int val)
	{
		this->parent = p;
		this->left = l;
		this->right = r;
		this->val = val;
	}
};
class bin_Search_Tree
{
private:
	bin_Search_Node* root;
public:
	bin_Search_Tree()
	{
		this->root = nullptr;
	}
	bin_Search_Node* insert(int val)
	{
		if (this->root == nullptr)
		{
			root = new bin_Search_Node;
			root->val = val;
			return root;
		}
		else
		{
			bin_Search_Node* position = this->root;
			bin_Search_Node* position_p = nullptr;
			while (position != nullptr)
			{
				position_p = position;
				if (val < position->val)
					position = position->left;
				else
					position = position->right;
			}
			position = new bin_Search_Node;
			position->val = val;
			position->parent = position_p;
			if (val < position_p->val)
				position_p->left = position;
			else
				position_p->right = position;
			return position;
		}
	}
	void transplant(bin_Search_Node* targ, bin_Search_Node* obj)
	{
		if (targ->parent == nullptr)
			this->root = obj;
		else if (targ == targ->parent->left)
			targ->parent->left = obj;
		else
			targ->parent->right = obj;
		if (obj != nullptr)
			obj->parent = targ->parent;
	}
	bin_Search_Node* Maxinum(bin_Search_Node* target)
	{
		while (target->right != nullptr)
			target = target->right;
		return target;
	}
	bin_Search_Node* Mininum(bin_Search_Node* target)
	{
		while (target->left != nullptr)
			target = target->left;
		return target;
	}
	void del(bin_Search_Node* target)
	{
		if (target->left == nullptr)
			transplant(target, target->right);
		else if (target->right == nullptr)
			transplant(target, target->left);
		else
		{
			bin_Search_Node* successor = Mininum(target->right);
			if (successor->parent != target)
			{
				transplant(successor, successor->right);
				successor->right = target->right;
				successor->right->parent = successor;
			}
			transplant(target, successor);
			successor->left = target->left;
			successor->right = target->right;
		};
	}
	bin_Search_Node* search(int val)
	{
		bin_Search_Node* temp = this->root;
		while (temp != nullptr&&temp->val!=val)
		{
			if (val < temp->val)
				temp = temp->left;
			else
				temp = temp->right;
		}
		return temp;
	}
};
int main()
{
	int Arr[10] = { 71, 34, 12, 16, 73, 26, 68, 52, 36, 91 };
	bin_Search_Tree tree;
	for (int i = 0; i != 10; i++)
		tree.insert(Arr[i]);
	bin_Search_Node* res = tree.search(26);
	if (res == nullptr)
		printf("%s", "not found");
	else
		printf("%d", res->val);
	tree.del(res);
	res = tree.search(26);
	if (res == nullptr)
		printf("%s", "not found");
	else
		printf("%d", res->val);
}