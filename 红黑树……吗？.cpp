#include <iostream>
#include <fstream>
#include <queue>
char red = 1;
char black = 0;
using namespace std;
template<typename keyType>
struct rb_Tree_Node
{
	rb_Tree_Node<keyType>* parent;
	rb_Tree_Node<keyType>* left;
	rb_Tree_Node<keyType>* right;
	char color_Bit;
	keyType key;
	rb_Tree_Node()
	{
		this->parent = this->left = this->right = nullptr;
		this->color_Bit = black;
	}
};
template<typename keyType>
class rb_Tree
{
private:
	rb_Tree_Node<keyType>* NIL;
	rb_Tree_Node<keyType>* root;
public:
	rb_Tree()
	{
		this->NIL = new rb_Tree_Node<keyType>;
		this->root = NIL;
		NIL->color_Bit = black;
		NIL->key = -1;
		NIL->left = NIL;
		NIL->right = NIL;
	}
	void insert(keyType val)
	{
		rb_Tree_Node<keyType>* slot_Parent = this->NIL;
		rb_Tree_Node<keyType>* slot = this->root;
		while (slot != this->NIL)
		{
			slot_Parent = slot;
			if (val < slot->key)
				slot = slot->left;
			else
				slot = slot->right;
		}
		slot = new rb_Tree_Node<keyType>;
		slot->key = val;
		slot->color_Bit = red;
		slot->left = slot->right = this->NIL;
		slot->parent = slot_Parent;
		if (slot_Parent == this->NIL)
			this->root = slot;
		else if (val < slot_Parent->key)
			slot_Parent->left = slot;
		else
			slot_Parent->right = slot;
		rb_insertion_Fixup(slot);
	}
	void rotate_left(rb_Tree_Node<keyType>* target)
	{
		rb_Tree_Node<keyType>* obj = target->right;
		target->right = obj->left;
		if (obj->left != this->NIL)
			obj->left->parent = target;
		obj->parent = target->parent;
		if (target->parent == this->NIL)
			this->root = obj;
		else if (target == target->parent->left)
			target->parent->left = obj;
		else
			target->parent->right = obj;
		obj->left = target;
		target->parent = obj;
	}
	void rotate_right(rb_Tree_Node<keyType>* target)
	{
		rb_Tree_Node<keyType>* obj = target->left;
		target->left = obj->right;
		if (obj->right != this->NIL)
			obj->right->parent = target;
		obj->parent = target->parent;
		if (target->parent == this->NIL)
			this->root = obj;
		else if (target == target->parent->left)
			target->parent->left = obj;
		else
			target->parent->right = obj;
		obj->right = target;
		target->parent = obj;
	}
	void rb_insertion_Fixup(rb_Tree_Node<keyType>* target)
	{
		while (target->parent->color_Bit == red)
		{
			if (target->parent == target->parent->parent->left)
			{
				rb_Tree_Node<keyType>* uncle = target->parent->parent->right;
				if (uncle->color_Bit == red)
				{
					target->parent->color_Bit = black;
					uncle->color_Bit = black;
					target->parent->parent->color_Bit = red;
					target = target->parent->parent;
				}
				else 
				{
					if (target == target->parent->right)
					{
						target = target->parent;
						rotate_left(target);
					}
					target->parent->color_Bit = black;
					target->parent->parent->color_Bit = red;
					rotate_right(target->parent->parent);
				}
			}
			else
			{
				rb_Tree_Node<keyType>* uncle = target->parent->parent->left;
				if (uncle->color_Bit == red)
				{
					target->parent->color_Bit = black;
					uncle->color_Bit = black;
					target->parent->parent->color_Bit = red;
					target = target->parent->parent;
				}
				else
				{
					if (target == target->parent->left)
					{
						target = target->parent;
						rotate_right(target);
					}
					target->parent->color_Bit = black;
					target->parent->parent->color_Bit = red;
					rotate_left(target->parent->parent);
				}
			}
		}
		this->root->color_Bit = black;
	}
	rb_Tree_Node<keyType>* find_Mininum(rb_Tree_Node<keyType>* target)
	{
		rb_Tree_Node<keyType>* seeker = target;
		rb_Tree_Node<keyType>* seeker_Parent = this->NIL;
		while (seeker != this->NIL)
		{
			seeker_Parent = seeker;
			seeker = seeker->left;
		}
		return seeker_Parent;
	}
	rb_Tree_Node<keyType>* find_Maxinum(rb_Tree_Node<keyType>* target)
	{
		rb_Tree_Node<keyType>* seeker = target;
		rb_Tree_Node<keyType>* seeker_Parent = this->NIL;
		while (seeker != this->NIL)
		{
			seeker_Parent = seeker;
			seeker = seeker->right;
		}
		return seeker_Parent;
	}
	void rb_del_Fixup(rb_Tree_Node<keyType>* x)
	{
		while (x != this->root&&x->color_Bit == black)
		{
			if (x == x->parent->left)
			{
				rb_Tree_Node<keyType>* w = x->parent->right;
				if (w->color_Bit == red)
				{
					w->color_Bit = black;
					x->parent->color_Bit = red;
					rotate_left(x->parent);
					w = x->parent->right;
				}
				if (w->left->color_Bit == black&&w->right->color_Bit == black)
				{
					w->color_Bit = red;
					x = x->parent;
				}
				else
				{
					if (w->right->color_Bit == black)
					{
						w->left->color_Bit = black;
						w->color_Bit = red;
						rotate_right(w);
						w = x->parent->right;
					}
					w->color_Bit = x->parent->color_Bit;
					x->parent->color_Bit = black;
					w->right->color_Bit = black;
					rotate_left(x->parent);
					x = this->root;
				}
			}
			else
			{
				rb_Tree_Node<keyType>* w = x->parent->left;
				if (w->color_Bit == red)
				{
					w->color_Bit = black;
					x->parent->color_Bit = red;
					rotate_right(x->parent);
					w = x->parent->left;
				}
				if (w->right->color_Bit == black&&w->left->color_Bit == black)
				{
					w->color_Bit = red;
					x = x->parent;
				}
				else
				{
					if (w->left->color_Bit == black)
					{
						w->right->color_Bit = black;
						w->color_Bit = red;
						rotate_left(w);
						w = x->parent->right;
					}
					w->color_Bit = x->parent->color_Bit;
					x->parent->color_Bit = black;
					w->right->color_Bit = black;
					rotate_right(x->parent);
					x = this->root;
				}
			}
		}
	}
	void rb_Transplant(rb_Tree_Node<keyType>* target, rb_Tree_Node<keyType>* obj)
	{
		if (this->root == target)
			this->root = obj;
		else if (target == target->parent->left)
			target->parent->left = obj;
		else
			target->parent->right = obj;
		obj->parent = target->parent;
	}

