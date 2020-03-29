#include <string>
#include <vector>
using namespace std;
bool isPossible(int n, const vector<int>& stones, int k) {
	int currLength = 0;
	for (int i = 0; i < stones.size(); i++) {
		if (stones[i] - n <= 0)
			currLength++;
		else
			currLength = 0;
		if (currLength > k)
			return false;
	}
	return true;
}
int solution(vector<int> stones, int k) {
	int lo = 0;
	int hi = 200000000;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (isPossible(mid, stones, k))
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return hi;
}
int main() {
	vector<int> stones = { 2,4,5,3,2,1,4,2,5,1 };
	int k = 3;
	solution(stones, k);
	return 0;
}
