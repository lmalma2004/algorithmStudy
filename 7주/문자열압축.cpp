#include <string>
#include <algorithm>
using namespace std;

string intToStr(int num) {
	string ret;
	while (num != 0) {
		char curr = num % 10;
		num /= 10;
		ret += curr;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

void compress(const string& s, int len, int size, string& compressStr) {
	if (len + size >= s.length()) {
		while (len != s.length()) {
			compressStr += s[len];
			len++;
		}
		return;
	}

	string compareStr;
	for (int i = len; i < len + size; i++)
		compareStr += s[i];

	int nextLen = len + size;
	int cnt = 1;
	while (nextLen < s.length()) {
		string currStr;
		for (int i = nextLen; i < nextLen + size; i++) {
			if (i >= s.length())
				break;
			currStr += s[i];
		}
		if (compareStr != currStr)
			break;
		cnt++;
		nextLen += size;
	}
	if (cnt == 1) {
		compressStr += compareStr;
	}
	else {
		string cntStr = intToStr(cnt);
		compressStr += cntStr;
		compressStr += compareStr;
	}
	compress(s, nextLen, size, compressStr);
}
int solution(string s) {
	int minLen = s.length();
	for (int i = 1; i < s.length() / 2 + 1; i++) {
		string compressStr;
		compress(s, 0, i, compressStr);
		minLen = min(minLen, (int)compressStr.length());
	}
	return minLen;
}

int main() {
	solution("abcabcdede");
	return 0;
}
