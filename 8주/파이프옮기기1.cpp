#include <iostream>
#define MAX 16
#define HORI     0
#define VERTI	 1
#define DIAGONAL 2
using namespace std;

int N;
int map[MAX][MAX];
int moveRow[3] = { 0, 1, 1 };
int moveCol[3] = { 1, 0, 1 };
int memo[MAX][MAX][3];

int moveRight(int row, int col);
int moveDiagonal(int row, int col);
int moveDown(int row, int col);

bool isRange(int row, int col) {
	if (row < 0 || col < 0)
		return false;
	if (row >= N || col >= N)
		return false;
	return true;
}

bool isValid(int row, int col) {
	if (!isRange(row, col))
		return false;
	if (map[row][col] != 0)
		return false;
	return true;
}
int getAllCnt(int row, int col, int direc) {
	if (row == N - 1 && col == N - 1)
		return 1;
	if (memo[row][col][direc] != -1)
		return memo[row][col][direc];

	int sum = 0;
	if (direc == HORI) {
		sum += moveRight(row, col);
		sum += moveDiagonal(row, col);
	}
	else if (direc == VERTI) {
		sum += moveDiagonal(row, col);
		sum += moveDown(row, col);
	}
	else if (direc == DIAGONAL) {
		sum += moveRight(row, col);
		sum += moveDiagonal(row, col);
		sum += moveDown(row, col);
	}
	memo[row][col][direc] = sum;
	return sum;
}


int moveRight(int row, int col) {
	int sum = 0;
	int nextRow = row + moveRow[0];
	int nextCol = col + moveCol[0];
	if (isValid(nextRow, nextCol)) {
		sum += getAllCnt(nextRow, nextCol, HORI);
	}
	return sum;
}
int moveDiagonal(int row, int col) {
	int nextRow;
	int nextCol;
	for (int i = 0; i < 3; i++) {
		nextRow = row + moveRow[i];
		nextCol = col + moveCol[i];
		if (!isValid(nextRow, nextCol))
			return 0;
	}
	return getAllCnt(nextRow, nextCol, DIAGONAL);
}
int moveDown(int row, int col) {
	int sum = 0;
	int nextRow = row + moveRow[1];
	int nextCol = col + moveCol[1];
	if (isValid(nextRow, nextCol)) {
		sum += getAllCnt(nextRow, nextCol, VERTI);
	}
	return sum;
}

int solve() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int d = 0; d < 3; d++)
				memo[i][j][d] = -1;

	return getAllCnt(0, 1, HORI);
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	printf("%d", solve());
	return 0;
}
