#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int mtime;
int memo[100][100001];

int getMaxMoney(vector<vector<int>>& travel, int loc, int currTime) {
    if (travel.size() == loc)
        return 0;
    if (currTime > mtime)
        return 0;
    if (memo[loc][currTime] != -1)
        return memo[loc][currTime];

    int nextTime1 = currTime + travel[loc][0];
    int nextMoney1 = nextTime1 <= mtime ? travel[loc][1] + getMaxMoney(travel, loc + 1, nextTime1) : 0;
    int nextTime2 = currTime + travel[loc][2];
    int nextMoney2 = nextTime2 <= mtime ? travel[loc][3] + getMaxMoney(travel, loc + 1, nextTime2) : 0;

    memo[loc][currTime] = max(nextMoney1, nextMoney2);
    return memo[loc][currTime];
}

int solution(int K, vector<vector<int>> travel) {
    mtime = K;
    for (int i = 0; i < travel.size(); i++)
        for (int j = 0; j < K; j++)
            memo[i][j] = -1;
    return getMaxMoney(travel, 0, 0);
}
