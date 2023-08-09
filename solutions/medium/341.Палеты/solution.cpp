#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct product {
    int delivery_id = -1, parent_id = -1;
};

struct node {
    int delivery_id = -1, id = -1;
    node(int delivery_id, int id) : delivery_id(delivery_id), id(id) {}
};

// dfs(bads, nodes, pallets_ids, already_was, node(products[pallet].delivery_id, pallet), true)
bool dfs(set<int> &bads, set<int> &bad_ids, vector<vector<node>> &nodes, set<int> &pallets_ids, vector<bool> &already_was, node &cur_node, bool isRoot)
{
    if (already_was[cur_node.id] || (pallets_ids.count(cur_node.id) > 0 && !isRoot) ||  bads.count(cur_node.delivery_id) > 0 ||
        bad_ids.count(cur_node.id) > 0) {
        return false;
    }
    already_was[cur_node.id] = true;
    bool res = true;
    for (auto el : nodes[cur_node.id]) {
        res &= dfs(bads, bad_ids, nodes, pallets_ids, already_was, el, false);
        if (!res) {
            return false;
        }
    }
    return res;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<product> products;
    set<int> pallets_ids, bad_ids;

    for (int i = 0; i < n; i++) {
        product p;
        cin >> p.delivery_id;
        products.push_back(p);
    }

    for (int i = 0; i < n; i++) {
        cin >> products.at(i).parent_id;
        if (products.at(i).parent_id == 0) {
            pallets_ids.insert(i + 1);
        }
        if (products.at(i).parent_id == i + 1) {
            bad_ids.insert(i);
        }
    }
    vector<vector<node>> nodes(n + 1);
    for (int i = 0; i < n; i++) {
        int parent = products[i].parent_id;
        nodes[parent].push_back(node(products.at(i).delivery_id, i + 1));
    }

    int bad;

    cin >> bad;
    set<int> bads;
    for (int i = 0; i < bad; i++) {
        int tmp;
        cin >> tmp;
        bads.insert(tmp);
    }
    vector<int> ans;
    vector<bool> already_was(n + 1);

    for (auto pallet : pallets_ids) {
        auto lol = node(products[pallet - 1].delivery_id, pallet);
        if (dfs(bads, bad_ids, nodes, pallets_ids, already_was, lol, true)) {
            ans.push_back(pallet);
        }
    }
    cout << ans.size() << "\n";
    for (auto el : ans) {
        cout << el << " ";
    }
}
/*
5
3 4 4 4 4
0 0 0 0 0
1
4
-> 1
   1


5
1 1 1 1000 1000
0 1 1 0 4
0


5
1 1 1 1 2
0 0 0 0 0
0
*/
