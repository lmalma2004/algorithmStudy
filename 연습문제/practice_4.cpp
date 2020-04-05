#include <string>
#include <vector>
#include <map>
#define WITHDRAW 0
#define SAVE     1
using namespace std;

map<string, int> datas;
int datasMoney[100001];
int dataSize = 0;
bool tranCheck[100001];

int strToInt(string& s) {
    int sum = 0;
    int len = 0;
    while (s[len] != 0) {
        sum *= 10;
        sum += (s[len] - '0');
        len++;
    }
    return sum;
}

int getType(string& s) {
    if (s == "WITHDRAW")
        return 0;
    return 1;
}

string intToStr(int num) {
    string ret;
    while (num != 0) {
        char curr = (num % 10) + '0';
        num /= 10;
        ret = curr + ret;
    }
    return ret;
}

vector<vector<string>> solution(vector<vector<string>> snapshots, vector<vector<string>> transactions) {
    for (int i = 0; i < 100000; i++) {
        datasMoney[i] = 0;
        tranCheck[i] = false;
    }
    for (int i = 0; i < snapshots.size(); i++) {
        string name = snapshots[i][0];
        int money = strToInt(snapshots[i][1]);
        datas[name] = dataSize;
        datasMoney[dataSize] = money;
        dataSize++;
    }

    for (int i = 0; i < transactions.size(); i++) {
        int id = strToInt(transactions[i][0]);
        if (tranCheck[id])
            continue;
        int type = getType(transactions[i][1]);
        string name = transactions[i][2];
        int money = strToInt(transactions[i][3]);
        tranCheck[id] = true;

        if (datas.find(name) != datas.end()) {
            int idx = datas[name];
            if (type == WITHDRAW) {
                datasMoney[idx] -= money;
            }
            else if (type == SAVE) {
                datasMoney[idx] += money;
            }
        }
        else {
            datas[name] = dataSize;
            if (type == WITHDRAW) {
                datasMoney[dataSize] -= money;
            }
            else if (type == SAVE) {
                datasMoney[dataSize] += money;
            }
            dataSize++;
        }
    }

    vector<vector<string>> answer;

    for (auto it = datas.begin(); it != datas.end(); it++) {
        string name = (*it).first;
        int idx = (*it).second;
        int money = datasMoney[idx];
        string moneyStr = intToStr(money);

        vector<string> curr;
        curr.push_back(name);
        curr.push_back(moneyStr);
        answer.push_back(curr);
    }
    return answer;
}
