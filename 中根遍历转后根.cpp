#include <iostream>
#include <string>

using namespace std;
string inputPrefix, inputMid;
void PreMid2Post(size_t preStartIndex, size_t preEndIndex, size_t midStartIndex, size_t midEndIndex)
{
	char root = inputPrefix.at(preStartIndex);
	size_t midRootIndex = inputMid.find(root);
	int leftLen = midRootIndex - midStartIndex;
	int rightLen = midEndIndex - midRootIndex;
	if (leftLen > 0)
		PreMid2Post(preStartIndex + 1, preStartIndex + leftLen,
		midStartIndex, midStartIndex + leftLen - 1);
	if (rightLen > 0)
		PreMid2Post(preStartIndex + leftLen + 1, preStartIndex + leftLen + rightLen,
		midStartIndex + leftLen + 1, midStartIndex + leftLen + rightLen);
	cout << root;
}

int main(void)
{
	inputPrefix = "ABDECF";
	inputMid = "DBEAFC";
	size_t L = inputPrefix.length();
	PreMid2Post(0, L - 1, 0, L - 1);
}