#include <string>
#include <vector>
#include <iostream>

using namespace std;

class function {
public:
	int priority;
	int completeTime;
	bool isComplete;
public:
	function(int p, int ct) {
		priority = p;
		completeTime = ct;
		isComplete = false;
	}
};

vector<function> functions;

bool isPossible(const int& function, const int& completeTime) {
	if (functions[function].completeTime <= completeTime && !functions[function].isComplete)
		return true;
	return false;
}

int getCompleteTime(const int& progress, const int& speed) {
	int remainProgress = 100 - progress;
	if (remainProgress % speed != 0)
		return (remainProgress / speed) + 1;
	return (remainProgress / speed);
}

int getFunctionCount(function& f) {
	if (f.isComplete)
		return 0;

	int sum = 0;
	for (int i = f.priority; i < functions.size(); i++) {
		if (isPossible(i, f.completeTime)) {
			sum++;
			functions[i].isComplete = true;
		}
		else
			break;
	}
	return sum;
}

vector<int> solve() {
	vector<int> ret;
	for (int i = 0; i < functions.size(); i++) {
		int cnt = getFunctionCount(functions[i]);
		if (cnt == 0)
			continue;
		ret.push_back(cnt);
	}
	return ret;
}

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	for (int i = 0; i < progresses.size(); i++) {
		function f = function(i, getCompleteTime(progresses[i], speeds[i]));
		functions.push_back(f);
	}
	return solve();
}