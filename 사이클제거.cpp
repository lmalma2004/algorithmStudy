#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

set<int> vertexs[5001];
bool visited[5001][5001];
int removeVertex;
int visitCnt = 0;
int maxVertex = 0;

bool isPossible(int& preVertex, int& vertex) {
    visited[removeVertex][vertex] = true;
    visitCnt++;
    if (preVertex != -1) {
        for (auto v = vertexs[vertex].begin(); v != vertexs[vertex].end(); v++) {
            int nextVertex = *v;
            if (nextVertex != removeVertex) {
                if (nextVertex != preVertex && visited[removeVertex][nextVertex])
                    return false;
                else if (!visited[removeVertex][nextVertex]) {
                    if (!isPossible(vertex, nextVertex))
                        return false;
                }
            }
        }
    }
    else {
        for (auto v = vertexs[vertex].begin(); v != vertexs[vertex].end(); v++) {
            int nextVertex = *v;
            if (nextVertex != removeVertex){
                if (!visited[removeVertex][nextVertex]) {
                    if (!isPossible(vertex, nextVertex))
                        return false;
                }
            }
        }
    }
    return true;
}

int getStartVertex() {
    for (int i = 1; i <= maxVertex; i++) {
        if (i != removeVertex && !visited[removeVertex][i])
            return i;
    }
    return -1;
}


int solution(int n, vector<vector<int>> edges) {
    if (edges.size() == 2)
        return 3;
    for (int i = 0; i < edges.size(); i++) {
        int vertex1 = edges[i][0];
        int vertex2 = edges[i][1];
        vertexs[vertex1].insert(vertex2);
        vertexs[vertex2].insert(vertex1);
        maxVertex = max(maxVertex, max(vertex1, vertex2));
    }

    int sum = 0;
    for (int i = 1; i <= maxVertex; i++) {
        removeVertex = i;
        int startVertex;
        int preVertex;
        visitCnt = 0;
        while (true) {
            startVertex = getStartVertex();
            preVertex = -1;
            if (startVertex == -1)
                break;
            if (!isPossible(preVertex, startVertex))
                break;
        }
        if (startVertex == -1)
            sum += i;
    }
    return sum;
}


int main() {
    vector<vector<int>> edges = { {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 1}, {2, 7}, {3, 6} };
    solution(8, edges);
    return 0;
}



