#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <map>


#define ll long long int

using namespace std;

int main() {
    ll tmp1, n, tmp2;
    cin >> n;
    map<ll, deque<pair<ll, ll>>> indAndCategories1;

    for (int i = 0; i < n; i++) {
        cin >> tmp1 >> tmp2;
        bool flag = true;
        indAndCategories1[tmp2].push_back({tmp1, tmp2});
    }

    vector<deque<pair<ll, ll>>> indAndCategories;

    for (auto it = indAndCategories1.begin(); it != indAndCategories1.end(); ++it) {
        indAndCategories.push_back(it->second);
    }

    sort(indAndCategories.begin(), indAndCategories.end(),
         [](const  deque<pair<ll, ll>>& a, const deque<pair<ll, ll>> & b) -> bool {
             return a.size() > b.size();
         });

    int qq = indAndCategories[0].size();
    vector<deque<pair<ll, ll>>> stable_deques(qq);

    for (int i = 0; i < qq; i++) {
        stable_deques[i].push_back(indAndCategories[0].front());
        indAndCategories[0].pop_front();
    }


    int j = 0;

    for (int i = 1; i < indAndCategories.size(); i++) {
        while (!indAndCategories[i].empty()) {
            auto tmp = indAndCategories[i].front();
            indAndCategories[i].pop_front();

            if (!stable_deques[j].empty() && stable_deques[j].back().second == tmp.second) {
                j = qq - 1;
                stable_deques[j].push_back(tmp);
                j = 0;
            } else {
                stable_deques[j].push_back(tmp);
                if (qq - 1 > 0) {
                    j = (j + 1) % (qq - 1);
                } else {
                    j = 0;
                }
            }

        }
    }

    for (auto &el : stable_deques) {
        while (!el.empty()) {
            auto tmp = el.front();
            el.pop_front();
            cout << tmp.first << " ";
        }
    }
}

/*
10
1 400
2 100
3 300
4 500
5 200
6 300
7 200
8 500
9 400
10 300

3 1 4 5 6 9 8 7 10 2 (минимальное расстояние 4)
———
9
1 900
2 600
3 800
4 200
5 900
6 400
7 200
8 700
9 100

1 4 2 3 6 8 9 5 7 (минимальное расстояние 7)
*/
