#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

class Bus {
public:
   int id;
   int startRow;
   int startCol;
   int endRow;
   int endCol;
   vector<pair<int, int>> locList;
   set<int> busList;
   bool isCalLocList;
   Bus(int i, int sr, int sc, int er, int ec) {
      isCalLocList = false;
      id = i;
      startRow = sr;
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

class Bus {
public:
   int id;
   int startRow;
   int startCol;
   int endRow;
   int endCol;
   vector<pair<int, int>> locList;
   set<int> busList;
   bool isCalLocList;
   Bus(int i, int sr, int sc, int er, int ec) {
      isCalLocList = false;
      id = i;
      startRow = sr;
      startCol = sc;
      endRow = er;
      endCol = ec;
   }
   Bus() {
      isCalLocList = false;
   }
   //row, col에 있는 승객을 태울수 있는지
   bool isPossible(int row, int col) {
      if (startRow <= row && row <= endRow && startCol <= col && col <= endCol)
         return true;
      return false;
   }
   void calLocList() {
      isCalLocList = true;
      for (int r = startRow; r <= endRow; r++)
         for (int c = startCol; c <= endCol; c++) {
            locList.push_back(make_pair(r, c));
         }
   }
};
class Loc {
public:
   int busCnt;
   int currBus; //현재 탑승한 버스
public:
   Loc(int bc, int cb) {
      busCnt = bc;
      currBus = cb;
   }
};

int n, m;
int k;
int startRow;
int startCol;
int endRow;
int endCol;
static int maxBusId = 0;
static Bus busses[5001];
bool visited[5001];

void pushBus(int row, int col, int currBus) {
   for (int i = 1; i <= maxBusId; i++) {
      if (busses[i].isPossible(row, col) && i != currBus)
         busses[i].busList.insert(currBus);
   }
}

class compare {
public:
   bool operator()(const Loc& l1, const Loc& l2) {
      return l1.busCnt > l2.busCnt;
   }
};

vector<int> getBusList(int row, int col) {
   vector<int> ret;
   for (int i = 1; i <= maxBusId; i++) {
      if (busses[i].isPossible(row, col))
         ret.push_back(i);
   }
   return ret;
}

int minCnt = 5001;
int getMinBusCnt(int bus) {

   visited[bus] = true;
   static priority_queue<Loc, vector<Loc>, compare> pq;

   for (auto b = busses[bus].busList.begin(); b != busses[bus].busList.end(); b++) {
      int currBus = *b;
      visited[currBus] = true;
      Loc newLoc(1, currBus);
      pq.push(newLoc);
   }

   while (!pq.empty()) {
      Loc currLoc = pq.top(); pq.pop();
      if (currLoc.busCnt >= minCnt)
         return minCnt;
      if (busses[currLoc.currBus].isPossible(endRow, endCol))
         return currLoc.busCnt;
      for (auto b = busses[currLoc.currBus].busList.begin(); b != busses[currLoc.currBus].busList.end(); b++) {
         int currBus = *b;
         if (!visited[currBus]) {
            visited[currBus] = true;
            Loc newLoc(currLoc.busCnt + 1, currBus);
            pq.push(newLoc);
         }
      }   
   }
   return 5001;
}

int solve() {
   //startRow, startCol에서 탈 수 있는 버스들을 구해서 타본다.
   for (int i = 1; i < maxBusId; i++) {
      busses[i].calLocList();
      for (int j = 0; j < busses[i].locList.size(); j++) {
         int row = busses[i].locList[j].first;
         int col = busses[i].locList[j].second;
         pushBus(row, col, i);
      }
   }

   vector<int> busList = getBusList(startRow, startCol);
   for (int i = 0; i < busList.size(); i++) {
      for (int j = 0; j < 5001; j++)
         visited[j] = false;
      //row, col에서 i번 버스를 탓을때 최소버스값
      int currBus = busList[i];
      int currCnt = 5001;
      currCnt = 1 + getMinBusCnt(busList[i]);
      minCnt = min(currCnt, minCnt);
   }
   return minCnt;
}

int main() {
   scanf("%d %d", &m, &m);
   scanf("%d", &k);
   for (int i = 0; i < k; i++) {
      int id, sr, sc, er, ec;
      scanf("%d %d %d %d %d", &id, &sc, &sr, &ec, &er);
      Bus bus(id, sr - 1, sc - 1, er - 1, ec - 1);
      busses[id] = bus;
      maxBusId = max(maxBusId, id);
   }
   scanf("%d %d %d %d", &startCol, &startRow, &endCol, &endRow);
   startRow--;
   startCol--;
   endRow--;
   endCol--;
   printf("%d", solve());
   return 0;
}
