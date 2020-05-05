#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#define MAX 500
using namespace std;

class Task {
public:
	int id;
	int timeOfRequest;
	int timeOfWork;
public:
	Task(int i, int tR, int tW) {
		id = i;
		timeOfRequest = tR;
		timeOfWork = tW;
	}
	bool operator<(const Task& t) const {
		if (timeOfWork == t.timeOfWork)
			return timeOfRequest < t.timeOfRequest;
		return timeOfWork < t.timeOfWork;
	}
};

class compareRequest {
public:
	bool operator()(const Task& t1, const Task& t2) {
		if (t1.timeOfRequest == t2.timeOfRequest) 
			return t1.timeOfWork > t2.timeOfWork;
		return t1.timeOfRequest > t2.timeOfRequest;
	}
};
bool doneTask[MAX];
priority_queue<Task, vector<Task>, compareRequest> taskOfRequest;
list<Task> taskOfWork;

void DoTask(const Task& task, int& currTime, int& sumTime) {
	currTime += task.timeOfWork;
	sumTime += task.timeOfWork;
	doneTask[task.id] = true;
	
	for (auto it = taskOfWork.begin(); it != taskOfWork.end();) {
		Task currTask = *it;
		if (doneTask[currTask.id]) {
			it = taskOfWork.erase(it);
			continue;
		}
		if (currTime <= currTask.timeOfRequest) {
			it++;
			continue;
		}
		doneTask[currTask.id] = true;
		currTime += currTask.timeOfWork;
		sumTime += (currTime - currTask.timeOfRequest);
		it = taskOfWork.begin();
	}
}

int solution(vector<vector<int>> jobs) {

	for (int i = 0; i < jobs.size(); i++) {
		Task newTask(i, jobs[i][0], jobs[i][1]);
		taskOfRequest.push(newTask);
		taskOfWork.push_back(newTask);
		doneTask[i] = false;
	}
	taskOfWork.sort();

	int sumTime  = 0;
	int currTime = 0;
	while (!taskOfRequest.empty()) {
		Task task = taskOfRequest.top(); taskOfRequest.pop();
		if (doneTask[task.id])
			continue;
		currTime = task.timeOfRequest;
		DoTask(task, currTime, sumTime);
	}

	return sumTime / jobs.size();
}

int main() {
	vector<vector<int>> jobs1 = { {0,3}, {1,9}, {2,6} };
	vector<vector<int>> jobs2 = { {24, 10}, {18, 39}, {34, 20}, {37, 5}, {47, 22}, {20, 47}, {15, 34}, {15, 2}, {35, 43}, {26, 1} };
	solution(jobs2);
	return 0;
}
