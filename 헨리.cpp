#include <iostream>

using namespace std;

int T;

bool isPossible(int a, int b, int nextB) {
	int first = a * nextB;
	int second = b;
	if (first - second >= 0)
		return true;
	return false;
}

void getNextB(int& a, int& b) {
	int lo = 1;
	int hi = b;
	while (lo <= hi) {	
		int mid = (lo + hi) / 2;
		if (isPossible(a, b, mid))
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	int first = a * lo;
	int second = b;

	a = first - second;
	b *= lo;
}

int solve(int a, int b) {	
	while (true) {
		getNextB(a, b);
		if (a == 1)
			return b;
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", solve(a, b));
	}
	return 0;
}
