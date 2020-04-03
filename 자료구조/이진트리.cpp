#include <iostream>
#include <vector>
#define LEFT  0 
#define RIGHT 1
using namespace std;

class Node {
public:
	int data;
	Node* parent;
	Node* left;
	Node* right;
public:
	Node() {
		parent = NULL;
		left = NULL;
		right = NULL;
	}
	Node(int d) {
		data = d;
		parent = NULL;
		left = NULL;
		right = NULL;
	}
};

class BinaryTree {
public:
	Node* root;
public:
	BinaryTree() {
		root = NULL;
	}
	void insert(int data) {
		Node* newNode = new Node(data);
		if (root == NULL) {
			root = newNode;
			return;
		}
		if (root->data > data) {
			if (root->left == NULL) {
				root->left = newNode;
				newNode->parent = root;
				return;
			}
			insert(root->left, newNode);
		}
		else {
			if (root->right == NULL) {
				root->right = newNode;
				newNode->parent = root;
				return;
			}
			insert(root->right, newNode);
		}
	}
	void insert(Node* curr, Node* newNode) {
		if (curr->data > newNode->data) {
			if (curr->left == NULL) {
				curr->left = newNode;
				newNode->parent = curr;
				return;
			}
			insert(curr->left, newNode);
		}
		else {
			if (curr->right == NULL) {
				curr->right = newNode;
				newNode->parent = curr;
				return;
			}
			insert(curr->right, newNode);
		}
	}
	int getSubTreeCnt(Node* node) {
		if (node->left != NULL && node->right != NULL)
			return 2;
		else if (node->left == NULL && node->right == NULL)
			return 0;
		return 1;
	}
	int getDirec(Node* parent, Node* child) {
		if (parent == NULL)
			return -1;
		if (parent->left == child)
			return LEFT;
		return RIGHT;
	}
	Node* getMinNode(Node* curr) {
		if (curr->left == NULL)
			return curr;
		return getMinNode(curr->left);
	}
	void setChildNode(Node* parent, Node* child, int direc) {
		if (parent == NULL)
			return;
		if (direc == LEFT)
			parent->left = child;
		else
			parent->right = child;		
	}
	//삭제연산 : 3가지 경우, 루트를 지울때
	//1. 삭제할노드의 서브트리가 없는경우
	//2. 삭제할노드의 서브트리가 한개인 경우
	//3. 삭제할노드의 두개인 경우
	void erase(int data) {
		Node* deleteNode = find(root, data);
		Node* parentNode = deleteNode->parent;
		int direc = getDirec(parentNode, deleteNode);
		int subTreeCnt = getSubTreeCnt(deleteNode);

		if (subTreeCnt == 0) {
			setChildNode(parentNode, NULL, direc);
			delete deleteNode;
			deleteNode = NULL;
			if (direc == -1) 
				root = NULL;			
		}
		else if (subTreeCnt == 1) {
			if (deleteNode->left != NULL) {
				deleteNode->left->parent = parentNode;
				setChildNode(parentNode, deleteNode->left, direc);
				if (direc == -1)
					root = deleteNode->left;
			}
			else {
				deleteNode->right->parent = parentNode;
				setChildNode(parentNode, deleteNode->right, direc);
				if (direc == -1)
					root = deleteNode->right;
			}
			delete deleteNode;
			deleteNode = NULL;
		}
		else if (subTreeCnt == 2) {
			//지우려는 데이터 바로 다음데이터를 찾아 노드를 바꿔준다.
			Node* targetNode = getMinNode(deleteNode->right);
			if (targetNode == deleteNode->right) {
				targetNode->left = deleteNode->left;
				deleteNode->left->parent = targetNode;
				setChildNode(parentNode, targetNode, direc);
				targetNode->parent = parentNode;
				delete deleteNode;
				deleteNode = NULL;
			}
			else {
				if (targetNode->right == NULL) {
					targetNode->parent->left = NULL;
				}
				else {
					targetNode->parent->left = targetNode->right;
					targetNode->right->parent = targetNode->parent;
				}
				deleteNode->right->parent = targetNode;
				deleteNode->left->parent = targetNode;
				targetNode->left = deleteNode->left;
				targetNode->right = deleteNode->right;
				setChildNode(parentNode, targetNode, direc);
				targetNode->parent = parentNode;
				delete deleteNode;
				deleteNode = NULL;
			}
			if (direc == -1)
				root = targetNode;
		}
	}
	Node* find(Node* curr, int data) {
		if (curr == NULL)
			return NULL;
		if (curr->data == data)
			return curr;
		if (curr->data > data)
			return find(curr->left, data);
		else
			return find(curr->right, data);
	}
};



int main() {
	//TEST
	BinaryTree binaryTree;
	vector<int> datas;
	for (int i = 0; i < 1000; i++) {
		datas.push_back(rand());
	}
	for (int i = 0; i < 1000; i++) {
		binaryTree.insert(datas[i]);
	}
	for (int i = 999; i >= 0; i--) {
		binaryTree.erase(datas[i]);
	}
	for (int i = 0; i < 1000; i++) {
		binaryTree.insert(datas[i]);
	}
	for (int i = 0; i < 1000; i++) {
		binaryTree.erase(datas[i]);
	}
	return 0;
}
