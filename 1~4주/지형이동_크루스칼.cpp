#include <string>
#include <vector>
#include <algorithm>

#define UP    0
#define LEFT  1
#define DOWN  2
#define RIGHT 3
using namespace std;

class DisJointSet {
public:
    int* parent;
    int* rank;
public:
    DisJointSet(int n) {
        init(n);
    }
    void init(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    bool union_(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return false;
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else if (rank[u] == rank[v]) {
            parent[v] = u;
            rank[u]++;
        }
        return true;
    }
    int find(int u) {
        if (u == parent[u])
            return u;
        return parent[u] = find(parent[u]);
    }
};
class Edge {
public:
    int vertex1;
    int vertex2;
    int weight;
public:
    Edge(int v1, int v2, int w) {
        vertex1 = v1;
        vertex2 = v2;
        weight = w;
    }
    bool operator<(const Edge& e) const{
        return weight < e.weight;
    }
};
int moveRow[4] = { -1, 0, 1, 0 };
int moveCol[4] = { 0, 1, 0, -1 };

bool isRange(const int& row, const int& col, const int& n) {
    if (row < 0 || col < 0)
        return false;
    if (row >= n || col >= n)
        return false;
    return true;
}

int getVertexNum(int row, int col, int n) {
    return n * row + col;
}
int solution(vector<vector<int>> land, int height) {
    vector<Edge> edges;    
    for (int i = 0; i < land.size(); i++) {
        for (int j = 0; j < land.size(); j++) {
            int currVertex = getVertexNum(i, j, land.size());
            for (int d = 0; d < 4; d++) {
                int nextRow = i + moveRow[d];
                int nextCol = j + moveCol[d];
                if (!isRange(nextRow, nextCol, land.size()))
                    continue;
                int nextVertex = getVertexNum(nextRow, nextCol, land.size());
                int currHeight = abs(land[i][j] - land[nextRow][nextCol]);
                int cost = currHeight > height ? currHeight : 0;
                Edge newEdge(currVertex, nextVertex, cost);
                edges.push_back(newEdge);
            }
        }
    }
    sort(edges.begin(), edges.end());

    DisJointSet disjointSet(land.size() * land.size());
    int ret = 0;
    for (int i = 0; i < edges.size(); i++) {
        if (disjointSet.union_(edges[i].vertex1, edges[i].vertex2))
            ret += edges[i].weight;
    }
    return ret;
}

int main() {
    vector<int> r1{ 10,11,10,11 };
    vector<int> r2{ 2,21,21,10 };
    vector<int> r3{ 1,20,21,11 };
    vector<int> r4{ 2,1,2,1 };
    vector<vector<int>> land{ r1,r2,r3,r4 };

    return solution(land, 3);
}
