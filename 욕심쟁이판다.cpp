#include <iostream>
#include <algorithm>
#include <map>
#define MAX 500
using namespace std;

int N;
int maps[MAX][MAX];
int moveRow[4] = { -1, 0, 1, 0 };
int moveCol[4] = { 0, 1, 0 ,-1 };
unsigned long long visited[40];
int visitedSize;

class Info {
public:
	int row;
	int col;
	int preTree;
	unsigned long long visited[40];
public:
	Info(int r, int c, int pT, unsigned long long v[40]) {
		row = r;
		col = c;
		preTree = pT;
		for (int i = 0; i < visitedSize; i++) {
			visited[i] = v[i];
		}
	}	
	bool operator<(const Info& info) const {
		if (row != info.row) 
			return row < info.row;		
		if (col != info.col)
			return col < info.col;
		if (preTree != info.preTree)
			return preTree < info.preTree;
		for (int i = 0; i < visitedSize; i++) {
			if (visited[i] != info.visited[i])
				return visited[i] < info.visited[i];
		}
		return visited[0] < info.visited[0];
	}
};
map<Info, int> memo;

bool isPossible(int row, int col, int preTree) {
	if (maps[row][col] < preTree)
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

int getVisitedNum(int row, int col) {
	return row * N + col;
}
int getVisitedIdx(int num) {
	return num / 64;
}

bool isVisit(int row, int col) {
	int visitedNum = getVisitedNum(row, col);
	int visitedIdx = getVisitedIdx(visitedNum);
	int visitedLoc = visitedNum % 64;
	if (visited[visitedIdx] & (1 << visitedLoc))
		return true;
	return false;
}

bool canMove(int row, int col, int tree) {
	for (int d = 0; d < 4; d++) {
		int nextRow = row + moveRow[d];
		int nextCol = col + moveCol[d];
		if (isRange(nextRow, nextCol) && !isVisit(nextRow, nextCol) && isPossible(nextRow, nextCol, tree))
			return true;
	}
	return false;
}


int getMaxDay(int row, int col, int preTree) {
	if (!canMove(row, col, maps[row][col]))
		return 0;

	Info info(row, col, preTree, visited);
	auto it = memo.find(info);
	if (it != memo.end())
		return (*it).second;

	int visitedNum = getVisitedNum(row, col);
	int visitedIdx = getVisitedIdx(visitedNum);
	int visitedLoc = visitedNum % 64;
	visited[visitedIdx] |= (1 << visitedLoc);

	int maxDay = 1;

	for (int d = 0; d < 4; d++) {
		int nextRow = row + moveRow[d];
		int nextCol = col + moveCol[d];	
		if (isRange(nextRow, nextCol) && !isVisit(nextRow, nextCol) && isPossible(nextRow, nextCol, maps[row][col])) {
			int day = 1 + getMaxDay(nextRow, nextCol, maps[row][col]);
			maxDay = max(maxDay, day);
		}
	}
	
	visited[visitedIdx] &= ~(1 << visitedLoc);

	memo[info] = maxDay;
	return maxDay;
}

int solve() {
	int maxDay = 0;
	visitedSize = ((N * N) / 64) + 1;

	for (int i = 0; i < visitedSize; i++)
		visited[i] = 0;

	for(int i=0; i<N; i++)
		for (int j = 0; j < N; j++) {
			int day = 1 + getMaxDay(i, j, 0);
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
