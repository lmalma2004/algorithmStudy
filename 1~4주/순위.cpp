#include <string>
#include <vector>

using namespace std;

class Vertex {
public:
    vector<int> winner;
    vector<int> loser;
};
Vertex vertexs[101];

int getWinnerCnt(int vertex, bool visited[101]) {
    visited[vertex] = true;
    int cnt = 0;
    for (int i = 0; i < vertexs[vertex].winner.size(); i++) {
        int nextVertex = vertexs[vertex].winner[i];
        if (!visited[nextVertex]) {
            cnt += 1 + getWinnerCnt(nextVertex, visited);
        }
    }
    return cnt;
}
int getLoserCnt(int vertex, bool visited[101]) {
    visited[vertex] = true;
    int cnt = 0;
    for (int i = 0; i < vertexs[vertex].loser.size(); i++) {
        int nextVertex = vertexs[vertex].loser[i];
        if (!visited[nextVertex]) {
            cnt += 1 + getLoserCnt(nextVertex, visited);
        }
    }
    return cnt;
}

bool canKnow(int vertex, int n) {
    bool visited[101];
    for (int i = 0; i <= n; i++)
        visited[i] = false;
    int winnerCnt = getWinnerCnt(vertex, visited);
    int loserCnt = getLoserCnt(vertex, visited);
    if (winnerCnt + loserCnt == n - 1)
        return true;
    return false;
}

int solution(int n, vector<vector<int>> results) {
    for (int i = 0; i < results.size(); i++) {
        vertexs[results[i][1]].winner.push_back(results[i][0]);
        vertexs[results[i][0]].loser.push_back(results[i][1]);
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (canKnow(i, n))
            sum++;
    }
    return sum;
}

int main() {
    //	[[4, 3], [4, 2], [3, 2], [1, 2], [2, 5]]
    vector<vector<int>> results = { {4,3}, {4,2}, {3,2}, {1,2}, {2,5} };
    solution(5, results);
    return 0;
}
