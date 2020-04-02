#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#define HORI  0
#define VERTI 1
using namespace std;

class Bus {
public:
    int direc;
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    vector<pair<int, int>> locList;
    set<int> busList;
    Bus() {
    }
    Bus(int sr, int sc, int er, int ec) {
        startRow = min(sr, er);
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#define HORI  0
#define VERTI 1
using namespace std;

class Bus {
public:
    int direc;
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    vector<pair<int, int>> locList;
    set<int> busList;
    Bus() {
    }
    Bus(int sr, int sc, int er, int ec) {
        startRow = min(sr, er);
        startCol = min(sc, ec);
        endRow = max(sr, er);
        endCol = max(sc, ec);
        if (sr == er)
            direc = HORI;
        else
            direc = VERTI;
    }
    //row, col에 있는 승객을 태울수 있는지
    bool isPossible(int row, int col) {
        if (startRow <= row && row <= endRow && startCol <= col && col <= endCol)
            return true;
        return false;
    }
};
class BusState {
public:
    int busCnt;
    int bus; //현재 탑승한 버스
public:
    BusState(int bc, int cb) {
        busCnt = bc;
        bus = cb;
    }
};
int startRow;
int startCol;
int endRow;
int endCol;
int maxBusId;
int minCnt = 5001;
Bus busses[5001];
bool visited[5001];

vector<int> getBusList(int row, int col) {
    vector<int> ret;
    for (int i = 1; i <= maxBusId; i++) {
        if (busses[i].isPossible(row, col))
            ret.push_back(i);
    }
    return ret;
}

bool isTransfer(int bus1, int bus2) {
    int direc1 = busses[bus1].direc;
    int direc2 = busses[bus2].direc;

    if (direc1 == VERTI && direc2 == VERTI) {
        if (busses[bus1].startCol != busses[bus2].startCol)
            return false;
        if (busses[bus2].startRow <= busses[bus1].startRow && busses[bus1].startRow <= busses[bus2].endRow)
            return true;
        if (busses[bus2].startRow <= busses[bus1].endRow && busses[bus1].endRow <= busses[bus2].endRow)
            return true;
        if (busses[bus1].startRow <= busses[bus2].startRow && busses[bus2].startRow <= busses[bus1].endRow)
            return true;
        if (busses[bus1].startRow <= busses[bus2].endRow && busses[bus2].endRow <= busses[bus1].endRow)
            return true;
        return false;
    }
    else if (direc1 == VERTI && direc2 == HORI) {
        if (busses[bus1].startCol > busses[bus2].endCol)
            return false;
        if (busses[bus1].startCol < busses[bus2].startCol)
            return false;
        if (busses[bus2].startRow > busses[bus1].endRow)
            return false;
        if (busses[bus2].startRow < busses[bus1].startRow)
            return false;
        return true;
    }
    else if (direc1 == HORI && direc2 == VERTI) {
        if (busses[bus2].startCol > busses[bus1].endCol)
            return false;
        if (busses[bus2].startCol < busses[bus1].startCol)
            return false;
        if (busses[bus1].startRow > busses[bus2].endRow)
            return false;
        if (busses[bus1].startRow < busses[bus2].startRow)
            return false;
        return true;
    }
    else if (direc1 == HORI && direc2 == HORI) {
        if (busses[bus1].startRow != busses[bus2].startRow)
            return false;
        if (busses[bus2].startCol <= busses[bus1].startCol && busses[bus1].startCol <= busses[bus2].endCol)
            return true;
        if (busses[bus2].startCol <= busses[bus1].endCol && busses[bus1].endCol <= busses[bus2].endCol)
            return true;
        if (busses[bus1].startCol <= busses[bus2].startCol && busses[bus2].startCol <= busses[bus1].endCol)
            return true;
        if (busses[bus1].startCol <= busses[bus2].endCol && busses[bus2].endCol <= busses[bus1].endCol)
            return true;
        return false;
    }
}

void calBusList(int bus) {
    for (int i = 1; i <= maxBusId; i++) {
        if (i == bus)
            continue;
        if (isTransfer(bus, i)) 
            busses[bus].busList.insert(i);        
    }
}
class compare {
public:
    bool operator()(const BusState& l1, const BusState& l2) {
        return l1.busCnt > l2.busCnt;
    }
};

int getMinBusCnt(int bus) {
    if (busses[bus].isPossible(endRow, endCol))
        return 1;

    priority_queue<BusState, vector<BusState>, compare> pq;
    visited[bus] = true;
    calBusList(bus);

    for (auto b = busses[bus].busList.begin(); b != busses[bus].busList.end(); b++) {
        int nextBus = *b;
        visited[nextBus] = true;
        BusState newState(2, nextBus);
        pq.push(newState);
    }

    while (!pq.empty()) {
        BusState currBusState = pq.top(); pq.pop();
        if (currBusState.busCnt >= minCnt)
            return minCnt;
        if (busses[currBusState.bus].isPossible(endRow, endCol))
            return currBusState.busCnt;

        calBusList(currBusState.bus);
        for (auto b = busses[currBusState.bus].busList.begin(); b != busses[currBusState.bus].busList.end(); b++) {
            int nextBus = *b;
            if (!visited[nextBus]) {
                visited[nextBus] = true;
                BusState newState(currBusState.busCnt + 1, nextBus);
                pq.push(newState);
            }
        }
    }
    return minCnt;
}

int solve() {
    vector<int> busList = getBusList(startRow, startCol);
    for (int i = 0; i < busList.size(); i++) {
        for (int j = 1; j <= maxBusId; j++)
            visited[j] = false;
        int bus = busList[i];
        int cnt = 5001;
        cnt = getMinBusCnt(bus);
        minCnt = min(cnt, minCnt);
    }
    return minCnt;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%d", &maxBusId);
    for (int i = 1; i <= maxBusId; i++) {
        int id, sr, sc, er, ec;
        scanf("%d %d %d %d %d", &id, &sc, &sr, &ec, &er);
        Bus bus(sr - 1, sc - 1, er - 1, ec - 1);
        busses[id] = bus;
    }
    scanf("%d %d %d %d", &startCol, &startRow, &endCol, &endRow);
    startRow--; startCol--; endRow--; endCol--;
    printf("%d\n", solve());
    return 0;
}
