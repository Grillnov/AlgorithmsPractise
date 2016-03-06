#include<iostream>
template<typename Type>
class customized_Stack
{
private:
	Type* Container;
	int top;
	int max_Size;
public:
	customized_Stack(int size)
	{
		Container = new Type[size];
		max_Size = size;
		top = -1;
	}
	bool is_Empty()
	{
		return (top == -1 ? true : false);
	}
	void push_back(Type& val)
	{
		++top;
		Container[top] = val;
	}
	void push_back(Type val)
	{
		++top;
		Container[top] = val;
	}
	void pop_back()
	{
		if (top == -1)
			std::cout << "Error";
		else
			--top;
	}
	Type& get_top()
	{
		return Container[top];
	}
};
int main()
{
	customized_Stack<int> stacker = customized_Stack<int>(6);
	stacker.push_back(5);
	stacker.push_back(6);
	//stacker.pop_back();
	std::cout << stacker.get_top();
}