	void del(rb_Tree_Node<keyType>* target)
	{
		rb_Tree_Node<keyType>* y = target;
		rb_Tree_Node<keyType>* x = nullptr;
		char y_Original_Color = y->color_Bit;
		if (target->left == this->NIL)
		{
			x = target->right;
			rb_Transplant(target, target->right);
		}
		else if (target->right == this->NIL)
		{
			x = target->left;
			rb_Transplant(target, target->left);
		}
		else
		{
			y = find_Mininum(target->right);
			y_Original_Color = y->color_Bit;
			x = y->right;
			if (y->parent == target)
			{
				x->parent = y;//潜在改变NIL的风险哎……
			}
			else
			{
				rb_Transplant(y, y->right);
				y->right = target->right;
				y->right->parent = y;
			}
			rb_Transplant(target, y);
			y->left = target->left;
			y->left->parent = y;
			y->color_Bit = target->color_Bit;
		}
		if (y_Original_Color == black)
			rb_del_Fixup(x);
		delete target;
	}

	rb_Tree_Node<keyType>* search(keyType val)
	{
		rb_Tree_Node<keyType>* seeker = this->root;
		while (seeker != this->NIL&&seeker->key != val)
		{
			if (val < seeker->key)
				seeker = seeker->left;
			else
				seeker = seeker->right;
		}
		return seeker;
	}

	void go_thru(rb_Tree_Node<keyType>* iter)
	{
		if (iter == this->NIL)
			return;
		go_thru(iter->left);
		cout << iter->key << ' ' << (int)iter->color_Bit<<' ';
		go_thru(iter->right);
	}

	ostream& mid_thru(rb_Tree_Node<keyType>* iter, ostream& stream1)
	{
		if (iter == this->NIL)
			return stream1;
		stream1 << iter->key << " " << (int)iter->color_Bit << "\n";
		mid_thru(iter->left, stream1);
		mid_thru(iter->right, stream1);
	}

	rb_Tree_Node<keyType>* get_root()const { return this->root; }

	ostream& broadth_thru(ostream& stream_output)
	{
		queue<rb_Tree_Node<keyType>> queue1;
		if (this->root != NIL)
			queue1.push(*this->root);
		while (!queue1.empty())
		{
			auto this_Node = queue1.front();
			stream_output << this_Node.key << ' ' << (int)this_Node.color_Bit << '\n';
			queue1.pop();
			if (this_Node.left != NIL)
				queue1.push(*this_Node.left);
			if (this_Node.right != NIL)
				queue1.push(*this_Node.right);
		}
		return stream_output;
	}
};

int main()
{
	rb_Tree<int> tree;
	for (int i = 0; i != 100; ++i)
	{
		tree.insert(rand());
	}
	//fstream fout("D:\\a.txt", ios::out);
	tree.go_thru(tree.get_root());
	//fout.close();
	cout << endl;
	tree.del(tree.search(32757));
	tree.go_thru(tree.get_root());
}