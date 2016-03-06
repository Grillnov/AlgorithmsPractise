#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<array>
#include<unordered_map>
using namespace std;
struct MyStruct
{
	string str;
	MyStruct(string str = "")
	{
		this->str = str;
	}
	size_t operator()(const MyStruct& m1)const
	{
		unsigned hashVal = 0;
		int digit = 1;
		for (int i = 0; i != m1.str.size(); i++)
		{
			for (int j = 0; j != i; j++)
				digit *= 128;
			hashVal += digit;
		}
		return digit;
	}
	bool operator==(const MyStruct& another)const
	{
		return (this->str == another.str);
	}
};

int main()
{
	unordered_map<MyStruct, int, MyStruct> hashMap;
	hashMap.insert(make_pair(MyStruct("wtf!"),125));
	hashMap.insert(make_pair(MyStruct("wtf2!"), 12125));
	auto a = hashMap.insert(make_pair(MyStruct("wtf!"), 1223));
	map<string, int> map2;
	auto b = map2.insert(make_pair(" ", 125));
	cout << hashMap.begin()->first.str;
}