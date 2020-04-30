#include <iostream>
#include <algorithm>
#include <vector>
#define BLACKHOLE -1
#define SPACE	   0
#define UP		 0
#define RIGHT	 1
#define DOWN	 2
#define LEFT	 3
using namespace std;

int T, N;
int map[100][100];
int moveRow[4] = { -1, 0, 1, 0 };
int moveCol[4] = { 0, 1, 0,- 1 };
int startRow;
int startCol;
bool progress;
vector<pair<int ,int>> wormHoles[11];

bool isBlock(int& row, int& col) {
	if (map[row][col] >= 1 && map[row][col] <= 5)
		return true;
	return false;
}
bool isWall(int& row, int& col) {
	if (row < 0 || col < 0)
		return true;
	if (row >= N || col >= N)
		return true;
	return false;
}
bool isWormHole(int& row, int& col) {
	if (map[row][col] >= 6 && map[row][col] <= 10)
		return true;
	return false;
}

int setNextLoc(int& row, int& col, int& direc) {
	if (map[row][col] == 1) {
		if (direc == UP) {
			row += moveRow[DOWN];
			col += moveCol[DOWN];
			direc = DOWN;
		}
		else if (direc == RIGHT) {
			row += moveRow[LEFT];
			col += moveCol[LEFT];
			direc = LEFT;
		}
		else if (direc == DOWN) {
			row += moveRow[RIGHT];
			col += moveCol[RIGHT];
			direc = RIGHT;
		}
		else if (direc == LEFT) {
			row += moveRow[UP];
			col += moveCol[UP];
			direc = UP;
		}
	}
	else if (map[row][col] == 2) {
		if (direc == UP) {
			row += moveRow[RIGHT];
			col += moveCol[RIGHT];
			direc = RIGHT;
		}
		else if (direc == RIGHT) {
			row += moveRow[LEFT];
			col += moveCol[LEFT];
			direc = LEFT;
		}
		else if (direc == DOWN) {
			row += moveRow[UP];
			col += moveCol[UP];
			direc = UP;
		}
		else if (direc == LEFT) {
			row += moveRow[DOWN];
			col += moveCol[DOWN];
			direc = DOWN;
		}
	}
	else if (map[row][col] == 3) {
		if (direc == UP) {
			row += moveRow[LEFT];
			col += moveCol[LEFT];
			direc = LEFT;
		}
		else if (direc == RIGHT) {
			row += moveRow[DOWN];
			col += moveCol[DOWN];
			direc = DOWN;
		}
		else if (direc == DOWN) {
			row += moveRow[UP];
			col += moveCol[UP];
			direc = UP;
		}
		else if (direc == LEFT) {
			row += moveRow[RIGHT];
			col += moveCol[RIGHT];
			direc = RIGHT;
		}
	}
	else if (map[row][col] == 4) {
		if (direc == UP) {
			row += moveRow[DOWN];
			col += moveCol[DOWN];
			direc = DOWN;
		}
		else if (direc == RIGHT) {
			row += moveRow[UP];
			col += moveCol[UP];
			direc = UP;
		}
		else if (direc == DOWN) {
			row += moveRow[LEFT];
			col += moveCol[LEFT];
			direc = LEFT;
		}
		else if (direc == LEFT) {
			row += moveRow[RIGHT];
			col += moveCol[RIGHT];
			direc = RIGHT;
		}
	}
	else if (map[row][col] == 5) {
		if (direc == UP) {
			row += moveRow[DOWN];
			col += moveCol[DOWN];
			direc = DOWN;
		}
		else if (direc == RIGHT) {
			row += moveRow[LEFT];
			col += moveCol[LEFT];
			direc = LEFT;
		}
		else if (direc == DOWN) {
			row += moveRow[UP];
			col += moveCol[UP];
			direc = UP;
		}
		else if (direc == LEFT) {
			row += moveRow[RIGHT];
			col += moveCol[RIGHT];
			direc = RIGHT;
		}
	}
	return row;
}
int getMaxScore(int& row, int& col, int& direc) {
	if (map[row][col] == BLACKHOLE) 
		return 0;
	if (progress && row == startRow && col == startCol)
		return 0;

	progress = true;
	int add = 0;
	int nextRow, nextCol, nextDirec;
	if (isBlock(row, col)){
		nextRow = row;
		nextCol = col;
		nextDirec = direc;
		setNextLoc(nextRow, nextCol, nextDirec);
		add = 1;
	}
	else if (isWall(row, col)) {
		nextDirec = (direc + 2) % 4;
		nextRow = row + moveRow[nextDirec];
		nextCol = col + moveCol[nextDirec];
		add = 1;
	}
	else if (isWormHole(row, col)) {
		int wormHole = map[row][col];
		nextRow = wormHoles[wormHole][0].first;
		nextCol = wormHoles[wormHole][0].second;
		nextDirec = direc;
		if (row == nextRow && col == nextCol) {
			nextRow = wormHoles[wormHole][1].first + moveRow[direc];
			nextCol = wormHoles[wormHole][1].second + moveCol[direc];
		}
		else {
			nextRow += moveRow[direc];
			nextCol += moveCol[direc];
		}
	}
	else {
		nextRow = row + moveRow[direc];
		nextCol = col + moveCol[direc];
		nextDirec = direc;
	}

	return add + getMaxScore(nextRow, nextCol, nextDirec);
}

int solve() {
	
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == 8 && j == 15)
				int a = 5;
			if (map[i][j] == 0) {
				for (int d = 0; d < 4; d++) {
					startRow = i;
					startCol = j;
					progress = false;
					int score = getMaxScore(i, j, d);
					ret = max(ret, score);
				}
			}
		}
	}
	return ret;
}
void init() {
	for (int i = 0; i < 11; i++) {
		wormHoles[i].clear();
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		init();
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] >= 6) {
					pair<int, int> wormHole = make_pair(i, j);
					wormHoles[map[i][j]].push_back(wormHole);
				}
			}
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
