#include <bits/stdc++.h>

using namespace std;
using graph = vector<vector<int>>;
using v_i = vector<int>;
using v_b = vector<bool>;
using pii = pair<int,int>;
using ll = int64_t;
using ull = uint64_t;
using ld = long double;
using ui = unsigned int;

const int inf = 2e9;
const ll INF = 1e18;
const int mod = 1e9 + 7;
const int MOD = 998244353;
const int MOD1 = 104857601;
const double eps = 1e-10;
const int p = 31;

bool found = false;

map<pair<int, int>, bool> dp;


bool f(vector<pair<int,int>> &a, int mul, int ind, int k) {
    if (mul == 1 && k == 0 && !found) {
        cout << a[ind].second + 1 << " ";
        found = true;
        dp[{mul, ind}] = true;

        return true;
    }

    if (dp.contains({mul, ind})) {
        return dp.at({mul, ind});
    }

    if (k == 0) {
        dp[{mul, ind}] = false;
        return false;
    }

    bool st = false;
    for (int i = ind + 1;i < a.size();i++) {
        if (mul % a[i].first == 0) {
            st |= f(a,mul / a[i].first,i,k - 1);
        }
        if (st) break;
    }

    if (st) cout << a[ind].second + 1 << " ";
    dp[{mul, ind}] = st;
    return st;
}

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    if (m == 0) {
        int c = 0;
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            if (t == 0) c = i;
        }
        for (int i = 0; i < k; i++) cout << (c + i) % n + 1 << " ";
    }
    else {
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            if (m % t == 0) {
                a.emplace_back(t, i);
            }
        }
        sort(a.begin(), a.end(), [](const pair<int, int> &p1, const pair<int, int> &p2){return p1 < p2;});

        for (int i = 0; i < a.size(); i++) {
            if (f(a, m / a[i].first, i, k - 1)) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);

    int t1 = 1;
    for (int i = 1;i <= t1;i++) {
        solve();
    }
    return 0;
}