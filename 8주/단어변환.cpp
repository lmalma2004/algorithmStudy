#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int getDiffCnt(string s1, string s2) {
	int cnt = 0;
	int len = 0;
	while (s1.length() != len) {
		if (s1[len] != s2[len])
			cnt++;
		len++;
	}
	return cnt;
}

int solution(string begin, string target, vector<string> words) {
	bool possible = false;
	for (int i = 0; i < words.size(); i++) {
		if (words[i] == target) {
			possible = true;
			break;
		}			
	}
	if (!possible)
		return 0;

	bool visited[50] = { false, };
	queue<pair<string, int>> q;
	q.push(make_pair(begin, 0));

	while (!q.empty()) {
		pair<string, int> curr = q.front(); q.pop();
		if (curr.first == target)
			return curr.second;
		
		for (int i = 0; i < words.size(); i++) {
			if (!visited[i] && getDiffCnt(words[i], curr.first) == 1) {
				visited[i] = true;
				pair<string, int> next = make_pair(words[i], curr.second + 1);
				q.push(next);
			}
		}
	}

	return 0;
}
