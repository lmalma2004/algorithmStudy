#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Node {
public:
    int num;
    Node* left;
    Node* right;
public:
    Node(int n) {
        num = n;
        left = NULL;
        right = NULL;
    }
};

class Tree {
public:
    Node* root;
    Tree() {
        root = NULL;
    }
    void insert(int num) {
        Node* newNode = new Node(num);
        if (root == NULL) {
            root = newNode;
            return;
        }
        if (root->num > num) {
            if (root->left != NULL)
                insert(root->left, newNode);
            else
                root->left = newNode;
        }
        else {
            if (root->right != NULL)
                insert(root->right, newNode);
            else
                root->right = newNode;
        }
    }
    void insert(Node* parent, Node* newNode) {
        if (parent->num > newNode->num) {
            if (parent->left != NULL)
                insert(parent->left, newNode);
            else
                parent->left = newNode;
        }
        else {
            if (parent->right != NULL)
                insert(parent->right, newNode);
            else
                parent->right = newNode;
        }
    }
    int findMax() {
        Node* curr = root;
        while (curr->right != NULL)
            curr = curr->right;
        return curr->num;
    }
    int findMin() {
        Node* curr = root;
        while (curr->left != NULL)
            curr = curr->left;
        return curr->num;
    }
    void popMax() {
        if (root == NULL)
            return;
        Node* curr = root;
        Node* pre = NULL;
        while (curr->right != NULL) {
            pre = curr;
            curr = curr->right;
        }
        if (curr == root) {
            root = curr->left;
            delete curr;
            curr = NULL;
            return;
        }
        pre->right = curr->left;
        delete curr;
        curr = NULL;
    }
    void popMin() {
        if (root == NULL)
            return;
        Node* curr = root;
        Node* pre = NULL;
        while (curr->left != NULL) {
            pre = curr;
            curr = curr->left;
        }
        if (curr == root) {
            root = curr->right;
            delete curr;
            curr = NULL;
            return;
        }
        pre->left = curr->right;
        delete curr;
        curr = NULL;
    }
    bool empty() {
        return root == NULL;
    }
};

int getNumber(string operation) {
    int len = operation.length() - 1;
    int cnt = 0;
    int sum = 0;
    while (operation[len] != ' ') {
        if (operation[len] != '-') {
            sum += (operation[len] - '0') * pow(10, cnt);
            len--;
            cnt++;
        }
        else {
            return -sum;
        }
    }
    return sum;
}

vector<int> solution(vector<string> operations) {
    Tree tree;
    for (int i = 0; i < operations.size(); i++) {
        if (operations[i][0] == 'I') {
            tree.insert(getNumber(operations[i]));
        }
        else if (operations[i][2] == '1') {
            tree.popMax();
        }
        else if (operations[i][2] == '-') {
            tree.popMin();
        }
    }
    vector<int> ret;
    if (tree.empty()) {
        ret.push_back(0);
        ret.push_back(0);
        return ret;
    }
    ret.push_back(tree.findMax());
    ret.push_back(tree.findMin());
    return ret;
}
