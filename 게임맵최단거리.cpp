#include <vector>
#include <queue>
#include <cmath>
#define MAX 100
using namespace std;

class Loc{
    public:
    int row;
    int col;
    int length;
    int cnt;
    public:
    Loc(int r, int c, int l, int cn){
        row = r;
        col = c;
        length = l;
        cnt = cn;
    }
    Loc(){       
    }
};

class compare{
    public:
    bool operator()(const Loc& l1, const Loc& l2){
#include <vector>
#include <queue>
#include <cmath>
#define MAX 100
using namespace std;

class Loc{
    public:
    int row;
    int col;
    int length;
    int cnt;
    public:
    Loc(int r, int c, int l, int cn){
        row = r;
        col = c;
        length = l;
        cnt = cn;
    }
    Loc(){       
    }
};

class compare{
    public:
    bool operator()(const Loc& l1, const Loc& l2){
        if(l1.cnt == l2.cnt)
            return l1.length > l2.length;
        return l1.cnt > l2.cnt;
    }
};

bool visited[MAX][MAX];
int moveRow[4] = {-1, 0, 1, 0};
int moveCol[4] = {0, 1, 0 ,-1};
int rowSize;
int colSize;

bool isRange(int row, int col){
    if(row < 0 || col < 0)
        return false;
    if(row >= rowSize || col >= colSize)
        return false;
    return true;
}
bool isPossible(int row, int col, const vector<vector<int> >& maps){
    if(maps[row][col] != 0)
        return true;
    return false;
}

int getLength(int row, int col){
    return abs(rowSize - row) + abs(colSize - col);
}

int solution(vector<vector<int> > maps)
{
    priority_queue<Loc, vector<Loc>, compare> pq;
    rowSize = maps.size();    
    colSize = maps[0].size();
    Loc startLoc(0, 0, rowSize + colSize, 1);
    pq.push(startLoc);
    while(!pq.empty()){
        Loc currLoc = pq.top(); pq.pop();
        if(currLoc.row == rowSize - 1 && currLoc.col == colSize - 1)
            return currLoc.cnt;
        
        for(int d=0; d<4; d++){
            int nextRow = currLoc.row + moveRow[d];
            int nextCol = currLoc.col + moveCol[d];
            if(isRange(nextRow, nextCol) && !visited[nextRow][nextCol] && isPossible(nextRow, nextCol, maps)){
                visited[nextRow][nextCol] = true;
                Loc newLoc(nextRow, nextCol, getLength(nextRow, nextCol), currLoc.cnt + 1);
                pq.push(newLoc);
            }
        }
    }
    return -1;                 
}




