#include <iostream>
#define MAX 50
#define INT_MAX (1<<30) * 2 - 1
using namespace std;

int T;
int N, M;
int chocolate[MAX][MAX];
int memo[MAX][MAX + 1][MAX][MAX + 1];

void init() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			chocolate[i][j] = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= N; j++)
			for (int k = 0; k < M; k++)
				for (int h = 0; h <= M; h++)
					memo[i][j][k][h] = -1;
}

int getGrapeCnt(int rowBegin, int rowEnd, int colBegin, int colEnd) {
	int cnt = 0;
	for (int r = rowBegin; r < rowEnd; r++)
#include <iostream>
#define MAX 50
#define INT_MAX (1<<30) * 2 - 1
using namespace std;

int T;
int N, M;
int chocolate[MAX][MAX];
int memo[MAX][MAX + 1][MAX][MAX + 1];

void init() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			chocolate[i][j] = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= N; j++)
			for (int k = 0; k < M; k++)
				for (int h = 0; h <= M; h++)
					memo[i][j][k][h] = -1;
}

int getGrapeCnt(int rowBegin, int rowEnd, int colBegin, int colEnd) {
	int cnt = 0;
	for (int r = rowBegin; r < rowEnd; r++)
		for (int c = colBegin; c < colEnd; c++)
			cnt += chocolate[r][c];
	return cnt;
}

int getMinGrapeCnt(int rowBegin, int rowEnd, int colBegin, int colEnd) {
	if (rowEnd - rowBegin <= 1 && colEnd - colBegin <= 1)
		return 0;
	if (memo[rowBegin][rowEnd][colBegin][colEnd] != -1)
		return memo[rowBegin][rowEnd][colBegin][colEnd];

	int min = INT_MAX;
	int currGrapeCnt = getGrapeCnt(rowBegin, rowEnd, colBegin, colEnd);
	//가로로 자름
	for (int r = rowBegin + 1; r < rowEnd; r++) {
		int grapeUpCnt;
		int grapeDownCnt;

		if (memo[rowBegin][r][colBegin][colEnd] != -1)
			grapeUpCnt = memo[rowBegin][r][colBegin][colEnd];
		else
			grapeUpCnt = getMinGrapeCnt(rowBegin, r, colBegin, colEnd);

		if (memo[r][rowEnd][colBegin][colEnd] != -1)
			grapeDownCnt = memo[r][rowEnd][colBegin][colEnd];
		else
			grapeDownCnt = getMinGrapeCnt(r, rowEnd, colBegin, colEnd);

		int grapeCnt = currGrapeCnt + grapeUpCnt + grapeDownCnt;
		if (min > grapeCnt)
			min = grapeCnt;
	}
	//세로로 자름
	for (int c = colBegin + 1; c < colEnd; c++) {
		int grapeLeftCnt;
		int grapeRightCnt;

		if (memo[rowBegin][rowEnd][colBegin][c] != -1)
			grapeLeftCnt = memo[rowBegin][rowEnd][colBegin][c];
		else
			grapeLeftCnt = getMinGrapeCnt(rowBegin, rowEnd, colBegin, c);
		if (memo[rowBegin][rowEnd][c][colEnd] != -1)
			grapeRightCnt = memo[rowBegin][rowEnd][c][colEnd];
		else
			grapeRightCnt = getMinGrapeCnt(rowBegin, rowEnd, c, colEnd);

		int grapeCnt = currGrapeCnt + grapeLeftCnt + grapeRightCnt;
		if (min > grapeCnt)
			min = grapeCnt;
	}
	memo[rowBegin][rowEnd][colBegin][colEnd] = min;
	return min;
}

int solve() {
	int min = INT_MAX;
	int currGrapeCnt = getGrapeCnt(0, N, 0, M);
	if (N == 1 && M == 1)
		return 0;
	//가로로 자름
	for (int r = 1; r < N; r++) {
		int grapeCnt = currGrapeCnt + getMinGrapeCnt(0, r, 0, M) + getMinGrapeCnt(r, N, 0, M);
		if (min > grapeCnt)
			min = grapeCnt;
	}
	//세로로 자름
	for (int c = 1; c < M; c++) {
		int grapeCnt = currGrapeCnt + getMinGrapeCnt(0, N, 0, c) + getMinGrapeCnt(0, N, c, M);
		if (min > grapeCnt)
			min = grapeCnt;
	}
	return min;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		init();
		for (int r = 0; r < N; r++)
			for (int c = 0; c < M; c++)
				scanf("%d", &chocolate[r][c]);
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
