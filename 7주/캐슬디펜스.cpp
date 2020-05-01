#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#define MAX 15
using namespace std;

int N, M, D;
int map[MAX][MAX];
bool live[MAX][MAX];

class Target {
public:
	pair<int, int> loc;
	int length;
public:
	Target(pair<int, int> loc_, int l) {
		loc = loc_;
		length = l;
	}
	bool operator<(const Target& t) const {
		if (length != t.length)
			return length < t.length;
		if (loc.second != t.loc.second)
			return loc.second < t.loc.second;
		return loc < t.loc;
	}
};

int getLength(int row1, int col1, int row2, int col2) {
	return abs(row1 - row2) + abs(col1 - col2);
}

int getTargetRow(int col, int row) {
	for (int i = row; i >= 0; i--) {
		if (!live[i][col])
			continue;
		if (map[i][col] == 1)
			return i;
	}
	return -1;
}

pair<int, int> getTarget(int archer, int row) {
	vector<Target> targets;
	for (int c = 0; c < M; c++) {
		int targetRow = getTargetRow(c, row - 1);
		if (targetRow != -1) {
			int length = getLength(targetRow, c, row, archer);
			if (length <= D) {
				pair<int, int> loc = make_pair(targetRow, c);
				Target target(loc, length);
				targets.push_back(target);
			}
		}
	}
	if(targets.size() == 0)
		return make_pair(-1, -1);

	sort(targets.begin(), targets.end());
	return targets[0].loc;
}

//row에 궁수들을 배치하고 죽일 수 있는 수
int playGame(int archer1, int archer2, int archer3, int row) {
	if (row < 1)
		return 0;
	set<pair<int, int>> targets;
	pair<int, int> target1 = getTarget(archer1, row);
	pair<int, int> target2 = getTarget(archer2, row);
	pair<int, int> target3 = getTarget(archer3, row);

	if(target1.first != -1)
		targets.insert(target1);
	if(target2.first != -1)
		targets.insert(target2);
	if(target3.first != -1)
		targets.insert(target3);

	for (auto it = targets.begin(); it != targets.end(); it++) {
		pair<int, int> targetLoc = *it;
		live[targetLoc.first][targetLoc.second] = false;
	}
	return targets.size() + playGame(archer1, archer2, archer3, row - 1);
}

int getArchersCnt(int archers) {
	int cnt = 0;
	for (int i = 0; i < M; i++) {
		if (archers & (1 << i))
			cnt++;
	}
	return cnt;
}
int getArcher(int archers, int num) {
	int turn = 1;
	for (int i = 0; i < M; i++) {
		if (archers & (1 << i)) {
			if (turn == num)
				return i;
			turn++;
		}
	}
}

int solve() {
	int ret = 0;
	for (int i = 0; i < (1 << M); i++) {
		if (getArchersCnt(i) == 3) {
			for (int j = 0; j < N; j++)
				for (int k = 0; k < M; k++)
					live[j][k] = true;

			int archer1 = getArcher(i, 1);
			int archer2 = getArcher(i, 2);
			int archer3 = getArcher(i, 3);
			int cntOfKill = playGame(archer1, archer2, archer3, N);
			ret = max(ret, cntOfKill);
		}
	}
	return ret;
}

int main() {
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	printf("%d\n", solve());
	return 0;
}
