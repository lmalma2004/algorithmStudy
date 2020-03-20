#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solution(int test_case) {
    string answer = "YES";
    string str;
    int count[3];
    for (int i = 0; i < 3; i++)
        count[i] = 0;
    cin >> str;
    for (char c : str) {
        int index = c - 'a';
        count[index]++;
    }
    sort(count, count + 3);
    count[2] -= count[0];

    if (count[2] > 1) {
        answer = "NO";
    }
    cout << "#" << test_case << " " << answer << endl;
}

int main() {
    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++) {
        solution(test_case);
    }

    return 0;
}
