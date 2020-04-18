#include <iostream>

using namespace std;
int T;

void getNextNumber(int& a, int& b) {
	int ma, mb;
	mb = (b / a) + 1;
	ma = a * mb;
	a = ma - b;
	b *= mb;
}

int solve(int a, int b) {	
	while (true) {
		if (a == 1)
			return b;
		getNextNumber(a, b);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int a, b;
		cin >> a;
		cin >> b;
		while (true) {
			if (!(b % a))
				break;
			getNextNumber(a, b);
		}
		cout << b / a << "\n";
	}
	return 0;
}
