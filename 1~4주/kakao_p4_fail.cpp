#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<long long, bool> memo;

long long getMinNumber(long long lo, long long hi) {
    if (!memo[lo])
        return lo;
    if (lo >= hi) {
        if (memo[hi])
            return -1;
        return hi;
    }
    long long mid = (lo + hi) / 2;

    long long num1 = getMinNumber(lo, mid - 1);
    if (num1 != -1)
        return num1;

    long long num2 = getMinNumber(mid + 1, hi);
    if (num1 == -1 && num2 == -1) {
        if (memo[mid])
            return -1;
        return mid;
    }
    if (num1 == -1) {
        if (memo[mid])
            return num2;
        return min(mid, num2);
    }
    if (num2 == -1) {
        if (memo[mid])
            return num1;
        return min(mid, num1);
    }
    if (memo[mid])
        return min(num1, num2);
    return min(mid, min(num1, num2));
}

long long getRoomNumber(long long& k, long long room_number) {
    if (!memo[room_number]) {
        memo[room_number] = true;
        return room_number;
    }

    long long lo = room_number + 1;
    long long hi = k;

    if (!memo[lo]) {
        memo[lo] = true;
        return lo;
    }

    /*long long num = getMinNumber(lo, hi);
    memo[num] = true;
    return num;*/

    long long mid = (lo + hi) / 2;
    long long num;
    long long num1 = getMinNumber(lo, mid - 1);
    if (num1 != -1) {
        memo[num1] = true;
        return num1;
    }
    long long num2 = getMinNumber(mid + 1, hi);

    if (num1 == -1 && num2 == -1)
        num = mid;
    else if (num1 == -1) {
        if (memo[mid])
            num = num2;
        else
            num = min(mid, num2);
    }
    else if (num2 == -1) {
        if (memo[mid])
            num = num1;
        else
            num = min(mid, num1);
    }
    else {
        if (memo[mid])
            num = min(num1, num2);
        else
            num = min(mid, min(num1, num2));
    }
    memo[num] = true;
    return num;
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for (int i = 0; i < room_number.size(); i++) {
        answer.push_back(getRoomNumber(k, room_number[i]));
    }
    return answer;
}

int main() {
    vector<long long> rn = { 1, 3, 4, 1, 3, 1 };

    solution(10, rn);
    return 0;
}


