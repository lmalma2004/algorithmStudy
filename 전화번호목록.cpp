#include <iostream>

using namespace std;

class Node {
public:
	bool exist;
	Node* next[10];
public:
	Node() {
		exist = false;
		for (int i = 0; i < 10; i++)
			next[i] = NULL;
	}
	~Node() {
		for (int i = 0; i < 10; i++)
			if (next[i] != NULL) {
#include <iostream>

using namespace std;

class Node {
public:
	bool exist;
	Node* next[10];
public:
	Node() {
		exist = false;
		for (int i = 0; i < 10; i++)
			next[i] = NULL;
	}
	~Node() {
		for (int i = 0; i < 10; i++)
			if (next[i] != NULL) {
				delete next[i];
				next[i] = NULL;
			}
	}
	bool push(char numbers[11]) {
		if (numbers[0] == '\0') {
			exist = true;
			return true;
		}
		if (exist)
			return false;

		int num = numbers[0] - '0';
		if (next[num] == NULL)
			next[num] = new Node();
		return next[num]->push(numbers + 1);
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
		delete root;
		root = NULL;
	}
	bool push(char numbers[11]) {
		if (root == NULL)
			root = new Node();
		return root->push(numbers);
	}
};

int T, N;

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		Trie trie;
		bool possible = true;
		for (int i = 0; i < N; i++) {
			char numbers[11];
			scanf("%s", numbers);
			if (!trie.push(numbers)) {
				possible = false;
				break;
			}
		}
		if (possible)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
