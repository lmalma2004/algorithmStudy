#include <iostream>
#include <algorithm>
#include <queue>
#define MAX 20
#define MAX_TIME 401
using namespace std;

int N;
int sea[MAX][MAX];
bool visited[MAX][MAX];
int moveRow[4] = { -1 , 0, 1, 0 };
int moveCol[4] = { 0, 1, 0, -1 };
int sharkRow;
int sharkCol;
int sharkSize = 2;

struct Fish {
	int row;
	int col;
	int time;
};

bool isRange(int row, int col) {
	if (row >= N || col >= N)
		return false;
	if (row < 0 || col < 0)
		return false;
	return true;
}
bool isPossible(int row, int col) {
	int fishSize = sea[row][col];	
	if (sharkSize >= fishSize)
		return true;
	return false;
}
//dfs 시간초과
//row, col에서 가장 가까운 물고기까지의 시간
Fish getFish(int row, int col) {

	visited[row][col] = true;
	Fish ret = { row, col, MAX_TIME };
	int fishSize = sea[row][col];

	if (fishSize != 0 && sharkSize > fishSize) {
		ret = { row, col, 0 };
		visited[row][col] = false;
		return ret;
	}

	for (int d = 0; d < 4; d++) {
		int nextRow = row + moveRow[d];
		int nextCol = col + moveCol[d];
		if (!visited[nextRow][nextCol] && isRange(nextRow, nextCol) && isPossible(nextRow, nextCol)) {
			Fish fish = getFish(nextRow, nextCol);
			fish.time += 1;
			if (ret.time > fish.time) 
				ret = fish;
			else if (ret.time == fish.time) {
				if (ret.row > fish.row)
					ret = fish;
				else if (ret.row == fish.row) {
					if (ret.col > fish.col)
						ret = fish;
				}
			}
		}
	}
	visited[row][col] = false;
	return ret;
}

class compare {
public:
	bool operator()(const Fish& f1, const Fish& f2) {
		if (f1.time == f2.time) {
			if (f1.row == f2.row)
				return f1.col > f2.col;
			return f1.row > f2.row;
		}
		return f1.time > f2.time;
	}
};
//다익스트라
Fish getFish2(int row, int col) {
	visited[row][col] = true;
	Fish start = { row, col, 0 };
	priority_queue<Fish, vector<Fish>, compare> pq;
	pq.push(start);

	while (!pq.empty()) {
		Fish curr = pq.top(); pq.pop();
		int fishSize = sea[curr.row][curr.col];

		if (fishSize != 0 && sharkSize > fishSize)
			return curr;		

		for (int d = 0; d < 4; d++) {
			int nextRow = curr.row + moveRow[d];
			int nextCol = curr.col + moveCol[d];
			if (!visited[nextRow][nextCol] && isRange(nextRow, nextCol) && isPossible(nextRow, nextCol)) {
				visited[nextRow][nextCol] = true;
				Fish newFish = { nextRow, nextCol, curr.time + 1 };
				pq.push(newFish);
			}
		}
	}

	Fish ret = { row, col, MAX_TIME };
	return ret;
}

void initVisit() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			visited[i][j] = false;
}

int solve() {
	int time = 0;
	int catchCnt = 0;

	while (true) {
		initVisit();
		Fish fish = getFish(sharkRow, sharkCol);
		if (fish.time == MAX_TIME)
			return time;
		sharkRow = fish.row;
		sharkCol = fish.col;
		sea[sharkRow][sharkCol] = 0;
		catchCnt++;

		if (catchCnt == sharkSize) {
			sharkSize++;
			catchCnt = 0;
		}

		time += fish.time;
	}	
}

int main() {	
	scanf("%d", &N);
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) {
			scanf("%d", &sea[i][j]);
			if (sea[i][j] == 9) {
				sharkRow = i;
				sharkCol = j;
				sea[i][j] = 0;
			}
		}
	cout<<solve();
	return 0;
}
