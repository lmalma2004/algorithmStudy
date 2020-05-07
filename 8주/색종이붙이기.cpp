#include <iostream>
#include <vector>
using namespace std;
int pad[10][10];
int paperCnt[6] = { 5,5,5,5,5,5 };
int coverNum = 0;

bool isRange(int row, int col) {
	if (row < 0 || col < 0)
		return false;
	if (row >= 10 || col >= 10)
		return false;
	return true;
}

bool isPossible(int row, int col, int paperSize) {
	if (paperSize == 1)
		return true;
	if (!isPossible(row, col, paperSize - 1))
		return false;

	for (int i = 0; i < paperSize; i++) {
		int row1 = row + i;
		int col1 = col + (paperSize - 1);
		int row2 = row + (paperSize - 1);
		int col2 = col + i;
		if (!isRange(row1, col1))
			return false;
		if (!isRange(row2, col2))
			return false;
		if (pad[row1][col1] == 0 || pad[row2][col2] == 0)
			return false;
	}
	return true;
}

void cover(const pair<int, int>& loc, const int& paperSize) {
	for (int r = loc.first; r < loc.first + paperSize; r++) {
		for (int c = loc.second; c < loc.second + paperSize; c++) {
			pad[r][c] = 0;
		}
	}
}

pair<int, int> getLoc(int paperSize) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (pad[i][j] == 1) {
				if (isPossible(i, j, paperSize))
					return make_pair(i, j);
			}
		}
	}
	return make_pair(-1, -1);
}

int solve(int currCoverNum) {
	if (coverNum == currCoverNum)
		return 0;

	pair<int, int> loc;
	int paperSize = 0;

	loc = getLoc(10);
	if (loc.first != -1) {
		if (paperCnt[5] >= 4) {
			paperCnt[5] -= 4;
			cover(loc, 10);
			return 4 + solve(currCoverNum + 100);
		}
	}
	loc = getLoc(8);
	if (loc.first != -1) {
		if (paperCnt[4] >= 4) {
			paperCnt[4] -= 4;
			cover(loc, 8);
			return 4 + solve(currCoverNum + 64);
		}
	}
	loc = getLoc(6);
	if (loc.first != -1) {
		if (paperCnt[3] >= 4) {
			paperCnt[3] -= 4;
			cover(loc, 6);
			return 4 + solve(currCoverNum + 36);
		}
	}

	for (int i = 5; i >= 1; i--) {
		if (paperCnt[i] == 0)
			continue;
		loc = getLoc(i);
		if (loc.first != -1) {
			paperSize = i;
			break;
		}
	}
	if (paperSize == 0)
		return -99999;
	paperCnt[paperSize]--;
	cover(loc, paperSize);
	return 1 + solve(currCoverNum + (paperSize * paperSize));
}
int main() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			scanf("%d", &pad[i][j]);
			if (pad[i][j] == 1)
				coverNum++;
		}

	int ret = solve(0);
	if (ret < 0)
		ret = -1;

	printf("%d", ret);
	return 0;
}
