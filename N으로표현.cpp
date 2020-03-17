#include <string>
#include <vector>
#include <cmath>
#include <set>
using namespace std;

set<int> memos[9];

bool calNumbers(int m1, int m2, const int& number) {
    int currMemo = m1 + m2;

    for (auto i = memos[m1].begin(); i != memos[m1].end(); i++) {
        for (auto j = memos[m2].begin(); j != memos[m2].end(); j++) {
            int num1 = *i;
            int num2 = *j;
            memos[currMemo].insert(num1 + num2);
            memos[currMemo].insert(num1 - num2);
            memos[currMemo].insert(num1 * num2);
            if (num2 != 0) {
                memos[currMemo].insert(num1 / num2);
            }
            if (memos[currMemo].find(number) != memos[currMemo].end())
                return true;
        }
    }
    return false;
}

bool isPossible(int MIN, int N, int number) {
    int firstNumber = 0;
    for (int i = 0; i < MIN; i++)
        firstNumber += N * pow(10, i);
    if (firstNumber == number)
        return true;
    memos[MIN].insert(firstNumber);

    for (int i = 1; i < MIN; i++) {
        if (calNumbers(i, MIN - i, number))
            return true;
    }
    return false;
}

int solution(int N, int number) {
    for (int i = 1; i < 9; i++) {
        if (isPossible(i, N, number))
            return i;
    }
    return -1;
}

int main() {
    solution(5, 12);
    return 0;
}
