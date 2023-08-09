#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

const ll INF = 9e18;
const ll p1 = 1e12;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> b(m);
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        for (int j = 0; j < t; j++) {
            int c;
            cin >> c;
            c--;
            b[c].push_back(i);
        }
    }

    vector<int> percent(m);
    for (int i = 0; i < m; i++) {
        cin >> percent[i];
    }

    vector<int> d;
    for (int i = 0; i < (1 << m); i++) {
        int d1 = 0;
        for (int j = 0; j < m; j++) {
            if (i & (1 << j))  {
                d1++;
            }
        }
        if (d1 == k) {
            d.push_back(i);
        }
    }

    vector<ll> d1(n);
    for (int i = 0; i < n; i++) {
        d1[i] = p1 * a[i];
    }
    int ans = 0;
    ll min_cost = INF;
    for (int t : d) {
        vector<ll> d2 = d1;
        for (int j = 0; j < m; j++) {
            if (t & (1 << j)) {
                for (int k1 : b[j]) {
                    d2[k1] -= d2[k1] / 100 * percent[j];
                }
            }
        }
        ll sum = 0;
        for (int j = 0; j < n; j++) {
            sum += d2[j];
        }
        if (sum < min_cost) {
            min_cost = sum;
            ans = t;
        }
    }

    cout << k << "\n";
    for (int i = 0; i < m; i++) {
        if (ans & (1 << i)) {
            cout << i + 1 << " ";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);

    solve();
}