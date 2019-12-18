#include <iostream>
#include "WeightSearcher.h"

using namespace std;

vector<double>* WeightSearcher::f_base;
int WeightSearcher::K;



WeightSearcher::WeightSearcher(int r, double l1)
{
	l = l1;
	//Забитие вектора весов
	a.resize(r);
	int M_ = r / 2;
	a[M_] = rnd(0, 1);
	double summ = a[M_];
	for(size_t i = M_-1; i > 0; --i){
		a[i] = a[r-i-1] = 0.5 * rnd(0, 1 - summ);
		summ += 2 * a[i];
	}
	a[0] = a[r - 1] = 0.5 * (1 - summ);
	initF();
	count_d();
	count_w();
}

WeightSearcher::~WeightSearcher()
{
}


void WeightSearcher::initF(){
	int M = a.size()/2;
	f.resize(K+1);
	for (size_t i = M; i <= K-M; i++) {
		f[i] = 0;
		for (size_t j = i-M; j <= i+M; ++j) {
			f[i]+=(*f_base)[j]*a[j+M-i];
		}
	}
}


void WeightSearcher::count_w() {
	double result = 0;
	for (size_t i = 1; i <= K; ++i) {
		result += _abs_(f[i] - f[i - 1]);
	}
	w = result;
}

void WeightSearcher::count_d() {
	double result = 0;
	for (size_t i = 0; i <= K; ++i) {
		result += _abs_(f[i] - (*f_base)[i]);
	}
	d = result / K;
}

ostream& operator<< (ostream& left, const WeightSearcher& right) {
	left << "[";
	for (size_t i = 0; i < right.a.size(); ++i) {
		left << right.a[i];
		if (i != right.a.size() - 1) left << ", ";
	}
	left << "]";
	return left;
}

double WeightSearcher::J() {
	return l*w+(1-l)*d;
}

bool operator<(WeightSearcher left, WeightSearcher right) {
	return left.J() < right.J();
}


void WeightSearcher::init(vector<double>* _f1, int _k) {
	f_base = _f1;
	K = _k;
}