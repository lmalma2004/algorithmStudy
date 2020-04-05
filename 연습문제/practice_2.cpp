#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int getPercent(string& answer_sheet, string& sheet1, string& sheet2) {
    int maxWrongLen = 0;
    int wrongCnt = 0;
    int len = 0;
    int currWrongLen = 0;

    while (answer_sheet[len] != 0) {
        if (answer_sheet[len] == sheet1[len]) {
            len++;
            currWrongLen = 0;
            continue;
        }
        if (answer_sheet[len] == sheet2[len]) {
            len++;
            currWrongLen = 0;
            continue;
        }
        if (sheet1[len] == sheet2[len]) {
            currWrongLen++;
            wrongCnt++;
            maxWrongLen = max(maxWrongLen, currWrongLen);
        }
        else {
            currWrongLen = 0;
        }
        len++;
    }
    return wrongCnt + (maxWrongLen * maxWrongLen);
}

int solution(string answer_sheet, vector<string> sheets) {

    int maxPercent = 0;
    for (int i = 0; i < sheets.size() - 1; i++) {
        for (int j = i + 1; j < sheets.size(); j++) {
            int person1 = i;
            int person2 = j;
            int percent = getPercent(answer_sheet, sheets[person1], sheets[person2]);
            maxPercent = max(maxPercent, percent);
        }
    }
    return maxPercent;
}

int main() {
    vector<string> sheets = { "3241523133", "4121314445", "3243523133", "4433325251", "2412313253" };
    solution("4132315142", sheets);
    return 0;
}
