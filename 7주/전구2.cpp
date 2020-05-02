#include <iostream>
#include <algorithm>
#include <queue>
#define MAX 200

using namespace std;
int N, K;
int origArr[MAX];

void copyArr(int copy[], int orig[]) {
	for (int i = 0; i < N; i++)
		copy[i] = orig[i];
}

class Command {
public:
	int begin;
	int end;
	int color;
public:
	Command(int b, int e, int c) {
		begin = b;
		end = e;
		color = c;
	}
};

class State {
public:
	vector<Command> commands;
	int cnt;
	int preBegin;
	int preEnd;
public:
	State(int c, int pB, int pE) {
		cnt = c;
		preBegin = pB;
		preEnd = pE;
	}
	bool isValid(int loc) {
		if (preBegin == -1)
			return true;
		if (preBegin <= loc && loc < preEnd)
			return false;
		return true;
	}
};

class compare {
public:
	bool operator()(const State& s1, const State& s2) {
		return s1.cnt > s2.cnt;
	}
};


bool isValid(int preBegin, int preEnd, int loc) {
	if (preBegin == -1)
		return true;
	if (preBegin <= loc && loc < preEnd)
		return false;
	return true;
}

bool isAllSame(int arr[]) {
	for (int i = 0; i < N - 1; i++) {
		if (arr[i] != arr[i + 1])
			return false;
	}
	return true;
}

int findEnd(int arr[], int begin) {
	int currColor = arr[begin];
	for (int i = begin; i < N; i++) {
		if (arr[i] != currColor)
			return i;
	}
	return N;
}
void change(int arr[], int begin, int end, int color) {
	for (int i = begin; i < end; i++) {
		arr[i] = color;
	}
}

void progress(int arr[], const vector<Command>& commands) {
	for (int i = 0; i < commands.size(); i++) {
		int begin = commands[i].begin;
		int end = commands[i].end;
		int color = commands[i].color;
		change(arr, begin, end, color);
	}
}

int solve() {
	priority_queue<State, vector<State>, compare> pq;
	State start(0, -1, -1);
	pq.push(start);

	while (!pq.empty()) {
		State curr = pq.top(); pq.pop();
		int currArr[MAX];
		copyArr(currArr, origArr);
		progress(currArr, curr.commands);

		if (isAllSame(currArr))
			return curr.cnt;

		for (int i = 0; i < N; i++) {
			if (curr.isValid(i)) {
				int begin = i;
				int end = findEnd(currArr, begin);
				int pairColor1 = begin != 0 ? currArr[begin - 1] : -1;
				int pairColor2 = currArr[end];
				int currColor = currArr[begin];

				for (int c = 1; c <= K; c++) {
					if (c == currColor)
						continue;
					if (c != pairColor1)
						continue;
					if (c != pairColor2)
						continue;
					State newState(curr.cnt + 1, begin, end);
					Command newCommand(begin, end, c);
					newState.commands = curr.commands;
					newState.commands.push_back(newCommand);
					pq.push(newState);
				}
				i = end - 1;
			}
		}
	}
}

int solve2(int preBegin, int preEnd) {
	if (isAllSame(origArr))
		return 0;

	int minRet = 999999999;

	for (int i = 0; i < N; i++) {
		if (isValid(preBegin, preEnd, i)) {
			int begin = i;
			int end = findEnd(origArr, begin);
			int pairColor1 = begin != 0 ? origArr[begin - 1] : -1;
			int pairColor2 = origArr[end];
			int currColor = origArr[begin];

			for (int c = 1; c <= K; c++) {
				if (c == currColor)
					continue;
				if (c != pairColor1)
					continue;
				if (c != pairColor2)
					continue;
				change(origArr, begin, end, c);
				int currCnt = 1 + solve2(begin, end);
				minRet = min(minRet, currCnt);
				change(origArr, begin, end, currColor);
			}
			i = end - 1;
		}
	}

	return minRet;
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d", &origArr[i]);
	printf("%d", solve2(-1, -1));
	return 0;
}
