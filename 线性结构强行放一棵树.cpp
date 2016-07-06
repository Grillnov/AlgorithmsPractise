#include <iostream>
#include <vector>

struct Node
{
	int leftChild;
	int rightChild;
	int parent;
	int val;
	Node(){};
	Node(int val) :leftChild(-1), rightChild(-1), parent(-1), val(val){};
};

struct BinTree
{
	std::vector<Node> container;
	void insert(int val)
	{
		int itsindex = container.size();
		if (container.empty())
		{
			container.push_back(Node(val));
			return;
		}
		else
			container.push_back(Node(val));
		int itsparent = 0;
		while (true)
		{
			int trial;
			if (val < container.at(itsparent).val)
			{
				trial = container.at(itsparent).leftChild;
				if (trial == -1)
				{
					container.at(itsparent).leftChild = itsindex;
					container.at(itsindex).parent = itsparent;
					break;
				}
			}
			else
			{
				trial = container.at(itsparent).rightChild;
				if (trial == -1)
				{
					container.at(itsparent).rightChild = itsindex;
					container.at(itsindex).parent = itsparent;
					break;
				}
			}
			itsparent = trial;
		}
	}
	bool isExist(int val)
	{
		if (container.empty())
			return false;
		int index = 0;
		while (container.at(index).val != val)
		{
			if (container.at(index).val < val)
				index = container.at(index).rightChild;
			else
				index = container.at(index).leftChild;
			if (index == -1)
				return false;
		}
		return true;
	}

	int questIndex(int val)
	{
		if (container.empty())
			return -1;
		int index = 0;
		while (container.at(index).val != val)
		{
			if (container.at(index).val < val)
				index = container.at(index).rightChild;
			else
				index = container.at(index).leftChild;
			if (index == -1)
				break;
		}
		return index;
	}

	bool remove(int val)
	{
		int index = questIndex(val);
		if (index == -1)
			return false;

	}

	void subInOrderTraverse(int index)
	{
		Node temp = container.at(index);
		if (temp.leftChild != -1)
			subInOrderTraverse(temp.leftChild);
		std::cout << container.at(index).val;
		if (temp.rightChild != -1)
			subInOrderTraverse(temp.rightChild);
	}
	void inOrderTraverse()
	{
		subInOrderTraverse(0);
	}
};

int main(void)
{
	BinTree happyTree;
	happyTree.insert(3);
	happyTree.insert(4);
	happyTree.insert(2);
	happyTree.insert(1);
	happyTree.inOrderTraverse();
}