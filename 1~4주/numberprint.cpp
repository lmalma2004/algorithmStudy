#include <iostream>
#include <vector>
#include <string>
using namespace std;

int N;
string DIREC;

class Number {
public:
	int num;
	int rowSize;
	int colSize;
public:
	Number(int n, int rs, int cs) {
		num = n;
		rowSize = rs;
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int N;
string DIREC;

class Number {
public:
	int num;
	int rowSize;
	int colSize;
public:
	Number(int n, int rs, int cs) {
		num = n;
		rowSize = rs;
		colSize = cs;
	}
};
class NumberPrint {
public:
	int maxRow;
	int maxCol;
	int allCol;
	vector<Number> numbers;
	vector<vector<bool>> board;
public:
	NumberPrint() {
		maxCol = 0;
	}
public:
	void push(Number number) {
		numbers.push_back(number);
		allCol += number.colSize + 1;
	}
	void makeBoard() {
		board.resize(maxRow);
		allCol--;
		for (int i = 0; i < board.size(); i++)
			board[i].resize(allCol, false);		
	}
	void printNumOnBoard(int col, int idx) {
		if (DIREC == "TOP")
			printNumOnBoardTop(col, idx);	
		else if (DIREC == "BOTTOM")
			printNumOnBoardBottom(col, idx);		
		else if (DIREC == "MIDDLE")
			printNumOnBoardMiddle(col, idx);
	}
	void drawHori(int row, int beginCol, int endCol) {
		for (int i = beginCol; i < endCol; i++)
			board[row][i] = true;
	}
	void drawVerti(int beginRow, int endRow, int col) {
		for (int i = beginRow; i < endRow; i++)
			board[i][col] = true;
	}
	void printNumOnBoardTop(int col, int idx) {
		int num = numbers[idx].num;
		int rowSize = numbers[idx].rowSize;
		int colSize = numbers[idx].colSize;
		if (num == 0) {
			drawHori(0, col, col + colSize);
			drawHori(rowSize - 1, col, col + colSize);
			drawVerti(0, 0 + rowSize, col);
			drawVerti(0, 0 + rowSize, col + colSize - 1);
		}
		else if (num == 1) {
			drawVerti(0, 0 + rowSize, col + colSize - 1);
		}
		else if (num == 2) {
			int midRow = rowSize / 2;
			drawHori(0, col, col + colSize);
			drawHori(midRow, col, col + colSize);
			drawHori(rowSize - 1, col, col + colSize);
			drawVerti(0, midRow, col + colSize - 1);
			drawVerti(midRow, rowSize, col);
		}
		else if (num == 3) {
			int midRow = rowSize / 2;
			drawHori(0, col, col + colSize);
			drawHori(midRow, col, col + colSize);
			drawHori(rowSize - 1, col, col + colSize);
			drawVerti(0, 0 + rowSize, col + colSize - 1);
		}
		else if (num == 4) {
			int midRow = rowSize / 2;
			drawVerti(0, midRow, col);
			drawVerti(0, 0 + rowSize, col + colSize - 1);
			drawHori(midRow, col, col + colSize);
		}
		else if (num == 5) {
			int midRow = rowSize / 2;
			drawHori(0, col, col + colSize);
			drawHori(midRow, col, col + colSize);
			drawHori(rowSize - 1, col, col + colSize);
			drawVerti(0, midRow, col);
			drawVerti(midRow, rowSize, col + colSize - 1);
		}
		else if (num == 6) {
			int midRow = rowSize / 2;
			drawVerti(0, 0 + rowSize, col);
			drawVerti(midRow, rowSize, col + colSize - 1);
			drawHori(midRow, col, col + colSize);
			drawHori(rowSize - 1, col, col + colSize);
		}
		else if (num == 7) {
			drawHori(0, col, col + colSize);
			drawVerti(0, rowSize, col + colSize - 1);			
		}
		else if (num == 8) {
			int midRow = rowSize / 2;
			drawHori(0, col, col + colSize);
			drawHori(rowSize - 1, col, col + colSize);
			drawHori(midRow, col, col + colSize);
			drawVerti(0, 0 + rowSize, col);
			drawVerti(0, 0 + rowSize, col + colSize - 1);
		}
		else if (num == 9) {
			int midRow = rowSize / 2;
			drawHori(0, col, col + colSize);
			drawHori(midRow, col, col + colSize);
			drawVerti(0, rowSize, col + colSize - 1);
			drawVerti(0, midRow, col);
		}
	}
	void printNumOnBoardBottom(int col, int idx) {
		//귀찮
	}
	void printNumOnBoardMiddle(int col, int idx) {
		//귀찮
	}
	void printBoard() {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				if (board[i][j])
					cout << "#";
				else
					cout << ".";
			}
			cout << endl;
		}
	}
	void printAll() {
		int currCol = 0;
		for (int i = 0; i < numbers.size(); i++) {
			printNumOnBoard(currCol, i);
			currCol += numbers[i].colSize + 1;
		}
		printBoard();
	}
};
NumberPrint NP;

int main() {
	cin >> N;
	cin >> DIREC;
	for (int i = 0; i < N; i++) {
		int colSize; string numbers;
		cin >> colSize;
		cin >> numbers;
		for (int j = 0; j < numbers.length(); j++) {
			int number = numbers[j] - '0';
			int rowSize = (2 * colSize) - 1;
			Number newNumber(number, rowSize, colSize);
			NP.push(newNumber);
			if (NP.maxCol < colSize) {
				NP.maxCol = colSize;
				NP.maxRow = rowSize;
			}
		}
	}
	NP.makeBoard();
	NP.printAll();
	return 0;
}
