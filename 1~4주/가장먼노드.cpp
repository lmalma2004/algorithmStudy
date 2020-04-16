#include <string>
#include <vector>
#include <queue>
using namespace std;

class Vertex {
public:
    int v;
    int len;
    vector<int> edges;
public:
    Vertex() {
        len = 0;
    }
};

int dist[2][20001];
bool visited[20001];
Vertex vertexs[20001];
int maxLen = 0;

int makeDist(int vertexCnt) {
    queue<Vertex> q;
    q.push(vertexs[1]);
    visited[1] = true;
    while (!q.empty()) {
        Vertex currVertex = q.front();
        q.pop();
        visited[currVertex.v] = true;
        for (int e = 0; e < currVertex.edges.size(); e++) {
            if (!visited[currVertex.edges[e]]) {
                q.push(vertexs[currVertex.edges[e]]);
                visited[currVertex.edges[e]] = true;
                vertexs[currVertex.edges[e]].len = vertexs[currVertex.v].len + 1;
                dist[1][currVertex.edges[e]] = vertexs[currVertex.v].len + 1;
                if (maxLen < vertexs[currVertex.edges[e]].len)
                    maxLen = vertexs[currVertex.edges[e]].len;
            }
        }
    }
    int sum = 0;
    for (int i = 2; i <= vertexCnt; i++) {
        if (dist[1][i] >= maxLen)
            sum++;
    }
    return sum;
}

int solution(int n, vector<vector<int>> edge) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 20001; j++)
            dist[i][j] = 0;

    for (int i = 0; i < edge.size(); i++) {
        vertexs[edge[i][0]].v = edge[i][0];
        vertexs[edge[i][1]].v = edge[i][1];
        vertexs[edge[i][0]].edges.push_back(edge[i][1]);
        vertexs[edge[i][1]].edges.push_back(edge[i][0]);
    }
    return makeDist(n);
}

