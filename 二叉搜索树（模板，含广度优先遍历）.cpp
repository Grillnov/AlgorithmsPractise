#include<iostream>
#include<queue>
using namespace std;
template<class Type>
struct bin_Search_Node
{
	bin_Search_Node<Type>* parent;
	bin_Search_Node<Type>* left;
	bin_Search_Node<Type>* right;
	Type val;
	bin_Search_Node()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}
};
template<class Type>
class bin_Search_Tree
{
private:
	bin_Search_Node<Type>* root;
public:
	bin_Search_Tree()
	{
		root = nullptr;
	}
	void go_thru(bin_Search_Node<Type>* ptr)
	{
		if (ptr == nullptr)
			return;
		go_thru(ptr->left);
		cout << ptr->val << " ";
		go_thru(ptr->right);
	}

	void broadth_go_thru()
	{
		queue<bin_Search_Node<Type>> Queue1;
		if (this->root != nullptr)
			Queue1.push(*root);
		while (!Queue1.empty())
		{
			auto this_Obj = Queue1.front();
			cout << this_Obj.val << " ";
			Queue1.pop();
			if (this_Obj.left != nullptr)
				Queue1.push(*this_Obj.left);
			if (this_Obj.right != nullptr)
				Queue1.push(*this_Obj.right);
		}
	}

	bin_Search_Node<Type>* get_root()
	{
		return this->root;
	}
	bin_Search_Node<Type>* insert(Type val);
	bin_Search_Node<Type>* search(Type val);
	void del(bin_Search_Node<Type>* target);
	bin_Search_Node<Type>* find_Maxinum(bin_Search_Node<Type>* target);
	bin_Search_Node<Type>* find_Mininum(bin_Search_Node<Type>* target);
	void transplant(bin_Search_Node<Type>* target, bin_Search_Node<Type>* object);
};
template<class Type>
bin_Search_Node<Type>* bin_Search_Tree<Type>::insert(Type val)
{
	if (this->root == nullptr)
	{
		root = new bin_Search_Node<Type>;
		root->val = val;
		return root;
	}
	else
	{
		bin_Search_Node<Type>* empty_Slot = this->root;
		bin_Search_Node<Type>* slot_Parent = nullptr;
		while (empty_Slot != nullptr)
		{
			slot_Parent = empty_Slot;
			if (val < empty_Slot->val)
				empty_Slot = empty_Slot->left;
			else
				empty_Slot = empty_Slot->right;
		}
		empty_Slot = new bin_Search_Node<Type>;
		empty_Slot->val = val;
		if (val < slot_Parent->val)
			slot_Parent->left = empty_Slot;
		else
			slot_Parent->right = empty_Slot;
		empty_Slot->parent = slot_Parent;
		return empty_Slot;
	}
}
template<class Type>
bin_Search_Node<Type>* bin_Search_Tree<Type>::search(Type val)
{
	bin_Search_Node<Type>* temp = this->root;
	while (temp != nullptr&&temp->val != val)
	{
		if (val < temp->val)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}
template<class Type>
void bin_Search_Tree<Type>::transplant(bin_Search_Node<Type>* target, bin_Search_Node<Type>* object)
{
	if (target->parent == nullptr)
		this->root = object;
	else
	{
		if (target == target->parent->left)
			target->parent->left = object;
		else
			target->parent->right = object;
	}
	if (object != nullptr)
		target->parent = object->parent;
}
template<class Type>
bin_Search_Node<Type>* bin_Search_Tree<Type>::find_Maxinum(bin_Search_Node<Type>* target)
{
	bin_Search_Node<Type>* temp = target;
	while (temp->right != nullptr)
		temp = temp->right;
	return temp;
}
template<class Type>
bin_Search_Node<Type>* bin_Search_Tree<Type>::find_Mininum(bin_Search_Node<Type>* target)
{
	bin_Search_Node<Type>* temp = target;
	while (temp->left != nullptr)
		temp = temp->left;
	return temp;
}
template<class Type>
void bin_Search_Tree<Type>::del(bin_Search_Node<Type>* target)
{
	if (target->left == nullptr)
	{
		transplant(target, target->right);
		//delete target;
	}
	else if (target->right == nullptr)
	{
		transplant(target, target->left);
		delete target;
	}
	else
	{
		bin_Search_Node<Type>* successor = find_Mininum(target->right);
		if (successor == target->right)
		{
			transplant(target, target->right);
			delete target;
		}
		else
		{
			transplant(successor, successor->right);
			target->val = successor->val;
			delete successor;
		}

	}
}
int main()
{
	bin_Search_Tree<int> tree;
	for (int i = 0; i != 10; ++i)
	{
		int this_val = rand() % 100;
		tree.insert(this_val);
		cout << this_val << " ";
	}
	cout << endl;
	/*tree.go_thru(tree.get_root());
	tree.del(tree.search(29358));
	cout << endl;
	tree.go_thru(tree.get_root());*/
	tree.broadth_go_thru();
	getchar();
}