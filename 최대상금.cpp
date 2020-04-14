#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int T, N;

class State{
public:
	int money;
	int remain;
public:
	bool operator<(const State& s) const{
		if (money != s.money)
			return money < s.money;
		return remain < s.remain;
	}
};
map<State, int> memo;

string swapStr(int a, int b, string money) {
	char tmp = money[a];
	money[a] = money[b];
	money[b] = tmp;
	return money;
}

int strToInt(const string& money) {
	int sum = 0;
	int len = 0;
	while (len != money.length()) {
		int num = money[len] - '0';
		sum *= 10;
		sum += num;
		len++;
	}
	return sum;
}

int solve(string& money, int remain) {
	if (remain == 0)
		return strToInt(money);
	State s;
	s.money = strToInt(money);
	s.remain = remain;
	if (memo.find(s) != memo.end())
		return memo[s];

	int score = 0;
	for (int i = 0; i < money.length() - 1; i++) {
		for (int j = i + 1; j < money.length(); j++) {
			int changeIdx1 = i;
			int changeIdx2 = j;
			string nextMoney = swapStr(i, j, money);			
			int nextScore = solve(nextMoney, remain - 1);
			score = max(score, nextScore);
		}
	}

	memo[s] = score;
	return score;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		memo.clear();
		string money;
		cin >> money;
		cin >> N;
		printf("#%d %d\n", tc, solve(money, N));
	}
	return 0;
}
