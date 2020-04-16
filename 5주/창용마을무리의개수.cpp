#include <iostream>
using namespace std;
int T;
int N, M;

class Edge {
public:
	int a;
	int b;
};
class DisJointSet {
public:
	int parent[101];
	int rank[101];
	int parentSize;
public:
	void init(int ps) {
		for (int i = 1; i <= ps; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
		parentSize = ps;
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
		else {
			parent[u] = v;
			rank[v]++;
		}	
	}
	int find(int u) {
		if (u == parent[u])
			return u;
		return parent[u] = find(parent[u]);
	}
	int getGroupCnt() {
		int grpCnt = 0;
		for (int i = 1; i <= parentSize; i++)
			if (i == parent[i])
				grpCnt++;
		return grpCnt;
	}
};
DisJointSet disjointSet;
Edge edges[4950];
int edgeSize;

void init() {
	disjointSet.init(N);
	edgeSize = 0;
}

int solve() {
	for (int i = 0; i < edgeSize; i++) 
		disjointSet.union_(edges[i].a, edges[i].b);	
	return disjointSet.getGroupCnt();
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		init();
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &edges[edgeSize].a, &edges[edgeSize].b);
			edgeSize++;
		}
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
