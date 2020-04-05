#include <string>
#include <vector>

using namespace std;

int open[4];
int close[4];

int countStr(string& str) {
    int cnt = 0;
    int len = 0;
    while (str[len] != 0) {
        if (str[len] == '[') {
            open[0]++;
            cnt++;
        }
        else if (str[len] == ']') {
            close[0]++;
            cnt++;
        }
        else if (str[len] == '{') {
            open[1]++;
            cnt++;
        }
        else if (str[len] == '}') {
            close[1]++;
            cnt++;
        }
        else if (str[len] == '(') {
            open[2]++;
            cnt++;
        }
        else if (str[len] == ')') {
            close[2]++;
            cnt++;
        }
        else if (str[len] == '<') {
            open[3]++;
            cnt++;
        }
        else if (str[len] == '>') {
            close[3]++;
            cnt++;
        }
        len++;
    }
    return cnt;
}

bool isPossible() {
    for (int i = 0; i < 4; i++) {
        if (open[i] != close[i])
            return false;
    }
    return true;
}

void findOpen(int& openLen, int& type, const string& str, bool* visited) {
    int len = openLen;

    while (str[len] != 0) {
        if (visited[len]) {
            len++;
            continue;
        }
        if (str[len] == '[') {
            openLen = len;
            type = 0;
            return;
        }
        else if (str[len] == '{') {
            openLen = len;
            type = 1;
            return;
        }
        else if (str[len] == '(') {
            openLen = len;
            type = 2;
            return;
        }
        else if (str[len] == '<') {
            openLen = len;
            type = 3;
            return;
        }
        len++;
    }
    openLen = -1;
}

void findClose(int& closeLen, int type, const string& str, bool* visited) {
    int len = closeLen;
    char target;
    if (type == 0)
        target = ']';
    else if (type == 1)
        target = '}';
    else if (type == 2)
        target = ')';
    else if (type == 3)
        target = '>';

    while (str[len] != 0) {
        if (visited[len]) {
            len++;
            continue;
        }
        if (str[len] == target) {
            closeLen = len;
            return;
        }
        len++;
    }
    closeLen = -1;
}
int solution(string inputString) {
    int cnt = countStr(inputString);
    if (cnt == 0)
        return 0;
    if (!isPossible())
        return -1;

    int strLen = inputString.length();
    bool* visited = new bool[strLen];
    int openLen = 0;
    int type = 0;
    int closeLen = 0;

    for (int i = 0; i < strLen; i++)
        visited[i] = false;

    int ret = 0;
    for (int i = 0; i < 4; i++)
        if (open[i] != 0)
            ret += open[i];

    while (true) {
        //열린괄호아무거나 찾는다.
        findOpen(openLen, type, inputString, visited);
        if (openLen == -1)
            break;
        visited[openLen] = true;
        open[type]--;

        closeLen = openLen + 1;
        //closeLen부터 type의 닫힌괄호를 찾는다.
        findClose(closeLen, type, inputString, visited);
        if (closeLen == -1)
            break;
        visited[closeLen] = true;
        close[type]--;
    }

    if (isPossible())
        return ret;
    return -1;
}

int main() {
    string s = ">_<";
    solution(s);
    return 0;
}
