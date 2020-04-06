#include <iostream>
#include <algorithm>
using namespace std;

int T, N;
int maps[100][100];
int moveCol[2] = { 0, 1 };
int memo[100][100];

int getMax(int row, int col) {
	if (row == N)
		return 0;
	if (memo[row][col] != -1)
		return memo[row][col];

	int add = maps[row][col];
	int nextRow = row + 1;
	int nextCol1 = col + moveCol[0];
	int nextCol2 = col + moveCol[1];
	int	ret1 = add + getMax(nextRow, nextCol1);
	int	ret2 = add + getMax(nextRow, nextCol2);

	memo[row][col] = max(ret1, ret2);
	return memo[row][col];
}

int solve() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= i; j++)
			memo[i][j] = -1;
	return getMax(0, 0);
}

int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);
		//for (int j = 0; j < N; j++)
		//	memset(memo[j], -1, sizeof(int) * (j + 1));		
		for (int j = 0; j < N; j++) {
			for (int k = 0; k <= j; k++) {
				scanf("%d", &maps[j][k]);
			}
		}
		printf("%d\n", solve());
	}
	return 0;
}
