#include <iostream>
#include <random>
#include "WeightSearcher.h"
#include "LambdaCounter.h"
#include "Logger.h"

using namespace std;


double _abs_(double r) {
	return r *(2*(r>0)-1);
}


void norm(vector<double> &n) {
	double sum = 0;
	for (size_t i = 0; i < n.size(); ++i) {
		sum += n[i];
	}
	for (size_t i = 0; i < n.size(); ++i) {
		n[i]/=sum;
	}

}

double rnd(double a, double b) {
	static mt19937 engine(random_device{}());
	auto generator = uniform_real_distribution<double>(a,b);
	return generator(engine);
}



double f_raw(double x) {
	return sin(x) + 0.5;
}

double xi(double xmin, double xmax, int i, int k) {
	return xmin + i * (xmax - xmin) / k;
}

double noise() {
	return rnd(-0.25, 0.25);
}



int main() {
	
	Logger logger("logger1.txt");
	Logger logger2("logger2.txt");
	Logger logger3("logger3.txt");

	double xmin = 0;
	double xmax = 3.1415926;
	int K = 100;
	int L = 10;

	vector<double> x;
	vector<double> f;
	vector<double> o;	//noises
	vector<double> fo;
	x.resize(K + 1);
	f.resize(K + 1);
	o.resize(K + 1);
	fo.resize(K + 1);
	for (size_t i = 0; i <= K; ++i) {
		x[i] = xi(xmin,xmax,i,K);
		f[i] = f_raw(x[i]);
		o[i] = noise();
		fo[i] = f[i] + o[i];
		logger.write(x[i],fo[i]);
	}
	
	int N = 1 + (log(0.05) / log(1 - 0.01 / (xmax - xmin)));
	cout << "N = " << N;
	cout << "\n";
	WeightSearcher::init(&fo,K);
	
	for (size_t r : {3, 5}) {
		LambdaCounter l_answ(r,0,N);
		cout << "l\tdist\talpha\t\t\t\tw\td\n";
		cout << l_answ;
		for (int l = 1; l <= L; ++l) {
			LambdaCounter counter(r, double(l)/L,N);
			cout << counter;
			if (l_answ.dist() > counter.dist()) l_answ = counter;
		}
		if(r!=5)
			for (size_t i = 0; i < l_answ.bestSet.f.size();++i) {
				logger2.write(x[i], l_answ.bestSet.f[i]);
			}
		else 
			for (size_t i = 0; i < l_answ.bestSet.f.size(); ++i) {
				logger3.write(x[i], l_answ.bestSet.f[i]);
			}
		cout << "r = " << r << ". The best result is:\n  lambda=" << l_answ.lambda;
		cout << "\n alphas: " << l_answ.bestSet;
		cout << "\n omega:" << l_answ.bestSet.w;
		cout << "\n delta:" << l_answ.bestSet.d;
		cout << "\n\n";
	}
}