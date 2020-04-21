#include <iostream>
#include <vector>
using namespace std;
int T;
int N, M, S, D;

class Edge {
public:
	int node;
	int length;
public:
	Edge(int n, int l) {
		node = n;
		length = l;
	}
};
class Node {
public:
	int time;
	vector<Edge> edges;
};
Node nodes[100001];

int solve() {

}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d %d", &N, &M, &S, &D);
		for (int m = 0; m < M; m++) {
			int node1, node2, length;
			Edge edge1(node2, length);
			Edge edge2(node1, length);
			nodes[node1].edges.push_back(edge1);
			nodes[node2].edges.push_back(edge2);
		}
		for (int n = 0; n < N; n++) {
			int time;
			scanf("%d", &time);
			nodes[n].time = time;
		}
		printf("%d\n", solve());
	}
	return 0;
}
