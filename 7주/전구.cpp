#include <iostream>
#include <algorithm>
#include <queue>
#define MAX 200

using namespace std;
int N, K;
short origArr[MAX];

void copyArr(short copy[], short orig[]) {
	for (int i = 0; i < N; i++)
		copy[i] = orig[i];
}

class State {
public:
	short arr[MAX];
	int cnt;
	int preBegin;
	int preEnd;
public:
	State(short a[], int c, int pB, int pE) {
		copyArr(arr, a);
		cnt = c;
		preBegin = pB;
		preEnd = pE;
	}
	bool isAllSame() {
		for (int i = 0; i < N - 1; i++) {
			if (arr[i] != arr[i + 1])
				return false;
		}
		return true;
	}
	bool isValid(int color) {
		if (preBegin <= color && color < preEnd)
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

int findEnd(short arr[], int begin) {
	int currColor = arr[begin];
	for (int i = begin; i < N; i++) {
		if (arr[i] != currColor)
			return i;
	}
	return N;
}
void change(short arr[], int begin, int end, int color) {
	for (int i = begin; i < end; i++) {
		arr[i] = color;
	}
}
int solve() {
	priority_queue<State, vector<State>, compare> pq;
	State start(origArr, 0, -1, -1);
	pq.push(start);

	while (!pq.empty()) {
		State curr = pq.top(); pq.pop();
		if (curr.isAllSame())
			return curr.cnt;
		for (int i = 0; i < N; i++) {
			if (curr.isValid(i)) {
				int begin = i;
				int end = findEnd(curr.arr, begin);
				int currColor = curr.arr[i];
				for (int c = 1; c <= K; c++) {
					if (c == currColor)
						continue;
					change(curr.arr, begin, end, c);
					State newState(curr.arr, curr.cnt + 1, begin, end);
					pq.push(newState);
				}
				change(curr.arr, i, end, currColor);
				i = end - 1;
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d", &origArr[i]);
	printf("%d", solve());
	return 0;
}

