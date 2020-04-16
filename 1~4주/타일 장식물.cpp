#include <string>
#include <vector>

using namespace std;

long long memo[81];

long long getFrameLen(int N) {
	if (memo[N] != -1)
		return memo[N];
	if (N == 1) // f(0)
		return 4;
	if (N == 2) // f(1)
		return 6;

	return memo[N] = getFrameLen(N - 1) + getFrameLen(N - 2);
}
long long solution(int N) {
	for (int i = 1; i < 81; i++)
		memo[i] = -1;
	return getFrameLen(N);
}