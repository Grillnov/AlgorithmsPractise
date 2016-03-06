template <class Type>
class Heap
{
public:
	unsigned Elements;
	Type* Data;
	Heap();
	void MinHeapfy(unsigned index);
	Heap(Type* Data, unsigned Number);
	void VaryKey(double newKey, unsigned index);
	Type ExtractTop();
	bool isEmpty();
};

template<class Type>
bool Heap<Type>::isEmpty()
{
	return (this->Elements == 0);
}

template<class Type>
void Heap<Type>::VaryKey(double newKey, unsigned index)
{
	Data[index].key = newKey;
	MinHeapfy(index);
}

template<class Type>
Type Heap<Type>::ExtractTop()
{
	Type ret = Data[0];
	Type temp = Data[0];
	Data[0] = Data[this->Elements];
	Data[this->Elements] = temp;
	--this->Elements;
	return ret;
}

template<class Type>
void Heap<Type>::MinHeapfy(unsigned index)
{
	while (true)
	{
		unsigned leftChild = 2 * index + 1;
		unsigned rightChild = 2 * index + 2;
		unsigned smallest = index;
		if (leftChild < this->Elements)
		{
			if (Data[leftChild] < Data[index])
				smallest = leftChild;
		}
		if (rightChild < this->Elements)
		{
			if (Data[rightChild] < Data[smallest])
				smallest = rightChild;
		}
		if (index == smallest)
			break;
		else
		{
			Type temp = Data[index];
			Data[index] = Data[smallest];
			Data[smallest] = temp;
		}
	}
};

template<class Type>
Heap<Type>::Heap(Type* Data, unsigned Number)
{
	this->Data = Data;
	this->Elements = Number;
	for (int i = (this->Elements) / 2; i >= 0; --i)
	{
		MinHeapfy(i);
	}
}