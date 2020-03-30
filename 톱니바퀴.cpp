#include <iostream>
#include <cmath>
#define LEFT  -1 //반시계
#define RIGHT  1 //시계
#define N '0'
#define S '1'
using namespace std;

char cogs[4][9];
char cogsValue[4][2]; //0이 동쪽, 1이 서쪽
bool visit[4];

bool isRange(int cog) {
	if (cog < 0)
		return false;
	if (cog >= 4)
		return false;
	return true;
}

bool isPossible(int leftCog, int rightCog) {
	int leftCogValue = cogs[leftCog][cogsValue[leftCog][0]];
	int rightCogValue = cogs[rightCog][cogsValue[rightCog][1]];
	if (leftCogValue != rightCogValue)
		return true;
	return false;
}

int getValueLeft(int idx) {
	return idx % 8;
}
int getValueRight(int idx) {
	return (idx + 8) % 8;
}

void rotate(int cog, int direc, bool visit[]) {
	if (direc == LEFT) {
		visit[cog] = true;
		int leftCog = cog - 1;
		int rightCog = cog + 1;
		if (isRange(leftCog) && !visit[leftCog] && isPossible(leftCog, cog))
			rotate(leftCog, -direc, visit);
		if (isRange(rightCog) && !visit[rightCog] && isPossible(cog, rightCog))
			rotate(rightCog, -direc, visit);
		cogsValue[cog][0] = getValueLeft(cogsValue[cog][0] + 1);
		cogsValue[cog][1] = getValueLeft(cogsValue[cog][1] + 1);
	}
	else if (direc == RIGHT) {
		visit[cog] = true;
		int leftCog = cog - 1;
		int rightCog = cog + 1;
		if (isRange(leftCog) && !visit[leftCog] && isPossible(leftCog, cog))
			rotate(leftCog, -direc, visit);
		if (isRange(rightCog) && !visit[rightCog] && isPossible(cog, rightCog))
			rotate(rightCog, -direc, visit);
		cogsValue[cog][0] = getValueRight(cogsValue[cog][0] - 1);
		cogsValue[cog][1] = getValueRight(cogsValue[cog][1] - 1);
	}
}

int cal() {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		int northIdx = getValueRight(cogsValue[i][0] - 2);
		if (cogs[i][northIdx] == S)
			sum += pow(2, i);
	}
	return sum;
}

int main() {
	for (int i = 0; i < 4; i++) {
		scanf("%s ", cogs[i]);
		cogsValue[i][0] = 2;
		cogsValue[i][1] = 6;
	}
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int cog, direc;
		for (int i = 0; i < 4; i++)
			visit[i] = false;
		scanf("%d %d", &cog, &direc);
		rotate(cog - 1, direc, visit);
	}
	printf("%d", cal());
}
