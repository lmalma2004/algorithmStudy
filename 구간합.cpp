//배열의 구간 최소 쿼리(RMQ) 문제를 해결하는 구간 트리의 초기화
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;

class RSQ {
public:
	int n; //배열의 길이
	vector<long long> rangeSum; //각 구간의 합
public:
	RSQ(const vector<int>& array) {
		n = array.size();
		rangeSum.resize(n * 4);
		init(array, 0, n - 1, 1);
	}
public:
	//node 노드가 array[left, right]배열을 표한할 때
	//node를 루트로 하는 서브트리를 초기화하고, 이 구간의 합을 반환한다.
	long long init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeSum[node] = array[left];
		int mid = (left + right) / 2;
		long long leftSum = init(array, left, mid, node * 2);
		long long rightSum = init(array, mid + 1, right, node * 2 + 1);

		return rangeSum[node] = leftSum + rightSum;
	}
	//node가 표현하는 범위[nodeLeft, nodeRight]와 우리가 최소치를 찾기 원하는 구간[left, right]의 교집합의 구간 합을 반환한다.
	long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//두 구간이 겹치지 않으면 0을 반환한다: 무시됨
		if (right < nodeLeft || nodeRight < left) 
			return 0;
		//node가 표현하는 범위가 array[left, right]에 완전히 포함되는 경우
		if (left <= nodeLeft && nodeRight <= right)
			return rangeSum[node];
		//양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
		int mid = (nodeLeft + nodeRight) / 2;
		return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
	}
	//array[index] = newValue로 바뀌었을 때 node를 루트로 하는
	//구간 트리를 갱신하고 노드가 표현하는 구간의 합을 반환한다.
	long long update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		//index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
		if (index < nodeLeft || nodeRight < index)
			return rangeSum[node];
		//트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight) return rangeSum[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeSum[node] = 
			update(index, newValue, node * 2, nodeLeft, mid) + update(index, newValue, node * 2 + 1, mid + 1, nodeRight);
	}
	//query()를 외부에서 호출하기 위한 인터페이스
	long long query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
	long long update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};
vector<int> arr;

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		int num;
		scanf("%d", &num);
		arr.push_back(num);
	}
	RSQ rsq(arr);

	int minIdx = 1000000;
	for (int i = 0; i < M + K; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			rsq.update(b - 1, c);
		}
		else if (a == 2) {		
			printf("%lld\n", rsq.query(b - 1, c - 1));
		}
	}
	return 0;
}
