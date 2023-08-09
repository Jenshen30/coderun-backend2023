#include <vector>
#include <iostream>

using namespace std;

class Node {
public:
    int value;
    int key;
    int priority;
    Node* leftnode;
    Node* rightnode;
    Node* parent;

    Node(int value, int key, int priority) {
        this->value = value;
        this->key = key;
        this->priority = priority;
        this->leftnode = nullptr;
        this->rightnode = nullptr;
        this->parent = nullptr;
    }
};

void calc(Node* v) {
    int tmp = 1;
    if (v->rightnode != nullptr) {
        tmp += v->rightnode->key;
    }
    if (v->leftnode != nullptr) {
        tmp += v->leftnode->key;
    }
    v->key = tmp;
}

std::pair<Node*, Node*> split(Node* v, int summary) {
    if (v == nullptr) {
        return {nullptr, nullptr};
    }

    int lkey = 0;
    if (v->leftnode != nullptr) {
        lkey = v->leftnode->key;
    }

    if (lkey >= summary) {
        auto lr = split(v->leftnode, summary);
        Node* l = lr.first;
        Node* r = lr.second;

        if (r != nullptr) {
            r->parent = v;
        }
        v->leftnode = r;

        if (l != nullptr) {
            l->parent = nullptr;
        }
        calc(v);
        return {l, v};
    }

    auto lr = split(v->rightnode, summary - lkey - 1);
    Node* l = lr.first;
    Node* r = lr.second;

    if (l != nullptr) {
        l->parent = v;
    }
    if (r != nullptr) {
        r->parent = nullptr;
    }
    v->rightnode = l;
    calc(v);
    return {v, r};
}

Node* merge(Node* old, Node* another) {
    if (old == nullptr) {
        return another;
    }
    if (another == nullptr) {
        return old;
    }
    if (old->priority > another->priority) {
        Node* tmp = merge(old->rightnode, another);
        if (tmp != nullptr) {
            tmp->parent = old;
        }
        old->rightnode = tmp;
        calc(old);
        return old;
    }
    Node* tmp = merge(old, another->leftnode);
    if (tmp != nullptr) {
        tmp->parent = another;
    }
    another->leftnode = tmp;
    calc(another);
    return another;
}

vector<int> randoms;
vector<Node*> mp;
vector<int> q;

Node* creating(int l, int r) {
    if (l - r == 0) {
        return NULL;
    }
    if (l - r == 1) {
        mp[q[r]] = new Node(q[r], 1, randoms[r]);
        return mp[q[r]];
    }
    int index = -1;
    int maxi = -1;
    for (int i = l; i < r; i++) {
        if (maxi < randoms[i]) {
            maxi = randoms[i];
            index = i;
        }
    }
    mp[q[index]] = new Node(q[index], -1, randoms[index]);
    Node* tmp = creating(l, index);
    if (tmp != NULL) {
        tmp->parent = mp[q[index]];
    }
    mp[q[index]]->leftnode = tmp;
    tmp = creating(min(index + 1, r), r);
    if (tmp != NULL) {
        tmp->parent = mp[q[index]];
    }
    mp[q[index]]->rightnode = tmp;
    calc(mp[q[index]]);
    return mp[q[index]];
}

Node* numToStart(int num, Node* root) {
    mp[num] = new Node(num, 1, rand() % 100000 + 1);
    auto tmp = split(root, 0);
    Node* partwith, *partno;
    partwith = tmp.first;
    partno = tmp.second;
    auto tmp1 = merge(partwith, mp[num]);
    return merge(tmp1, partno);
}

Node* delNumInPosition(int ind, Node* root) {
    auto tmp = split(root, ind);
    Node *partwith, *partno;
    partwith = tmp.first;
    partno = tmp.second;
    tmp = split(partwith, ind - 1);
    return merge(tmp.first, partno);
}

int findInd(Node* node, bool isRight) {
    if (node == NULL) {
        return 0;
    }

    int tmp = 0;
    if (isRight) {
        tmp = 1 + (node->leftnode == NULL ? 0 : node->leftnode->key);
    }

    if (node->parent != NULL && node->parent->rightnode == node) {
        return tmp + findInd(node->parent, true);
    }
    return tmp + findInd(node->parent, false);
}

int getValue(int key, Node* node) {
    int realInd = (node == NULL || node->leftnode == NULL) ? 0 : node->leftnode->key;
    if (realInd + 1 == key) {
        return node->value;
    }
    if (realInd + 1 > key) {
        return getValue(key, node->leftnode);
    }
    return getValue(key - 1 - realInd, node->rightnode);
}

void code(vector<int> &vec, Node *root) {
    for (int i : vec) {
        int pos = findInd(mp[i], true);
        cout << pos << " ";
        root = delNumInPosition(pos, root);
        root = numToStart(i, root);
    }
}

void decode(vector<int> &vec, Node* root) {
    for (int i : vec) {
        int val = getValue(i, root);
        cout << val << " ";
        root = delNumInPosition(i, root);
        root = numToStart(val, root);
    }
}

int main() {
    int n, k, opType;
    cin >> n >> k >> opType;
    q.resize(k);
    mp.resize(k + 1);
    randoms.resize(k);

    for (int i = 1; i <= k; i++) {
        q[i - 1] = i;
        randoms[i - 1] = rand() % 100000 + 1;
    }
    auto root = creating(0, k);
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    if (opType == 1) {
        code(v, root);
    } else {
        decode(v, root);
    }
    return 0;
}