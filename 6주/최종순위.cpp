#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 501
using namespace std;

int T;
int N;
int M;

class Team {
public:
	int id;
	int ranking;
public:
	Team(int i, int r) {
		id = i;
		ranking = r;
	}
	Team() {
	}
public:
	bool operator<(const Team& t) const {
		if (ranking != t.ranking)
			return ranking < t.ranking;
		return id < t.id;
	}
};

vector<Team> teams;
bool edges[MAX][MAX];
bool visited[MAX];

void topologicalSort(int team, vector<int>& sorted) {
	visited[team] = true;
	for (int i = 1; i <= N; i++) {
		if (!visited[i] && edges[team][i])
			topologicalSort(i, sorted);
	}
	sorted.push_back(team);
}
vector<int> solve() {
	vector<int> sorted;
	for (int i = 1; i <= N; i++) {
		if (!visited[i])
			topologicalSort(i, sorted);
	}
	reverse(sorted.begin(), sorted.end());

	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++) {
			if (edges[sorted[j]][sorted[i]])
				return vector<int>();
		}
	
	return sorted;
}
void init() {
	teams.clear();
	for (int i = 0; i <= N; i++)
		visited[i] = false;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			edges[i][j] = false;
}

void makeEdges() {
	for (int i = 0; i < teams.size() - 1; i++) {
		for (int j = i + 1; j < teams.size(); j++) {
			int id1 = teams[i].id;
			int id2 = teams[j].id;
			edges[id1][id2] = true;
		}
	}
}
int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		init();
		for (int i = 1; i <= N; i++) {
			int id;
			scanf("%d", &id);
			Team team(id, i);
			teams.push_back(team);
		}
		sort(teams.begin(), teams.end());
		makeEdges();

		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (edges[a][b]) {
				edges[a][b] = false;
				edges[b][a] = true;
			}
			else {
				edges[a][b] = true;
				edges[b][a] = false;
			}
		}
		vector<int> ret = solve();

		if (ret.size() == 0)
			printf("IMPOSSIBLE\n");
		else {
			for (int i = 0; i < ret.size(); i++)
				printf("%d ", ret[i]);
			printf("\n");
		}
	}
	return 0;
}
