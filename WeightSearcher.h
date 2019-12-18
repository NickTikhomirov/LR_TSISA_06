#pragma once

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

double rnd(double, double);
void norm(vector<double>&);
double _abs_(double r);


class WeightSearcher
{
	void initF();
	void count_w();
	void count_d();
	static vector<double>* f_base; //noisy function
	static int K;
public:
	static void init(vector<double>*, int);
	
	vector<double> a; //alphas
	vector<double> f; //cleaned function
	double d; //delta
	double w; //omega
	double l; //lambda
	WeightSearcher() {}
	WeightSearcher(int,double);
	~WeightSearcher();
	double J();
	friend ostream& operator<< (ostream& left, const WeightSearcher& right);
	friend bool operator<(WeightSearcher left, WeightSearcher right);
};

