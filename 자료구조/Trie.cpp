#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    Node* next[26];
    bool flag;
    Node() {
        for (int i = 0; i < 26; i++)
            next[i] = NULL;
        flag = false;
    }
    void insert(string& str) {
        if (str[0] == 0) {
            flag = true;
            return;
        }
        int alphabet = str[0] - 'a';
        if (next[alphabet] == NULL)
            next[alphabet] = new Node();
        str.erase(str.begin());
        next[alphabet]->insert(str);
    }
    Node* getPrefixNode(string& str) {
        if (str[0] == 0)
            return this;
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    Node* next[26];
    bool flag;
    Node() {
        for (int i = 0; i < 26; i++)
            next[i] = NULL;
        flag = false;
    }
    void insert(string& str) {
        if (str[0] == 0) {
            flag = true;
            return;
        }
        int alphabet = str[0] - 'a';
        if (next[alphabet] == NULL)
            next[alphabet] = new Node();
        str.erase(str.begin());
        next[alphabet]->insert(str);
    }
    Node* getPrefixNode(string& str) {
        if (str[0] == 0)
            return this;
        int alphabet = str[0] - 'a';
        if (next[alphabet] == NULL)
            return NULL;
        str.erase(str.begin());
        return next[alphabet]->getPrefixNode(str);
    }
};

class Trie {
public:
    Node* root;
public:
    Trie() {
        root = NULL;
    }
    void insert(string& str) {
        if (root == NULL)
            root = new Node();
        root->insert(str);
    }
};
