#include <iostream>
#include <algorithm>
#define MAX 500
using namespace std;

int N;
int maps[MAX][MAX];
int moveRow[4] = { -1, 0, 1, 0 };
int moveCol[4] = { 0, 1, 0 ,-1 };
int memo[MAX][MAX];

bool isPossible(int row, int col, int preTree) {
	if (maps[row][col] <= preTree)
		return false;
	return true;
}

bool isRange(int row, int col) {
	if (row >= N || col >= N)
		return false;
	if (row < 0 || col < 0)
		return false;
	return true;
}

bool canMove(int row, int col, int tree) {
	for (int d = 0; d < 4; d++) {
		int nextRow = row + moveRow[d];
		int nextCol = col + moveCol[d];
		if (isRange(nextRow, nextCol) && isPossible(nextRow, nextCol, tree))
			return true;
	}
	return false;
}

int getMaxDay(int row, int col) {
	if (!canMove(row, col, maps[row][col]))
		return 0;
	if (memo[row][col] != -1)
		return memo[row][col];
	
	int maxDay = 1;
	for (int d = 0; d < 4; d++) {
		int nextRow = row + moveRow[d];
		int nextCol = col + moveCol[d];	
		if (isRange(nextRow, nextCol) && isPossible(nextRow, nextCol, maps[row][col])) {
			if(memo[nextRow][nextCol] == -1)
				memo[nextRow][nextCol] = getMaxDay(nextRow, nextCol);
			int day = 1 + memo[nextRow][nextCol];
			maxDay = max(maxDay, day);
		}
	}
	
	memo[row][col] = maxDay;
	return maxDay;
}

int solve() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			memo[i][j] = -1;
	int maxDay = 0;

	for(int i=0; i<N; i++)
		for (int j = 0; j < N; j++) {
			int day = 1 + getMaxDay(i, j);
			maxDay = max(maxDay, day);
		}

	return maxDay;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &maps[i][j]);
		}
	}
	printf("%d", solve());
	return 0;
}
