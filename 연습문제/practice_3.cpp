#include <string>
#include <vector>

using namespace std;

//n재료를 가지고 len길이의 도로를 만들 수 있냐

int getWrongCnt(string& road, int start, int len) {
    int sum = 0;    

    for (int i = start; i < start + len; i++) {
        if (road[i] == '0')
            sum++;
    }
    return sum;
}
bool isPossible(string& road, int len, int n) {
    for (int i = 0; i <= road.size() - len; i++) {
        int wrongCnt = getWrongCnt(road, i, len);
        if (wrongCnt <= n)
            return true;
    }
    return false;
}

int solution(string road, int n) {
    int lo = 0;
    int hi = road.length();

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
