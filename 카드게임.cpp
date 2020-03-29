// 문제가 개편 되었습니다. 이로 인해 함수 구성이 변경되어, 과거의 코드는 동작하지 않을 수 있습니다.
// 새로운 함수 구성을 적용하려면 [코드 초기화] 버튼을 누르세요. 단, [코드 초기화] 버튼을 누르면 작성 중인 코드는 사라집니다.
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

bool memoCheck[2000][2000];
int memo[2000][2000];

int getMaxScore(vector<int>& left, vector<int>& right, int leftIdx, int rightIdx) {
	if (left.size() == leftIdx || right.size() == rightIdx)
		return 0;
	if (memoCheck[leftIdx][rightIdx])
		return memo[leftIdx][rightIdx];

	int ret1 = getMaxScore(left, right, leftIdx + 1, rightIdx);
	memo[leftIdx + 1][rightIdx] = ret1;
	int ret2 = getMaxScore(left, right, leftIdx + 1, rightIdx + 1);
	memo[leftIdx + 1][rightIdx + 1] = ret2;

	//오른쪽카드버림
	int ret3 = 0;
	if (left[leftIdx] > right[rightIdx])
		ret3 += right[rightIdx] + getMaxScore(left, right, leftIdx, rightIdx + 1);

	memoCheck[leftIdx][rightIdx] = true;
	memo[leftIdx][rightIdx] = max(max(ret1, ret2), ret3);
	return memo[leftIdx][rightIdx];
}

int solution(vector<int> left, vector<int> right) {
	return getMaxScore(left, right, 0, 0);
}

int main() {
	vector<int> left = { 3,2,5 };
	vector<int> right = { 2,4,1 };
	solution(left, right);
	return 0;
}
