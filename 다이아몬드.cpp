#include <iostream>
#include <vector>
using namespace std;

int T;
int N, K;
int minDiamond = 10001;
int maxDiamond = 0;
int diamonds[10001];

int solve() {
	int ret = 0;
	for (int i = minDiamond; i < maxDiamond + 1; i++) {
		int currMax = i + K + 1;
		int sum = 0;
		for (int j = i; j < currMax; j++) {
			if (j > maxDiamond)
				break;
			sum += diamonds[j];
		}
		if (ret < sum)
			ret = sum;
	}
	return ret;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 0; i < maxDiamond + 1; i++)
			diamonds[i] = 0;
		scanf("%d %d", &N, &K);
		minDiamond = 10001;
		maxDiamond = 0;
		for (int i = 0; i < N; i++) {
			int num;
			scanf("%d", &num);
			diamonds[num]++;
			if (minDiamond > num)
				minDiamond = num;
			if (maxDiamond < num)
				maxDiamond = num;
		}
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
