#include "LambdaCounter.h"
#include <iomanip>

using namespace std;

LambdaCounter::LambdaCounter(int r1, double l1, int N)
{
	lambda = l1;
	r = r1;
	bestSet = WeightSearcher(r1,l1);
	for (size_t i = 1; i < N;++i) {
		WeightSearcher w(r1, l1);
		if (bestSet < w) {
			bestSet = w;
		}
	}
}


LambdaCounter::~LambdaCounter()
{
}

double LambdaCounter::dist() {
	return bestSet.w + bestSet.d;
}



ostream& operator<< (ostream& left, LambdaCounter right) {
	left << std::fixed << std::setprecision(4) <<
		right.lambda << "\t" <<
		right.dist() << "\t" <<
		right.bestSet << "\t" <<
		right.bestSet.w << "\t" <<
		right.bestSet.d << "\n";
	return left;
}
