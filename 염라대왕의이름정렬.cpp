#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int T, N;
class Node {
public:
	Node* next[26];
	bool check;
public:
	class QueueNode {
	public:
		Node* node;
		string word;
	public:
		QueueNode(Node* n, string s) {
			node = n;
			word = s;
		}
	};
public:
	Node() {
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
		check = false;
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int T, N;
class Node {
public:
	Node* next[26];
	bool check;
public:
	class QueueNode {
	public:
		Node* node;
		string word;
	public:
		QueueNode(Node* n, string s) {
			node = n;
			word = s;
		}
	};
public:
	Node() {
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
		check = false;
	}
	void init() {
		for (int i = 0; i < 26; i++) {
			if (next[i] != NULL) {
				next[i]->init();
				next[i] = NULL;
			}
		}
		delete this;
	}
	void push(string s) {
		if (s[0] == NULL) {
			check = true;
			return;
		}
		int alphabet = s[0] - 'a';
		if (next[alphabet] == NULL)
			next[alphabet] = new Node();
		s.erase(s.begin());
		next[alphabet]->push(s);
	}
	void print() {
		QueueNode queueNode(this, "");
		queue<QueueNode> q;
		q.push(queueNode);
		while (!q.empty()) {
			QueueNode curr = q.front();
			q.pop();
			if (curr.node->check)
				printf("%s\n", curr.word.c_str());
			for (int i = 0; i < 26; i++) {
				if (curr.node->next[i] == NULL)
					continue;
				char alphabet = i + 'a';
				QueueNode newNode(curr.node->next[i], curr.word + alphabet);
				q.push(newNode);
			}
		}
	}
};
class Trie {
public:
	Node* root;
public:
	Trie() {
		root = NULL;
	}
	~Trie() {
		root->init();
		root = NULL;
	}
	void push(string s) {
		if (root == NULL)
			root = new Node();
		root->push(s);
	}
	void printAllWord() {
		root->print();
	}
};

class compare {
public:
	bool operator()(const string& s1, const string& s2) {
		if (s1.length() == s2.length()) {
			if (s1.compare(s2) < 0)
				return false;
			return true;
		}
		return s1.length() > s2.length();
	}
};

void solve1() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		priority_queue<string, vector<string>, compare> pq;
		map<string, bool> memo;
		for (int i = 0; i < N; i++) {
			string s;
			cin >> s;
			if (memo[s])
				continue;
			memo[s] = true;
			pq.push(s);
		}
		printf("#%d\n", tc);
		string preStr = "";
		while (!pq.empty()) {
			if (preStr != pq.top()) {
				printf("%s\n", pq.top().c_str());
				preStr = pq.top();
			}
			pq.pop();
		}
	}
}
void solve2() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		map<string, bool> memo;
		Trie trie;
		for (int i = 0; i < N; i++) {
			string s;
			cin >> s;
			if (memo[s])
				continue;
			memo[s] = true;
			trie.push(s);
		}
		printf("#%d\n", tc);
		trie.printAllWord();
	}
}

void solve3() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		vector<string> words[51];
		map<string, bool> memo;
		for (int i = 0; i < N; i++) {
			string s;
			cin >> s;
			if (memo[s])
				continue;
			words[s.length()].push_back(s);
			memo[s] = true;
		}
		printf("#%d\n", tc);
		for (int i = 1; i < 51; i++) {
			sort(words[i].begin(), words[i].end());
			string preStr = " ";
			for (int j = 0; j < words[i].size(); j++) {
				if (preStr != words[i][j]) {
					printf("%s\n", words[i][j].c_str());
					preStr = words[i][j];
				}
			}
		}
	}
}
int main() {
	solve2();
	return 0;
}
