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

vector<ull> fact(251,1), rev_fact(251,1);

ull bin_pow_mod(ull a, int pow, int m) {
    ull res = 1;
    while (pow) {
        if (pow % 2) res = (res * a) % m;
        a = (a * a) % m;
        pow /= 2;
    }
    return res;
}

void preculc() {
    for (int i = 1;i <= 250;i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        rev_fact[i] = bin_pow_mod(fact[i],mod - 2,mod);
    }
}

ull c(int k,int n) {
    return (fact[n] * ((rev_fact[n - k] * rev_fact[k]) % mod)) % mod;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    int sum = 0;
    for (int i = 0;i < n;i++) {
        cin >> a[i];
        sum += a[i];
    }

    // c[k][n] = fact[n] * rev_fact[n - k] * rev_fact[k]
    vector<vector<vector<ull>>> dp_1(sum / 2 + 1,vector<vector<ull>>(n + 1, vector<ull>(n + 1,inf)));
    queue<vector<int>> q_1;
    q_1.push({0,0,0});
    dp_1[0][0][0] = 1;
    int cur_sum = 0;
    for (int step = 0;step < n;step++) {
        vector<vector<vector<ull>>> dp_2(sum / 2 + 1,vector<vector<ull>>(n + 1, vector<ull>(n + 1,inf)));
        queue<vector<int>> q_2;

        while (!q_1.empty()) {
            vector<int> conf = q_1.front();
            q_1.pop();
            for (int i = 0;i <= a[step];i++) {
                bool d1 = i;
                bool d2 = (a[step] - i);
                if (conf[0] + i <= sum / 2) {
                    if (dp_2[conf[0] + i][conf[1] + d1][conf[2] + d2] == inf) {
                        dp_2[conf[0] + i][conf[1] + d1][conf[2] + d2] = 0;
                        q_2.push({conf[0] + i, conf[1] + d1, conf[2] + d2});
                    }
                    dp_2[conf[0] + i][conf[1] + d1][conf[2] + d2] =
                            (dp_2[conf[0] + i][conf[1] + d1][conf[2] + d2] +
                             ((dp_1[conf[0]][conf[1]][conf[2]] *
                               ((c(i, i + conf[0]) * c(a[step] - i, a[step] - i + cur_sum - conf[0])) % mod)) % mod)) % mod;
                }
            }
        }

        /*
        queue<vector<int>> q3;
        while (!q_2.empty()) {
            vector<int> conf = q_2.front();
            q3.push(conf);
            q_2.pop();
        }
        */
        dp_1 = dp_2;
        q_1 = q_2;
        cur_sum += a[step];
    }

    ull r1 = 0;
    ull q1 = 0;
    while (!q_1.empty()) {
        vector<int> conf = q_1.front();
        q_1.pop();
        if (conf[0] != sum / 2) continue;
        q1 = (q1 + dp_1[conf[0]][conf[1]][conf[2]]) % mod;
        if (conf[1] == conf[2]) r1 = (r1 + dp_1[conf[0]][conf[1]][conf[2]]) % mod;
    }
    cout << (r1 * bin_pow_mod(q1,mod - 2,mod)) % mod << "\n";
}

int main() {
    preculc();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    //string input;
    int t1 = 1;
    //cin >> t1;
    //getline(cin,input);
    //t1 = stoi(input);
    for (int i = 1;i <= t1;i++) {
        //cout << "Game " << i << "\n";
        solve();
    }
    return 0;
}
