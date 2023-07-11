#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#define ll long long

using namespace std;

ll sum(vector<pair<long long, long long>> &vec, map<long long, long long> &mp, ll from, ll to) {
    ll acc = 0;
    for (ll i = from; i < to; i++) {
        auto p = vec.at(i);
        acc += mp.at(p.second);
    }
    return acc;
}

void createCorrectHeap(set<pair<long long, long long>> &heap, vector<pair<long long, long long>> sorted, ll from, ll to) {
    for (ll i = from; i < to; i++) {
        heap.insert(sorted[i]);
    }
}


int main() {
    ll n, tmp, q;
    cin >> n;

    vector<pair<long long, long long>> save_res(n);
    map<long long, long long> numToFirstWeight, numToSecondWeight;

    for (ll i = 0; i < n; i++) {
        cin >> save_res[i].first;
        save_res[i].second = i + 1;
        numToFirstWeight[i + 1] = save_res[i].first;
    }

    for (ll i = 0; i < n; i++) {
        cin >> tmp;
        numToSecondWeight[i + 1] = tmp;
        save_res[i].first -= tmp;
    }

    // first to second set, others to first
    sort(save_res.begin(), save_res.end());

    // value who
    set<pair<ll, ll>> second_set;
    set<pair<ll, ll>> first_set;

    ll sum_first, sum_second;
    createCorrectHeap(first_set, save_res, save_res.size() / 2, save_res.size());
    sum_first = sum(save_res, numToFirstWeight, save_res.size() / 2, save_res.size());

    createCorrectHeap(second_set, save_res, 0, save_res.size() / 2);
    sum_second = sum(save_res, numToSecondWeight, 0, save_res.size() / 2);

    ll id, skillId, addition;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        cin >> id >> skillId >> addition;
        pair<ll, ll> mini;

        if (second_set.count({numToFirstWeight.at(id) - numToSecondWeight.at(id), id}) > 0) {
           second_set.erase({numToFirstWeight.at(id) - numToSecondWeight.at(id), id});
           sum_second -= numToSecondWeight.at(id);
           if (skillId == 2) {numToSecondWeight.find(id)->second += addition;} else {numToFirstWeight.find(id)->second += addition;}

           mini = *first_set.begin();
           first_set.erase(mini);
           sum_first -= numToFirstWeight.at(mini.second);
        } else {
            first_set.erase({numToFirstWeight.at(id) - numToSecondWeight.at(id), id});
            sum_first -= numToFirstWeight.at(id);
            if (skillId == 2) {numToSecondWeight.find(id)->second += addition;} else {numToFirstWeight.find(id)->second += addition;}

            mini = *second_set.rbegin();
            second_set.erase(mini);
            sum_second -= numToSecondWeight.at(mini.second);
        }

        if (numToFirstWeight.at(mini.second) + numToSecondWeight.at(id) <=
            numToSecondWeight.at(mini.second) + numToFirstWeight.at(id)) {

            second_set.insert({numToFirstWeight.at(mini.second) - numToSecondWeight.at(mini.second), mini.second});
            sum_second += numToSecondWeight.at(mini.second);

            first_set.insert({numToFirstWeight.at(id) - numToSecondWeight.at(id), id});
            sum_first += numToFirstWeight.at(id);
        } else {
            second_set.insert({numToFirstWeight.at(id) - numToSecondWeight.at(id), id});
            sum_second += numToSecondWeight.at(id);

            first_set.insert({numToFirstWeight.at(mini.second) - numToSecondWeight.at(mini.second), mini.second});
            sum_first += numToFirstWeight.at(mini.second);
        }
        cout << sum_second + sum_first << "\n";
    }
}
/*
4
7 15 3 4
10 10 0 6
3
1 1 4
4 1 6
2 2 10

34
35
43
*/