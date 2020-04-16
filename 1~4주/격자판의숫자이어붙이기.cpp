#include <iostream>
#include <set>
#include <string>
using namespace std;

int T;
char maps[4][4];
int moveRow[4] = { -1, 0, 1, 0 };
int moveCol[4] = { 0, 1, 0, -1 };

bool isRange(int row, int col) {
	if (row < 0 || col < 0)
		return false;
	if (row >= 4 || col >= 4)
		return false;
	return true;
}

void findNumbers(int row, int col, string number, set<string>& numbers) {
	if (number.length() == 7) {
		numbers.insert(number);
		return;
	}
	number += maps[row][col];
	for (int d = 0; d < 4; d++) {
		int nextRow = row + moveRow[d];
		int nextCol = col + moveCol[d];
		if (isRange(nextRow, nextCol))
			findNumbers(nextRow, nextCol, number, numbers);
	}
}

int solve() {
	set<string> numbers;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			findNumbers(i, j, "", numbers);

	return numbers.size();
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		for(int i=0; i<4; i++)
			for (int j = 0; j < 4; j++) {
				scanf(" %c", &maps[i][j]);
			}
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
