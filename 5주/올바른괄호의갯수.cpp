#include <string>
#include <vector>
#include <set>

using namespace std;
set<string> sets[15];

void makeSet(int n) {
    if (n == 1) {
        sets[n].insert("()");
        return;
    }
    makeSet(n - 1);
    for (auto it = sets[n - 1].begin(); it != sets[n - 1].end(); it++) {
        string curr = *it;
        string s1 = "(" + curr + ")";
        string s2 = curr + "()";
        string s3 = "()" + curr;
        sets[n].insert(s1);
        sets[n].insert(s2);
        sets[n].insert(s3);
    }
}
//틀린풀이
int solution2(int n) {
    makeSet(n);
    return sets[n].size();
}

int getAvailableCombination(int curr, int sum, int n) {
    int end = n * 2;
    if (curr == end) {
        if (sum == 0)
            return 1;
        else
            return 0;
    }
    if (sum < 0)
        return 0;
    if (sum > n)
        return 0;
    return getAvailableCombination(curr + 1, sum + 1, n) + getAvailableCombination(curr + 1, sum - 1, n);
}
//맞는풀이
int solution(int n) {
    if (n == 1)
        return 1;
    return getAvailableCombination(1, 1, n);
}

int main() {
    solution(4);
    return 0;
}
