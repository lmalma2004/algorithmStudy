#include <iostream>
#define MAX 100
using namespace std;

class DisJointSet {
public:
	int parent[MAX];
	int rank[MAX];
public:
	DisJointSet() {
		for (int i = 0; i < MAX; i++) {
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
};
