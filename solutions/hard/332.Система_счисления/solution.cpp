#include <bits/stdc++.h>

#define MAX(a, b) (a > b ? a : b)

using namespace std;
using graph = vector<vector<int>>;
using v_i = vector<int>;
using v_b = vector<bool>;
using pii = pair<int,int>;
using ll = int64_t;
using ull = uint64_t;
using ld = long double;
using ui = unsigned int;


int MIN_LIMIT = 1;

int convert(char ch) {
    if (isalpha(ch)) {
        return ch - 'A' + 10;
    }
    return ch - '0';
}

void addNumToMass(string &numS, vector<int> &mass) {
    for (int i = numS.size() - 1; i >= 0; i--) {
        mass[numS.size() - 1 - i] += convert(numS[i]);
        MIN_LIMIT = max(MIN_LIMIT, convert(numS[i]));
    }
}



void subNumToMass(string &numS, vector<int> &mass) {
    for (int i = numS.size() - 1; i >= 0; i--) {
        mass[numS.size() - 1 - i] -= convert(numS[i]);
        MIN_LIMIT = max(MIN_LIMIT, convert(numS[i]));
    }
}

vector<int> generDivisors(int n1) {

    int n = abs(n1);
    vector<int> ans;

    for (int i = 1; i < (int) sqrt(n) + 1; i++) {

        if (n % i == 0 && i != 1) {
            ans.push_back(i);
        }

        if (n % (n / i) == 0) {
            ans.push_back(n / i);
        }
    }

    return ans;
}

int pow (int a, int n) {
    int res = 1;
    while (n)
        if (n & 1) {
            res *= a;
            --n;
        }
        else {
            a *= a;
            n >>= 1;
        }
    return res;
}

bool isRoot(int shift, vector<int> &m, int x0) {

    int ans = 0;
    for (int i = shift; i < m.size(); i++) {
        ans += m[i] * pow(x0, (i - shift));
    }
    return ans == 0;
}


int searchSS(vector<int> &m) {
    int i = 0;

    while (i < m.size() && m[i] == 0) {
        i += 1;
    }

    if (i == m.size()) {
        return MIN_LIMIT + 1;
    }

    for (auto d : generDivisors(m[i])) {
        if (d >= MIN_LIMIT + 1 && isRoot(i, m, d)) {
            return d;
        }
    }

    return -1;
}



vector<string> parse() {

    char ch;
    vector<string> ans;

    stringstream ss;

    while (~scanf("%c", &ch)) {
        if (ch == '\n') {
            ans.push_back(ss.str());
            break;
        }

        if (ch == '+' || ch == '-' || ch == '=') {
            ans.push_back(ss.str());
            ss.str("");

            ss << ch;
            ans.push_back(ss.str());
            ss.str("");
        } else {
            if (ch == ' ') continue;
            ss << ch;
        }
    }
    return ans;
}

int corLen(vector<string> &prsd) {
    int maxi = -1;
    for (auto &el : prsd) {
        maxi = max(maxi, (int) el.size());
    }
    return maxi;
}

int solve() {
    vector<string> prsd = parse();
    vector<int> m(corLen(prsd));

    addNumToMass(prsd[0], m);

    int i = 1;
    while (prsd[i] != "=") {
        if (prsd[i] == "+") {
            addNumToMass(prsd[i + 1], m);
        } else {
            subNumToMass(prsd[i + 1], m);
        }
        i += 2;
    }

    i++;
    subNumToMass(prsd[i], m);

    i += 1;


    while (i < prsd.size()) {
        if (prsd[i] == "+") {
            subNumToMass(prsd[i + 1], m);
        } else {
            addNumToMass(prsd[i + 1], m);
        }
        i += 2;
    }

    return searchSS(m);
}

int main() {
    cout << solve();

    return 0;
}