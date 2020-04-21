#include <iostream>
#include <stack>

using namespace std;

class Queue {
public:
	stack<int> s1;
	stack<int> s2;
public:
	void push(int data) {
		s1.push(data);
	}
	bool empty() {
		return s1.empty() && s2.empty();
	}
	int pop() {
		if (!s2.empty()) {
			int ret = s2.top();
			s2.pop();
			return ret;
		}
		if (s1.empty())
			return -1;
		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
		int ret = s2.top();
		s2.pop();
		return ret;
	}
};

int main() {
	Queue q;
	for (int i = 0; i < 10; i++) {
		q.push(i);
	}
	for (int i = 0; i < 5; i++) {
		int front = q.pop();
		cout << front << endl;
	}
	for (int i = 10; i < 15; i++) {
		q.push(i);
	}
	while (!q.empty()) {
		int front = q.pop();
		cout << front << endl;
	}
	
	return 0;
}
