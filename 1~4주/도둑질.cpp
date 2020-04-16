#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int solution(vector<int> money) {
    int houseSize = money.size();
    int dp[1000000]; //첫번째 집 훔친경우
    int dp2[1000000]; //첫번째 집 안훔친경우
    dp[0] = money[0];
    dp[1] = money[0];
    dp2[0] = 0;
    dp2[1] = money[1];

    for (int i = 2; i < houseSize; i++) {
        dp[i] = max(dp[i - 2] + money[i], dp[i - 1]);
        dp2[i] = max(dp2[i - 2] + money[i], dp2[i - 1]);
    }

    return max(dp[houseSize - 2], dp2[houseSize - 1]);
}
//----------------------잘못된 풀이---------------------------//
int n;
vector<int> mmoney;
map<pair<int, map<int, int>>, int> memo;

int getLeftAdj(int a) {
    if (a == 0)
        return n - 1;
    return a - 1;
}
int getRightAdj(int b) {
    return (b + 1) % n;
}

int getMaxMoney(int a, map<int, int>& visited) {
    pair<int, map<int, int>> currState = make_pair(a, visited);
    if (memo.find(currState) != memo.end())
        return memo[currState];
    

    int ret = mmoney[a];
    int leftAdj = getLeftAdj(a);
    int rightAdj = getRightAdj(a);
    visited[a]++;
    visited[leftAdj]++;
    visited[rightAdj]++;
    for (int i = 0; i < mmoney.size(); i++) {
        if (i != leftAdj && i != rightAdj && visited[i] == 0) {
            int currMoney = mmoney[a] + getMaxMoney(i, visited);
            if (ret < currMoney)
                ret = currMoney;
        }
    }
    visited[a]--;
    visited[leftAdj]--;
    visited[rightAdj]--;
    memo[currState] = ret;
    return ret;
}

int solution2(vector<int> money) {
    mmoney = money;
    n = money.size();
    int ret = 0;
    for (int i = 0; i < money.size(); i++) {
        map<int, int> visited;
        int leftAdj = getLeftAdj(i);
        int rightAdj = getRightAdj(i);
        visited[i]++;
        visited[leftAdj]++;
        visited[rightAdj]++;
        for (int j = 0; j < money.size(); j++) {
            if (j != leftAdj && j != rightAdj && visited[j] == 0) {
                int currMoney = money[i] + getMaxMoney(j, visited);
                if (ret < currMoney)
                    ret = currMoney;
            }
        }
    }
    return ret;
}

