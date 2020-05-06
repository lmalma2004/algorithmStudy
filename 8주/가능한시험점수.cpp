#include <iostream>
#include <vector>
#include <map>
#define MAX 100
using namespace std;
int T, N;
int problems[MAX];
bool checkScore[10001];
vector<int> scores;

int getScoreCnt(int problem) {
	int score = problems[problem];
	int origScoreSize = scores.size();

	if (!checkScore[score]) {
		checkScore[score] = true;
		scores.push_back(score);
	}
	for (int i = 0; i < origScoreSize; i++){
		int newScore = scores[i] + score;
		if (checkScore[newScore])
			continue;
		checkScore[newScore] = true;
		scores.push_back(newScore);
	}

	int addCnt = scores.size() - origScoreSize;
	return addCnt;
}

int solve() {
	int sum = 1;
	for (int i = 0; i < N; i++) 
		sum += getScoreCnt(i);	
	return sum;
}

void init() {
	scores.clear();
	for (int i = 0; i < 10001; i++)
		checkScore[i] = false;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &problems[i]);
		}
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
