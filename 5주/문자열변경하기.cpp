#include <iostream>
#include <string>
#include <queue>
#include <map>
using namespace std;

int T;
string s;
string t;
bool visited[100000];

int findNotMatchLoc(string& s, string& t, int len) {
	while (len < s.length()) {
		if (s[len] != t[len])
			return len;
		len++;
	}
	return len;
}

int findTarget(string& s, string& t, int len, char target, queue<int>& lenList) {
	while (len < s.length()) {
		if (s[len] == target)
			return len;
		if (!visited[len] && s[len] != t[len]) {
			lenList.push(len);
			visited[len] = true;
		}
		len++;
	}
	return len;
}

void swapString(string& s, int a, int b) {
	char tmp = s[a];
	s[a] = s[b];
	s[b] = tmp;
}

int solve() {
	queue<int> lenList;
	int len = 0;
	int startLen = findNotMatchLoc(s, t, 0);
	memset(visited, false, sizeof(bool) * s.length());
	lenList.push(startLen);
	visited[startLen] = true;

	int sum = 0;
	while (len < s.length()) {
		while (!lenList.empty()) {
			len = lenList.front(); lenList.pop();
			if (s[len] == t[len])
				continue;
			char target = t[len];
			int targetLen = findTarget(s, t, len + 1, target, lenList);
			swapString(s, len, targetLen);
			int swapCnt = targetLen - len;
			sum += swapCnt;
			len = targetLen;
		}
		len = findNotMatchLoc(s, t, len);
		lenList.push(len);
	}
	return sum;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		cin >> s;
		cin >> t;
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}

