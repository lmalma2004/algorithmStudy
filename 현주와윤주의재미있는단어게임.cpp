#include <iostream>
#include <string>
#include <list>
#include <map>
#define MAX 100000
using namespace std;

int N;

class Word {
public:
	string orig;
	string reverse;
public:
	Word(string& str) {
		orig = str;
		int len = str.length() - 1;
		while (len >= 0) {
			reverse.push_back(str[len]);
			len--;
		}
	}
	bool hate(Word word) {
		if (orig > word.orig)
			return false;
		if (word.reverse > reverse)
			return false;		
		return true;
	}
};
list<Word> words;
map<string, bool> visited;

list<Word>::iterator findPair(Word word, list<Word>::iterator it) {

	while (it != words.end()) {
		Word curr = *it;
		if (word.hate(curr) || curr.hate(word))
			return it;
		it++;
	}
	return words.end();
}

int solve() {
	int sum = 0;
	while (!words.empty()) {
		Word curr = words.front(); words.pop_front();
		auto it = findPair(curr, words.begin());
		while (it != words.end()) {
			sum++;
			auto next = ++it;
			it = findPair(curr, next);
		}
	}
	return sum;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		Word newWord(str);
		words.push_back(newWord);
	}
	printf("%d", solve());
	return 0;
}
