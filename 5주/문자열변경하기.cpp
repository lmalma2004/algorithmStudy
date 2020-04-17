#include <iostream>
#include <list>
using namespace std;

class Node {
public:
	char c;
	Node* next;
public:
	Node() {
		next = NULL;
	}
	Node(char c_) {
		c = c_;
		next = NULL;
	}
};

class List {
public:
	Node* head;
	Node* rear;
public:
	List() {
		head = NULL;
		rear = NULL;
	}
	void clear() {
		while (head != NULL) {
			Node* deleteNode = head;
			head = head->next;
			delete deleteNode;
			deleteNode = NULL;
		}
		head = NULL;
		rear = NULL;
	}
	void push_back(char c) {
		Node* newNode = new Node(c);
		if (head == NULL) {
			head = newNode;
			rear = head;
			return;
		}
		rear->next = newNode;
		rear = newNode;
	}
	Node* getNode(int loc) {
		Node* curr = head;
		for (int i = 0; i < loc; i++)
			curr = curr->next;
		return curr;
	}
	void swapChar(int loc1, int loc2) {
		Node* node1 = getNode(loc1);
		Node* node2 = getNode(loc2);
		char tmp = node1->c;
		node1->c = node2->c;
		node2->c = tmp;
	}
	void insert(Node** pre, char c, Node** curr) {
		Node* newNode = new Node(c);

		if (*pre == NULL) {
			newNode->next = head;
			head = newNode;			
			*pre = newNode;
			*curr = newNode->next;
			return;
		}
		if (*pre == rear) {
			(*pre)->next = newNode;
			rear = newNode;
			*pre = newNode;
			*curr = newNode->next;
			return;
		}
		newNode->next = (*pre)->next;
		(*pre)->next = newNode;
		*pre = newNode;
		*curr = newNode->next;
	}
	void erase(int loc) {
		Node* deleteNode = head;
		Node* preNode = NULL;
		for (int i = 0; i < loc; i++) {
			preNode = deleteNode;
			deleteNode = deleteNode->next;
		}
		if (deleteNode == head) {
			head = head->next;
			delete deleteNode;
			deleteNode = NULL;
			return;
		}
		if (deleteNode == rear) {
			rear = preNode;
			rear->next = NULL;
			delete deleteNode;
			deleteNode = NULL;
			return;
		}
		preNode->next = deleteNode->next;
		delete deleteNode;
		deleteNode = NULL;
	}
};
int T;
List s;
char t[100001];
char sTmp[100001];

int getSwapCnt(Node* node, char target){
	int cnt = 0;
	while (node != NULL) {
		if (node->c == target)
			return cnt;
		node = node->next;
		cnt++;
	}
	return cnt;
}

int solve() {
	int sum = 0;
	Node* curr = s.head;
	Node* pre = NULL;
	int currLoc = 0;

	while (curr != NULL) {
		if (curr->c != t[currLoc]) {
			int swapCnt = getSwapCnt(curr, t[currLoc]);
			int nextLoc = currLoc + swapCnt;
			s.erase(nextLoc);
			s.insert(&pre, t[currLoc], &curr);
			sum += swapCnt;
		}
		else {
			pre = curr;
			curr = curr->next;
		}
		currLoc++;
	}
	return sum;
}

void setStr(char* sTmp) {
	s.clear();
	int len = 0;
	while (sTmp[len] != '\0') {
		s.push_back(sTmp[len]);
		len++;
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%s", sTmp);
		scanf("%s", t);
		setStr(sTmp);
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
