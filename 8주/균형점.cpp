#include <iostream>
#include <vector>
#include <cmath>
#define MAX 10
using namespace std;
int T;
int N;
double magneticsLoc[MAX];
double magneticsMass[MAX];

double getLeftForce(double loc, int turn) {
	double sum = 0;
	for (int i = 0; i <= turn; i++) {
		double d2 = pow((loc - magneticsLoc[i]), 2);
		double m = magneticsMass[i];
		sum += (m / d2);
	}
	return sum;
}
double getRightForce(double loc, int turn) {
	double sum = 0;
	for (int i = turn + 1; i < N; i++) {
		double d2 = pow((loc - magneticsLoc[i]), 2);
		double m = magneticsMass[i];
		sum += (m / d2);
	}
	return sum;
}

double getBalanceLoc(int turn) {
	double lo = magneticsLoc[turn];
	double hi = magneticsLoc[turn + 1];

	while (abs(lo - hi) >= 1e-12) {
		double mid = (lo + hi) / 2;
		double leftForce = getLeftForce(mid, turn);
		double rightForce = getRightForce(mid, turn);
		if (leftForce < rightForce)
			hi = mid;
		else if (leftForce > rightForce)
			lo = mid;
		else
			return mid;
	}
	return hi;
}

vector<double> getBalanceLocs() {
	vector<double> balanceLocs;
	for (int i = 0; i < N - 1; i++) {
		double balanceLoc = getBalanceLoc(i);
		balanceLocs.push_back(balanceLoc);
	}
	return balanceLocs;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%lf", &magneticsLoc[i]);
		for (int i = 0; i < N; i++)
			scanf("%lf", &magneticsMass[i]);

		vector<double> ret = getBalanceLocs();
		printf("#%d ", tc);
		for (int j = 0; j < ret.size(); j++)
			printf("%.10lf ", ret[j]);
		printf("\n");
	}
	return 0;
}
