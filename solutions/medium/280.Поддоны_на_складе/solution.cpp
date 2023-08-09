#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main1() {
    int n, tmp1, tmp2;

    cin >> n;
    vector<pair<int, int>> pallets;
    for (int i = 0; i < n; i++) {
        cin >> tmp1 >> tmp2;
        pallets.emplace_back(tmp1, tmp2);
        pallets.emplace_back(tmp2, tmp1);
    }

    sort(pallets.begin(), pallets.end(),
         [](const pair<int, int> & a, const pair<int, int> & b)
         {
             if (a.second == b.second) {
                 return a.first > b.first;
             }
             return a.second < b.second;
         });

    int ans = 0, max_cur = pallets[pallets.size() - 1].first;
    set<pair<int, int>> already;

    for (int i = pallets.size() - 1; i >= 0; i--) {
        auto p = pallets[i];

        if (p.first >= max_cur && already.count(p) == 0) {
            ans++;
            already.insert({p.second, p.first});
        }
        max_cur = max(max_cur, p.first);
    }
    return ans;
}

int main() {
    cout << main1();
    return 0;
}
/*
5
2 3
3 2
1 5
5 1
2 2
*/