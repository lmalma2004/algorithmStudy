#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int DY[] = { -1, 0, 1, 0 };
const int DX[] = { 0, -1, 0, 1 };

struct Position {
    int row;
    int col;
};

bool operator<(const pair<int, Position>& a, const pair<int, Position>& b) {
    return a.first > b.first;
}
#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int DY[] = { -1, 0, 1, 0 };
const int DX[] = { 0, -1, 0, 1 };

struct Position {
    int row;
    int col;
};

bool operator<(const pair<int, Position>& a, const pair<int, Position>& b) {
    return a.first > b.first;
}

bool positionIsValid(const Position& p, int n) {
    if ((p.row < 0) || (p.row >= n)) return false;
    if ((p.col < 0) || (p.col >= n)) return false;
    return true;
}

int solution(vector<vector<int>> land, int height) {
    int n = land.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    int totalCost = 0;

    priority_queue<pair<int, Position>> q;
    q.push(make_pair(0, Position{ 0, 0 }));

    while (!q.empty()) {
        pair<int, Position> item = q.top();
        q.pop();

        int cost = item.first;
        Position pos = item.second;

        if (visited[pos.row][pos.col]) {
            continue;
        }
        visited[pos.row][pos.col] = true;
        totalCost += cost;

        int curHeight = land[pos.row][pos.col];

        for (int d = 0; d < 4; d++) {
            Position nextPos = { pos.row + DY[d], pos.col + DX[d] };
            if (!positionIsValid(nextPos, n)) {
                continue;
            }
            if (visited[nextPos.row][nextPos.col]) {
                continue;
            }

            int nextHeight = land[nextPos.row][nextPos.col];
            int diffHeight = abs(nextHeight - curHeight);
            int nextCost = (diffHeight > height) ? diffHeight : 0;
            q.push(make_pair(nextCost, nextPos));
        }
    }

    return totalCost;
}

int main() {
    vector<vector<int>> land{
        { 1, 4, 8, 10 },
        { 5, 5, 5, 5 },
        { 10, 10, 10, 10 },
        { 10, 10, 10, 20 },
    };
    int a = solution(land, 3);
    return 0;
}
