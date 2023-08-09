#include <iostream>

class AVLTree
{
    struct Node
    {
        Node * left = nullptr;
        Node * right = nullptr;
        int height = 1;
        int realheight = 1;
        int value;

        Node(int value)
            : value(value){};

        ~Node()
        {
            delete left;
            delete right;
        }
    };

    using NodePtr = Node *;

    static int height(NodePtr node);
    static int realheight(NodePtr node);
    static void recalc_height(NodePtr node);

    static int get_balance(NodePtr node);

    static void detach_children(NodePtr node);

    static void fix_height(NodePtr node);

    static NodePtr rotate_left(NodePtr old_root);
    static NodePtr rotate_right(NodePtr old_root);

    static NodePtr rebalance(NodePtr node);

    static NodePtr min_node(NodePtr current);

    static bool recursive_insert(NodePtr & node, int value);
    static bool recursive_remove(NodePtr & node, int value);

    NodePtr root = nullptr;

public:
    AVLTree() = default;

    bool insert(int value);
    bool remove(int value);

    int kmax(int k);

    ~AVLTree();
};


int AVLTree::get_balance(AVLTree::NodePtr const node)
{
    return node != nullptr ? height(node->left) - height(node->right) : 0;
}
void AVLTree::detach_children(AVLTree::NodePtr node)
{
    node->left = node->right = nullptr;
}
void AVLTree::fix_height(AVLTree::NodePtr node)
{
    node->height = 1 + std::max(height(node->left), height(node->right));
}

void AVLTree::recalc_height(AVLTree::NodePtr node)
{
    node->realheight = 1 + realheight(node->left) +  realheight(node->right);
}

int AVLTree::realheight(AVLTree::NodePtr const node)
{
    return node != nullptr ? node->realheight : 0;
}

int AVLTree::height(AVLTree::NodePtr const node)
{
    return node != nullptr ? node->height : 0;
}

AVLTree::NodePtr AVLTree::rotate_left(AVLTree::NodePtr old_root)
{
    Node * new_root = old_root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    recalc_height(old_root);
    recalc_height(new_root);
    fix_height(old_root);
    fix_height(new_root);
    return new_root;
}

AVLTree::NodePtr AVLTree::rotate_right(AVLTree::NodePtr old_root)
{
    Node * new_root = old_root->right;
    old_root->right = new_root->left;
    new_root->left = old_root;
    recalc_height(old_root);
    recalc_height(new_root);
    fix_height(old_root);
    fix_height(new_root);
    return new_root;
}

AVLTree::NodePtr AVLTree::min_node(AVLTree::NodePtr current)
{
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

AVLTree::NodePtr AVLTree::rebalance(AVLTree::NodePtr node)
{
    int current_balance = get_balance(node);
    if (current_balance > 1) {
        if (get_balance(node->right) < 0) {
            node->right = rotate_right(node->right);
        }

        node = rotate_left(node);
    }
    else if (current_balance < -1) {
        if (get_balance(node->left) > 0) {
            node->left = rotate_left(node->left);
        }

        node = rotate_right(node);
    }
    fix_height(node);
    recalc_height(node);
    return node;
}


int AVLTree::kmax(int k)
{
    NodePtr curr_node = this->root;
    int count;

    for(;;)
    {
        if (curr_node == nullptr)
        {
            return -1;
        }
        count = 1 + realheight(curr_node->right);
        if (count < k)
        {
            curr_node = curr_node->left;
            k -= count;
        } else
        {
            if (count > k)
            {
                curr_node = curr_node->right;
            } else
            {
                return curr_node->value;
            }
        }
    }
}

bool AVLTree::recursive_insert(AVLTree::NodePtr & node, int value)
{
    bool success;
    if (node == nullptr) {
        node = new Node(value);
        return true;
    }
    else if (value < node->value) {
        success = recursive_insert(node->left, value);
    }
    else if (value > node->value) {
        success = recursive_insert(node->right, value);
    }
    else {
        return false;
    }

    node = rebalance(node);

    return success;
}

bool AVLTree::insert(const int value)
{
    return recursive_insert(root, value);
}

bool AVLTree::recursive_remove(AVLTree::NodePtr & node, int value)
{
    bool success = true;
    if (node == nullptr) {
        return false;
    }
    else if (value < node->value) {
        success = recursive_remove(node->left, value);
    }
    else if (value > node->value) {
        success = recursive_remove(node->right, value);
    }
    else if (node->left == nullptr && node->right == nullptr) {
        delete node;
        node = nullptr;
        return true;
    }
    else if (node->left == nullptr || node->right == nullptr) {
        Node * child = (node->left == nullptr) ? node->right : node->left;
        *node = *child;
        detach_children(child);
        delete child;
    }
    else {
        Node * subtree_min = min_node(node->right);
        node->value = subtree_min->value;
        recursive_remove(node->right, node->value);
    }

    node = rebalance(node);

    return success;
}

bool AVLTree::remove(const int value)
{
    return recursive_remove(root, value);
}



AVLTree::~AVLTree()
{
    delete root;
}

int main()
{
    AVLTree tree;
    int n, el;
    long long ans = 0;

    std::cin >> n;
    for (int i = 1; i < n + 1; i++)
    {
        std::cin >> el;

        if (!tree.insert(el))
        {
            return -1;
        }

        if (i % 2 == 0)
        {
            ans += tree.kmax(i / 2 + 1);
        } else
        {
            ans += tree.kmax( (i + 1) / 2);
        }
    }
    std::cout << ans;
}
/*
10
5 10 8 1 7 3 9 6 2 4
 -> 59
*/