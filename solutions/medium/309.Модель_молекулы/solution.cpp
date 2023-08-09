#include <iostream>
#include <vector>
#include <set>

int parent[100001], rank[100001];

void make_set (int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set (int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set (parent[v]);
}

void union_sets (int a, int b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b) {
        if (rank[a] < rank[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        parent[b] = a;
        if (rank[a] == rank[b])
            ++rank[a];
    }
}

using namespace std;

bool dfs(int v, int color, vector<int> &colors, vector<multiset<int>> &graph, bool isFirst) {
    if (colors[v] > 0) {
        return false;
    }
    colors[v] = color;
    bool flag = false;

    if (isFirst) {
        make_set(color);
        flag  = true;
    }

    for (auto u : graph[v]) {
        dfs(u, color, colors, graph, false);
    }
    return flag;
}

int main() {
    int n, m, k, from, to;
    cin >> n >> m;

    vector<multiset<int>> graph(n + 1);
    vector<pair<int, int>> edges(m + 1);

    // creating graph
    for (int i = 1; i < m + 1; i++) {
        cin >> from >> to;
        graph[from].insert(to);
        graph[to].insert(from);
        edges[i] = {from, to};
    }

    // remove edges
    cin >> k;
    vector<int> numOfDeletedEdges(k);
    for (int i = 0; i < k; i++) {
        cin >> from;
        numOfDeletedEdges[i] = from;
        graph[edges[from].first].erase(graph[edges[from].first].find(edges[from].second));
        graph[edges[from].second].erase(graph[edges[from].second].find(edges[from].first));
    }

    vector<int> colors(n + 1);
    int comps = 0;

    // paint all graph
    for (int v = 1; v < n + 1; v++) {
        if (dfs(v, v, colors, graph, true)) {
            comps++;
        }
    }

    auto ans = vector<int>(k);
    // reconstruct graph
    for (int i = k - 1; i >= 0; i--) {
        auto p = edges[numOfDeletedEdges[i]];
        ans[i] = comps;
        if (find_set(colors[p.first]) != find_set(colors[p.second])) {
            union_sets(colors[p.first], colors[p.second]);
            comps--;
        }
    }
    for (auto lol : ans) {
        cout << lol << " ";
    }
    return 0;
}
