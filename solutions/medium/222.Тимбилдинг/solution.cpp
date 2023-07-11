#include <iostream>
#include <vector>

using namespace std;

bool dfs(int v, int color, int n, vector<vector<bool>> &graph, vector<int> &colors) {
    if (colors[v] > 0) {
        if (colors[v] != color) {
            return false;
        }
        return true;
    }
    colors[v] = color;

    bool flag = true;
    for (int u = 1; u < n + 1; u++) {
        if (!flag) {
            return false;
        }
        if (graph[v][u]) {
            flag &= dfs(u, 2 - color + 1, n, graph, colors);
        }
    }
    return flag;
}
void check(vector<vector<bool>> &graph, vector<int> &colors) {
    for (int v = 1; v < colors.size(); v++) {
        for (int u = v + 1; u < colors.size(); u++) {
            if (graph[v][u] && colors[v] == colors[u]) {
                cout << "kkfflfl";
            }
        }
    }
}
int main() {
    int n, m, from, to;
    cin >> n >> m;

    vector<vector<bool>> graph(n + 1, vector<bool> (n + 1, true));

    for (int i = 1; i < n + 1; i++) {
        graph[i][i] = false;
    }

    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph[from][to] = graph[from][to] & false;
        graph[to][from] = graph[to][from] & false;
    }

    vector<int> colors(n + 1);
    bool isOk = dfs(1, 1, n, graph, colors);
    for (int v = 1; v < n + 1; v++) {
        if (colors[v] == 0) {
            isOk &= dfs(v, 2, n, graph, colors);
        }
    }

    if (isOk) {
        int c = 0;
        check(graph, colors);
        for (auto color : colors) {
            if (color == 1) {
                c++;
            }
        }
        cout << c << "\n";
        for (int v = 1; v < n + 1; v++) {
            if (colors[v] == 1) {
                cout << v << " ";
            }
        }
        cout << "\n";
        for (int v = 1; v < n + 1; v++) {
            if (colors[v] == 2) {
                cout << v << " ";
            }
        }

    } else {
        cout << -1;
    }
}
/*
3 1
1 2


*/