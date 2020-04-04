#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define HORI  0
#define VERTI 1
#define MAX_BUS 5001
using namespace std;

int startRow, startCol;
int endRow, endCol;
int maxBusId = 0;
int minCnt = MAX_BUS;
bool memoCalBusList[MAX_BUS];

class Bus {
public:
   int id;
   int startRow;
   int startCol;
   int endRow;
   int endCol;
   int direc;
   vector<int> busList;
public:
   Bus() {
   }
   Bus(int i, int sc, int sr, int ec, int er) {
      id = i;
      startRow = min(sr, er);
      startCol = min(sc, ec);
      endRow = max(sr, er);
      endCol = max(sc, ec);
      if (sr == er)
         direc = HORI;
      else
         direc = VERTI;
   }
   bool isPossible(int row, int col) {
      if (startRow <= row && row <= endRow && startCol <= col && col <= endCol)
         return true;
      return false;
   }
};
Bus busses[MAX_BUS];

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
         busses[bus].busList.push_back(i);
   }
}
vector<int> getBusList(int row, int col) {
   vector<int> ret;
   for (int i = 1; i <= maxBusId; i++) {
      if (busses[i].isPossible(row, col))
         ret.push_back(i);
   }
   return ret;
}

int getBusCnt(int bus, bool visited[MAX_BUS]) {
   if (busses[bus].isPossible(endRow, endCol))
      return 1;
   if (!memoCalBusList[bus]) {
      memoCalBusList[bus] = true;
      calBusList(bus);
   }
   visited[bus] = true;
   queue<pair<int, int>> q;

   const vector<int>& busList = busses[bus].busList;
   for (int i = 0; i < busList.size(); i++) {
      int nextBus = busList[i];
      visited[nextBus] = true;
      q.push(make_pair(nextBus, 2));
   }

   while (!q.empty()) {
      int currBus = q.front().first;
      int currBusCnt = q.front().second;
      q.pop();

      if (currBusCnt >= minCnt)
         return minCnt;
      if (busses[currBus].isPossible(endRow, endCol))
         return currBusCnt;

      if (!memoCalBusList[currBus]) {
         calBusList(currBus);
         memoCalBusList[currBus] = true;
      }

      const vector<int>& busList = busses[currBus].busList;
      for (int i = 0; i < busList.size(); i++) {
         int nextBus = busList[i];
         if (!visited[nextBus]) {
            visited[nextBus] = true;
            q.push(make_pair(nextBus, currBusCnt + 1));
         }
      }
   }
   return minCnt;
}

int solve() {
   vector<int> busList = getBusList(startRow, startCol);

   for (int i = 1; i <= maxBusId; i++) 
      memoCalBusList[i] = false;
   
   for (int i = 0; i < busList.size(); i++) {
      bool visited[MAX_BUS];
      for (int j = 1; j <= maxBusId; j++)
         visited[j] = false;
      int bus = busList[i];
      int busCnt = getBusCnt(bus, visited);
      if (minCnt > busCnt)
         minCnt = busCnt;
   }
   return minCnt;
}

int main() {
   int m, n;
   scanf("%d %d", &m, &n);
   int k;
   scanf("%d", &k);
   for (int i = 0; i < k; i++) {
      int id, col1, row1, col2, row2;
      scanf("%d %d %d %d %d", &id, &col1, &row1, &col2, &row2);
      Bus bus(id, col1 - 1, row1 - 1, col2 - 1, row2 - 1);
      busses[id] = bus;
      if (maxBusId < id)
         maxBusId = id;
   }
   scanf("%d %d %d %d", &startCol, &startRow, &endCol, &endRow);
   startCol--; startRow--; endCol--; endRow--;
   printf("%d", solve());
   return 0;
}
