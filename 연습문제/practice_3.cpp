#include <string>
#include <vector>

using namespace std;

vector<int> rangeSum;

int getWrongCnt(string& road, int start, int len) {       
    if (start == 0)
        return rangeSum[len - 1];
    return rangeSum[start + len - 1] - rangeSum[start - 1];
}
//n재료를 가지고 len길이의 도로를 만들 수 있냐
bool isPossible(string& road, int len, int n) {
    for (int i = 0; i <= road.size() - len; i++) {
        int wrongCnt = getWrongCnt(road, i, len);
        if (wrongCnt <= n)
            return true;
    }
    return false;
}
int makeRangeSum(const string& road, int index) {
    if (index == 0) {
        rangeSum[0] = road[0] == '0' ? 1 : 0;
        return rangeSum[0];
    }
    int add = road[index] == '0' ? 1 : 0;
    return rangeSum[index] = makeRangeSum(road, index - 1) + add;
}

int solution(string road, int n) {
    int lo = 0;
    int hi = road.length();
    rangeSum.resize(hi);
    makeRangeSum(road, road.size() - 1);

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (isPossible(road, mid, n))
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return hi;
}

int main() {
    string road = "001100";
    int n = 5;
    solution(road, n);
    return 0;
}
