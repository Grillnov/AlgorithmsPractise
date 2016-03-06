#include<iostream>

struct line_Tree
{
	int from;
	int to;
	line_Tree* left;
	line_Tree* right;
};
line_Tree* build_Tree(int from, int to)
{
	line_Tree* p = new line_Tree;
	p->from = from;
	p->to = to;
	if (to - from > 1)
	{
		p->left = build_Tree(from, (from + to) / 2);
		p->right = build_Tree((from + to) / 2, to);
	}
	else
		p->left = p->right = nullptr;
	return p;
}
void search(line_Tree* p, int from, int to)
{
	if (p == nullptr || p->to <= from || p->from >= to)
		return;
	if ((from <= p->from) && (to >= p->to))
	{
		printf("(%d,%d)", p->from, p->to);
		return;
	}
	search(p->left, from, to);
	search(p->right, from, to);
}
int main()
{
	line_Tree* root = build_Tree(1, 1000000);
	search(root, 2, 15545);
	getchar();
}