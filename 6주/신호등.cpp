#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
int T;
int N, M, S, D;

class Edge {
public:
	int node;
	long long length;
public:
	Edge(int n, long long l) {
		node = n;
		length = l;
	}
public:
	bool operator<(const Edge& e) {
		return node < e.node;
	}
};
vector<Edge> edges[100001];

class Node {
public:
	int node;
	int preNode;
	long long time;
	long long signalTime;
public:
	Node() {
	}
	Node(int n, int pn, int t, int st) {
		node = n;
		preNode = pn;
		time = t;
		signalTime = st;
	}
	void init() {
		node = -1;
		preNode = -1;
		time = -1;
		signalTime = -1;
	}
	bool canMove() {
		long long edgeSize = (long long)edges[node].size();
		int index = (time / signalTime) % edgeSize;
		int canMoveNode = edges[node][index].node;
		return preNode == canMoveNode;
	}
	void updateTime() {
		if (preNode == -1)
			return;
		while (!canMove()) {
			time = ((time / signalTime) + 1) * signalTime;
		}
	}
};
Node nodes[100001];

class Visit {
public:
	int node1;
	int node2;
public:
	Visit(int n1, int n2) {
		node1 = n1;
		node2 = n2;
	}
public:
	bool operator<(const Visit& v) const {
		if (node1 != v.node1)
			return node1 < v.node1;
		return node2 < v.node2;
	}
};
map<Visit, bool> visited;

class Compare {
public:
	bool operator()(const Node& n1, const Node& n2) {
		return n1.time > n2.time;
	}
};

long long solve() {
	priority_queue<Node, vector<Node>, Compare> pq;
	pq.push(nodes[S]);

	while (!pq.empty()) {
		Node curr = pq.top(); pq.pop();
		if (curr.node == D)
			return curr.time;

		curr.updateTime();
		long long currTime = curr.time;
		const vector<Edge>& currEdges = edges[curr.node];

		for (int e = 0; e < currEdges.size(); e++) {
			int nextNode = currEdges[e].node;
			if (nextNode == curr.node)
				continue;
			Visit visit(curr.node, nextNode);
			if (visited.find(visit) == visited.end()) {
				visited[visit] = true;
				long long nextTime = currTime + currEdges[e].length;
				long long nextSignalTime = nodes[nextNode].signalTime;
				Node newNode = nodes[nextNode];
				newNode.preNode = curr.node;
				newNode.time = nextTime;
				//Node newNode(nextNode, curr.node, nextTime, nextSignalTime); //이렇게 하면 시간초과나옴
				pq.push(newNode);
			}
		}
	}
	return -1;
}

void init() {
	visited.clear();
	for (int i = 1; i <= N; i++) {
		nodes[i].init();
		edges[i].clear();
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d %d", &N, &M, &S, &D);
		init();
		for (int m = 0; m < M; m++) {
			int node1, node2;
			long long length;
			scanf("%d %d %lld", &node1, &node2, &length);
			Edge edge1(node2, length);
			Edge edge2(node1, length);
			edges[node1].push_back(edge1);
			edges[node2].push_back(edge2);
		}
		for (int n = 1; n <= N; n++) {
			long long signalTime;
			scanf("%lld", &signalTime);			
			nodes[n].node = n;
			nodes[n].preNode = -1;
			nodes[n].time = 0;
			nodes[n].signalTime = signalTime;
			sort(edges[n].begin(), edges[n].end());
		}
		printf("%lld\n", solve());
	}
	return 0;
}
