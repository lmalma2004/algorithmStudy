#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string ENDL = "\n";


vector<string> createSuffixes(const string& s) {
    vector<string> suffixes;

    int len = s.length();
    for (int i = 0; i < len; i++) {
        suffixes.push_back(s.substr(i, len - i));
    }

    return suffixes;
}

int getPrefixLength(const string& s0, const string& s1) {
    int len = min(s0.length(), s1.length());
    for (int i = 0; i < len; i++) {
        if (s0[i] != s1[i]) {
            return i;
        }
    }
    return len;
}

int findLongestPrefixLength(const vector<string>& suffixes) {
    int maxLength = 0;
    for (int i = 1; i < suffixes.size(); i++) {
        const string& s0 = suffixes[i - 1];
        const string& s1 = suffixes[i];
        int length = getPrefixLength(s0, s1);

        maxLength = max(maxLength, length);
    }
    return maxLength;
}

int solve(const string& s) {
    vector<string> suffixes = createSuffixes(s);
    sort(suffixes.begin(), suffixes.end());
    return findLongestPrefixLength(suffixes);
}

int getMaxMatchLength(const string& s, int p0, int p1) {
    int i;

    for (i = 0; i < s.length(); i++) {
        if (p0 + i >= s.length()) break;
        if (p1 + i >= s.length()) break;

        if (s[p0 + i] == s[p1 + i]) {
            continue;
        }
        if (s[p0 + i] != s[p1 + i]) {
            return i;
        }
    }

    return i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    cout << solve(s) << ENDL;

    return 0;
}
