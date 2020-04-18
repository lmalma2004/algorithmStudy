#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const string ENDL = "\n";


int indexOf(const string& s, char c, int startIndex) {
    int length = s.length();
    for (int i = startIndex; i < length; i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

long long solve(const string& s, const string& t) {
    long long count = 0;

    int length = s.length();
    int sIndex = indexOf(s, 'a', 0);
    int tIndex = indexOf(t, 'a', 0);

    while (sIndex != -1) {
        count += abs(tIndex - sIndex);

        sIndex = indexOf(s, 'a', sIndex + 1);
        tIndex = indexOf(t, 'a', tIndex + 1);
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        string s, t;
        cin >> s >> t;

        long long answer = solve(s, t);
        cout << "#" << tc << " " << answer << ENDL;
    }

    return 0;
}
