#pragma once
#include "WeightSearcher.h"
#include <iostream>

using std::ostream;


class LambdaCounter
{
public:
	WeightSearcher bestSet;
	double lambda;
	int r;
	double dist();
	friend ostream& operator<< (ostream& left, LambdaCounter right);
	LambdaCounter(int r1, double l1, int N);
	~LambdaCounter();
};

