#include <iostream>
#include <vector>
#include <set>

#define BIG_NUM 1000002

using namespace std;

class Node {
public:
    vector<Node *>children = vector<Node*>(27);
    int terms;
    bool isTerm;

    Node() {
        terms = 0;
        isTerm = false;
    }
    void createNodes() {

    }

    Node* getChild(char ch) {
        return children[ch - 'a'];
    }
    void setChild(char  ch, Node *node) {
        if (children[ch - 'a'] == nullptr) {
            children[ch - 'a'] = node;
        }
    }
};

bool checkWas(string &word, Node *node, int ind) {
    if (node == nullptr) {
        return false;
    }
    if (ind < word.size() - 1) {
        return checkWas(word, node->getChild(word.at(ind)), ind + 1);
    }
    return node->getChild(word[ind]) != nullptr &&\
        node->getChild(word[ind])->isTerm;
}

int add(string &word, Node *node, int ind) {
    if (node == nullptr || ind == word.size()) {
        return 0;
    }
    Node *nextnode = nullptr;

    if (ind < word.size()) {
        nextnode = node->getChild(word[ind]);
    }
    int term = 0;
    if (nextnode == nullptr) {
        nextnode = new Node();
        node->setChild(word[ind], nextnode);
    }

    if (ind == word.size() - 1 && !node->getChild(word[ind])->isTerm) {
        node->getChild(word[ind])->terms++;
        node->getChild(word[ind])->isTerm = true;
        term = 1;
    }
    int tmp = add(word, nextnode, ind + 1);
    node->terms += tmp + term;
    return tmp + term;
}

int find(string &word, Node *node, int ind) {
    if (ind == word.size() + 1) {
        return ind - 1;
    }
    if (node->terms > 1) {
        return find(word, node->getChild(word[ind]), ind + 1);
    }
    return ind;
}


int main() {
    int n, ans = 0;
    string tmp;

    cin >> n;
    auto root = new Node();

    for (int i = 0; i < n; i++) {
        cin >> tmp;
        root->terms = BIG_NUM;
        if (checkWas(tmp, root, 0)) {
            ans += find(tmp, root, 0);
        } else {
            add(tmp, root, 0);
            ans += (int) tmp.size();
        }
    }

    cout << ans;
}
