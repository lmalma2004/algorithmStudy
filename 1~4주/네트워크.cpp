#include <string>
#include <vector>
#define MAX 200
using namespace std;

class DisJointSet {
public:
    int parent[MAX];
    int rank[MAX];
    int size;
public:
    DisJointSet(int n) {
        size = n;
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    void union_(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return;
#include <string>
#include <vector>
#define MAX 200
using namespace std;

class DisJointSet {
public:
    int parent[MAX];
    int rank[MAX];
    int size;
public:
    DisJointSet(int n) {
        size = n;
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    void union_(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return;
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else if (rank[u] == rank[v]) {
            parent[u] = v;
            rank[v]++;
        }
    }
    int find(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = find(parent[u]);
    }
    int getParentCnt() {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (parent[i] == i)
                cnt++;
        }
        return cnt;
    }
};

int findVertex(const vector<int>& computer) {
    for (int i = 0; i < MAX; i++)
        if (computer[i] == 1)
            return i;
    return MAX;
}

int solution(int n, vector<vector<int>> computers) {
    DisJointSet disJointSet(n);
    for (int i = 0; i < computers.size(); i++) {
        for (int j = 0; j < n; j++) {
            int currVertex = findVertex(computers[i]);
            if (j != currVertex && computers[i][j] == 1)
                disJointSet.union_(currVertex, j);
        }
    }
    return disJointSet.getParentCnt();
}
