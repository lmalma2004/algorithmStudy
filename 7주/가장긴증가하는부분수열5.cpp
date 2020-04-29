#include <iostream>
#include <vector>
#include <map>
using namespace std;
int N;
vector<int> arr;
map<int, vector<int>> memo;

vector<int> getArr(int idx) {
	if (idx == arr.size())
		return vector<int>();
	if (memo.find(idx) != memo.end())
		return memo[idx];

	int curr = arr[idx];
	vector<int> ret;
	ret.push_back(curr);

	vector<int> origRet = ret;

	for (int i = idx + 1; i < arr.size(); i++) {
		int next = arr[i];
		if (curr < next) {
			vector<int> nextArr = getArr(i);
			nextArr.insert(nextArr.begin(), origRet.begin(), origRet.end());
			if (ret.size() < nextArr.size()) {
				ret = nextArr;
				memo[i] = ret;
			}				
		}
	}

	memo[idx] = ret;
	return ret;	
}
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		arr.push_back(n);
	}
	vector<int> ret;
	ret.resize(0);
	for (int i = 0; i < N; i++) {
		vector<int> curr = getArr(i);
		if (ret.size() < curr.size())
			ret = curr;
	}

	printf("%d\n", ret.size());
	for (int i = 0; i < ret.size(); i++) {
		printf("%d ", ret[i]);
	}
	return 0;
}
