#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

class Data {
public:
    string name;
    set<string> tags;
    int searchCnt;
    Data(string n) {
        name = n;
    }
    void pushTag(string& tag) {
        tags.insert(tag);
    }
};

vector<Data> datas;

int getSearchCnt(int data, vector<string>& tags) {
    int sum = 0;
    for (int i = 0; i < tags.size(); i++) {
        if (datas[data].tags.find(tags[i]) != datas[data].tags.end())
            sum++;
    }
    return sum;
}

class compare {
public:
    bool operator()(const Data& d1, const Data& d2) {
        if (d1.searchCnt == d2.searchCnt) {
            return d1.name > d2.name;
        }
        return d1.searchCnt < d2.searchCnt;
    }
};

vector<string> solution(vector<vector<string>> dataSource, vector<string> tags) {
    for (int i = 0; i < dataSource.size(); i++) {
        string name = dataSource[i][0];
        Data newData(name);
        for (int j = 1; j < dataSource[i].size(); j++) {
            string tag = dataSource[i][j];
            newData.pushTag(tag);
        }
        datas.push_back(newData);
    }

    priority_queue<Data, vector<Data>, compare> pq;

    for (int i = 0; i < datas.size(); i++) {
        int searchCnt = getSearchCnt(i, tags);
        datas[i].searchCnt = searchCnt;
        if (searchCnt == 0)
            continue;
        pq.push(datas[i]);
    }

    vector<string> answer;

    while (!pq.empty()) {
        string name = pq.top().name;
        pq.pop();
        answer.push_back(name);
        if (answer.size() >= 10)
            break;
    }

    return answer;
}
