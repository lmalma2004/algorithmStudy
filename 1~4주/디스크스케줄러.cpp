#include <string>
#include <vector>
#include <queue>
#include <iostream>

#define MAXTASK 500
using namespace std;

class Task {
public:
    int id;
    int requestTime;
    int workTime;
public:
    Task(int i, int r, int w) {
        id = i;
#include <string>
#include <vector>
#include <queue>
#include <iostream>

#define MAXTASK 500
using namespace std;

class Task {
public:
    int id;
    int requestTime;
    int workTime;
public:
    Task(int i, int r, int w) {
        id = i;
        requestTime = r;
        workTime = w;
    }
};

class compareOfRequestTime {
public:
    bool operator()(const Task& t1, const Task& t2) {
        if (t1.requestTime == t2.requestTime)
            return t1.workTime > t2.workTime;
        return t1.requestTime > t2.requestTime;
    }
};
class compareOfWorkTime {
public:
    bool operator()(const Task& t1, const Task& t2) {
        if (t1.workTime == t2.workTime)
            return t1.requestTime > t2.requestTime;
        return t1.workTime > t2.workTime;
    }
};

priority_queue<Task, vector<Task>, compareOfRequestTime> pqOfRequestTime;
priority_queue<Task, vector<Task>, compareOfWorkTime> pqOfWorkTime;

bool completeTask[MAXTASK];

void DoTask(int& currTime, int& sumTime, Task& task) {
    if (currTime <= task.requestTime) {
        currTime = task.requestTime + task.workTime;
        sumTime += task.workTime;
        completeTask[task.id] = true;
        pqOfRequestTime.pop();
    }
    else {
        priority_queue<Task, vector<Task>, compareOfWorkTime> tmp;
        while (!pqOfWorkTime.empty()) {
            task = pqOfWorkTime.top();
            if (completeTask[task.id]) {
                pqOfWorkTime.pop();
                continue;
            }
            if (currTime < task.requestTime) {
                tmp.push(task);
                pqOfWorkTime.pop();
            }
            else {
                currTime += task.workTime;
                sumTime += currTime - task.requestTime;
                completeTask[task.id] = true;
                pqOfWorkTime.pop();
                while (!tmp.empty()) {
                    pqOfWorkTime.push(tmp.top());
                    tmp.pop();
                }
            }
        }
    }
}

int solution(vector<vector<int>> jobs) {

    for (int i = 0; i < jobs.size(); i++) {
        completeTask[i] = false;
        Task task = Task(i, jobs[i][0], jobs[i][1]);
        pqOfRequestTime.push(task);
        pqOfWorkTime.push(task);
    }
    int currTime = 0;
    int sumTime = 0;
    while (!pqOfRequestTime.empty()) {
        Task currTask = pqOfRequestTime.top();
        if (completeTask[currTask.id]) {
            pqOfRequestTime.pop();
            continue;
        }
        DoTask(currTime, sumTime, currTask);
    }

    /*
    int currTime = pqOfRequestTime.top().requestTime;
    int sumTime = 0;
    
    while (!pqOfWorkTime.empty()) {
        Task currTask = pqOfWorkTime.top();
        if (completeTask[currTask.id]) {
            pqOfWorkTime.pop();
            continue;
        }
        if (currTime <= currTask.requestTime) {
            while (!pqOfRequestTime.empty()) {
                currTask = pqOfRequestTime.top();
                pqOfRequestTime.pop();
                if (!completeTask[currTask.id])
                    break;
            }
            if (currTime <= currTask.requestTime) {
                currTime = currTask.requestTime + currTask.workTime;
                sumTime += currTask.workTime;
                completeTask[currTask.id] = true;
                continue;
            }
        }
        else
            pqOfWorkTime.pop();

        currTime += currTask.workTime;
        sumTime += currTime - currTask.requestTime;
        completeTask[currTask.id] = true;
    }
    */

    return sumTime / jobs.size();


}

int main() {
    //[[0, 3], [1, 9], [500, 6]]
    vector<vector<int>> jobs = { {0,3},{1,9},{2,6} };
    solution(jobs);
    return 0;
}
