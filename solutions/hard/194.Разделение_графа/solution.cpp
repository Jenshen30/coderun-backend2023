#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool dfs(vector<set<pair<int, int>>> &graph, vector<int> &colors, int mid, int v, int color, int n) {
    if (colors[v] != -1) {
        return colors[v] == color;
    }
    colors[v] = color;

    for (auto p : graph[v]) {
        if (p.second <= mid) {
            if (!dfs(graph, colors, mid, p.first, (color + 1) % 2, n)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n, m, max_w = -1;

    cin >> n >> m;
    vector<set<pair<int, int>>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int tmp1, tmp2, w;
        cin >> tmp1 >> tmp2 >> w;
        graph[tmp1].insert({tmp2, w});
        graph[tmp2].insert({tmp1, w});
        max_w = max(max_w, w);
    }

    vector<int> color(n + 1);
    int r = max_w, l = 0;

    while (r - l > 1) {
        int mid = (l + r) / 2;
        fill(color.begin(), color.end(), -1);
        bool ans = true;

        for (int v = 1; v < n + 1; v++) {
            if (color[v] != -1) {continue;}
            ans &= dfs(graph, color, mid, v, 0, n);
            if (!ans) {
                break;
            }
        }

        if (ans) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << r;
}
