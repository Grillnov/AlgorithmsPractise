#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double epsilon = 1e-7;
const double c = 1e-4;

struct labeledInstance
{
	char x1;
	char x2;
	char x3;
	char label;
	labeledInstance(bool x1, bool x2, bool x3, bool label) :
		x1(x1), x2(x2), x3(x3), label(label){};
};

struct Weight
{
	double w1;
	double w2;
	double w3;
	double threshold;
	Weight() :w1(-1.23), w2(-1.33), w3(-1.26), threshold(2.9){};
};

bool isConverged(const Weight& w1, const Weight& w2)
{
	bool flag = true;
	if (abs(w1.threshold - w2.threshold) > epsilon)
		flag = false;
	if (abs(w1.w1 - w2.w1) > epsilon)
		flag = false;
	if (abs(w1.w2 - w2.w2) > epsilon)
		flag = false;
	if (abs(w1.w3 - w2.w3) > epsilon)
		flag = false;
	return flag;
}

double dotProduct(const labeledInstance& label, const Weight& weight)
{
	return label.x1*weight.w1 + label.x2*weight.w2 + label.x3*weight.w3 + weight.threshold;
}

void vectDec(Weight& weight, const labeledInstance& label, double c)
{
	weight.w1 -= label.x1*c;
	weight.w2 -= label.x2*c;
	weight.w3 -= label.x3*c;
	weight.threshold -= c;
}

void vectInc(Weight& weight, const labeledInstance& label, double c)
{
	weight.w1 += label.x1*c;
	weight.w2 += label.x2*c;
	weight.w3 += label.x3*c;
	weight.threshold += c;
}

int main(int arcv, char** argv)
{
	vector<labeledInstance> trainingSet;
	trainingSet.reserve(6);
	trainingSet.push_back(labeledInstance(0, 0, 0, 0));
	trainingSet.push_back(labeledInstance(0, 0, 1, 1));
	trainingSet.push_back(labeledInstance(0, 1, 1, 1));
	trainingSet.push_back(labeledInstance(1, 0, 0, 1));
	trainingSet.push_back(labeledInstance(1, 0, 1, 1));
	trainingSet.push_back(labeledInstance(1, 1, 0, 1));
	Weight weightVector = Weight();
	Weight weightVectorUpdated = Weight();
	int i = 0;
	while (true)
	{
		++i;
		for (auto a : trainingSet)
		{
			double dotProd = dotProduct(a, weightVector);
			if (dotProd >= 0 && a.label == 0)
			{
				vectDec(weightVectorUpdated, a, c);
			}
			if (dotProd < 0 && a.label == 1)
			{
				vectInc(weightVectorUpdated, a, c);
			}
		}
		if (isConverged(weightVector, weightVectorUpdated))
			break;
		else
			weightVector = weightVectorUpdated;
		if (i % 1000 == 0)
			cout << weightVectorUpdated.w1 << ' ' << weightVectorUpdated.w2 << ' ' << weightVectorUpdated.w3 << endl;
	}
	cout << i << endl;
	cout << weightVectorUpdated.w1 << ' ' << weightVectorUpdated.w2 << ' ' << weightVectorUpdated.w3 << ' ' << weightVectorUpdated.threshold << endl;
}