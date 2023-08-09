#include <climits>
#include <iostream>
#include <vector>


#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

typedef long long int ll;

void easy() {
    int n, k;
    cin >> n >> k;
    vector<ll> mass(n + 1);
    ll ans = LONG_LONG_MIN;

    vector<vector<ll>> dp_left_side(n + 2, vector<ll>(k + 1)),
            dp_right_side(n + 2, vector<ll>(k + 1));


    for (int i = 0; i < n; i++) {
        cin >> mass[i];
        ans = MAX(ans, mass[i]);
    }

    if (ans <= 0) {
        cout << ans << "\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp_left_side[i][j] = MAX(dp_left_side[i - 1][j] + mass[i - 1], 0ll);
            if (j > 0) {
                dp_left_side[i][j] = MAX(dp_left_side[i][j],
                                         dp_left_side[i - 1][j - 1]);
            }

            ans = MAX(ans, dp_left_side[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp_left_side[i][j] = dp_left_side[i - 1][j] + mass[i - 1];
            if (j > 0) {
                dp_left_side[i][j] = MAX(dp_left_side[i][j], dp_left_side[i - 1][j - 1]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (i > 1) {
                dp_left_side[i][j] = MAX(dp_left_side[i][j],
                                         dp_left_side[i - 1][j]);
            }
            if (j > 0) {
                dp_left_side[i][j] = MAX(dp_left_side[i][j],
                                         dp_left_side[i][j - 1]);
            }
        }
    }

    for (int i = n; i > 0; i--) {
        for (int j = 0; j <= k; j++) {
            dp_right_side[i][j] = dp_right_side[i + 1][j] + mass[i - 1];
            if (j > 0) {
                dp_right_side[i][j] = MAX(dp_right_side[i][j],
                                          dp_right_side[i + 1][j - 1]);
            }
        }
    }

    for (int i = n; i > 0; i--) {
        for (int j = 0; j <= k; j++) {
            if (i < n) {
                dp_right_side[i][j] = MAX(dp_right_side[i][j],
                                          dp_right_side[i + 1][j]);
            }
            if (j > 0) {
                dp_right_side[i][j] = MAX(dp_right_side[i][j],
                                          dp_right_side[i][j - 1]);
            }
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            ans = MAX(ans,
                      dp_left_side[i][j] + dp_right_side[i + 1][k - j]);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (;t > 0;t--) {
        easy();
    }
}