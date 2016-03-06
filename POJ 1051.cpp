#include<iostream>
#include <string>
#include<map>
#include<stack>
using namespace std;
int main()
{
	map<char, string>decode1;
	map<string, char>decode2;
	decode1['A'] = ".-";
	decode1['B'] = "-...";
	decode1['C'] = "-.-.";
	decode1['D'] = "-..";
	decode1['E'] = ".";
	decode1['F'] = "..-.";
	decode1['G'] = "--.";
	decode1['H'] = "....";
	decode1['I'] = "..";
	decode1['J'] = ".---";
	decode1['K'] = "-.-";
	decode1['L'] = ".-..";
	decode1['M'] = "--";
	decode1['N'] = "-.";
	decode1['O'] = "---";
	decode1['P'] = ".--.";
	decode1['Q'] = "--.-";
	decode1['R'] = ".-.";
	decode1['S'] = "...";
	decode1['T'] = "-";
	decode1['U'] = "..-";
	decode1['V'] = "...-";
	decode1['W'] = ".--";
	decode1['X'] = "-..-";
	decode1['Y'] = "-.--";
	decode1['Z'] = "--..";
	decode1['_'] = "..--";
	decode1[','] = ".-.-";
	decode1['.'] = "---.";
	decode1['?'] = "----";

	decode2[".-"] = 'A';
	decode2["-..."] = 'B';
	decode2["-.-."] = 'C';
	decode2["-.."] = 'D';
	decode2["."] = 'E';
	decode2["..-."] = 'F';
	decode2["--."] = 'G';
	decode2["...."] = 'H';
	decode2[".."] = 'I';
	decode2[".---"] = 'J';
	decode2["-.-"] = 'K';
	decode2[".-.."] = 'L';
	decode2["--"] = 'M';
	decode2["-."] = 'N';
	decode2["---"] = 'O';
	decode2[".--."] = 'P';
	decode2["--.-"] = 'Q';
	decode2[".-."] = 'R';
	decode2["..."] = 'S';
	decode2["-"] = 'T';
	decode2["..-"] = 'U';
	decode2["...-"] = 'V';
	decode2[".--"] = 'W';
	decode2["-..-"] = 'X';
	decode2["-.--"] = 'Y';
	decode2["--.."] = 'Z';
	decode2["..--"] = '_';
	decode2[".-.-"] = ',';
	decode2["---."] = '.';
	decode2["----"] = '?';
	decode2["..--"] = '_';
	decode2[".-.-"] = ',';
	decode2["---."] = '.';
	decode2["----"] = '?';

	int totCases;
	cin >> totCases;
	for (int i = 1; i <= totCases; ++i)
	{
		string encrypted;
		string decrypted;
		string binary;
		cin >> encrypted;
		stack<int> lengthInfo;
		for (int j = 0; j != encrypted.size(); ++j)
		{
			string temp = decode1[encrypted.at(j)];
			binary += temp;
			lengthInfo.push(temp.size());
		}
		int offset = 0;
		while (!lengthInfo.empty())
		{
			int curLen = lengthInfo.top();
			string temp = binary.substr(offset, curLen);
			offset += curLen;
			decrypted += decode2[temp];
			lengthInfo.pop();
		}
		cout << i << ": " << decrypted << endl;
	}
	return 0;
}