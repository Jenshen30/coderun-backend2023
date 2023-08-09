#include <iostream>
#include "vector"

using namespace std;

struct Node {
    int min, max;
    bool flag = false;
};



void andrey_stankevich(vector<Node> &a, int i)
{
    if (a[i].flag)
    {
        a[i].flag = false;
        a[i * 2 + 1].flag = true;
        a[i * 2 + 2].flag = true;
        a[i * 2 + 1].min = a[i].min;
        a[i * 2 + 2].min = a[i].min;

        a[i * 2 + 1].max = a[i].max;
        a[i * 2 + 2].max = a[i].max;
    }
}

void build(vector<Node> &a, vector<Node> &hlp, int i, int l, int r)
{
    if (r - l == 1)
    {
        a[i].min = hlp[l].min;
        a[i].max = hlp[l].max;
        return;
    }

    int m = (l + r) / 2;
    build(a, hlp, 2 * i + 1, l, m);
    build(a, hlp, 2 * i + 2, m, r);

    a[i].max = max(a[2 * i + 1].max, a[2 * i + 2].max);
    a[i].min = min(a[2 * i + 1].min, a[2 * i + 2].min);
}

int findMin(vector<Node> &a, int i, int l, int r, int lx, int rx)
{
    if (rx <= l || r <= lx)
    {
        return 1000000000 + 1;
    }
    if (l <= lx && rx <= r)
    {
        return a[i].min;
    }
    int m = (lx + rx) / 2;
    andrey_stankevich(a, i);
    return min(findMin(a, 2 * i + 1, l, r, lx, m), findMin(a, 2 * i + 2, l, r, m, rx));
}

int findMax(vector<Node> &a, int i, int l, int r, int lx, int rx)
{
    if (rx <= l || r <= lx)
    {
        return -1;
    }
    if (l <= lx && rx <= r)
    {
        return a[i].max;
    }
    int m = (lx + rx) / 2;
    andrey_stankevich(a, i);
    return max(findMax(a, 2 * i + 1, l, r, lx, m), findMax(a, 2 * i + 2, l, r, m, rx));
}

void set(vector<Node> &a, int i, int x, int l, int r, int lx, int rx)
{

    if (rx <= l || r <= lx)
    {
        return;
    }
    if (l <= lx && rx <= r)
    {
        a[i].flag = true;
        a[i].min = x;
        a[i].max = x;
        return;
    }
    int m = (lx + rx) / 2;
    andrey_stankevich(a, i);
    set(a, 2 * i + 1, x, l, r, lx, m);
    set(a, 2 * i + 2, x, l, r, m, rx);
    a[i].min = min(a[2 * i + 1].min, a[2 * i + 2].min);
    a[i].max = max(a[2 * i + 1].max, a[2 * i + 2].max);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> mass(n, -1);

    for (int i = 0; i < n; ++i)
    {
        cin >> mass[i];
    }

    vector<Node> hlp;
    for (int i = 0; i < n; i++)
    {
        Node * node = new Node();
        node->min = mass[i];
        node->max = mass[i];
        hlp.push_back(*node);
    }

    while (true)
    {
        if (!(hlp.size() & (hlp.size() - 1)))
        {
            break;
        }
        Node *node = new Node();
        node->min = 1000000000 + 1;
        node->max = -1;
        hlp.push_back(*node);
    }

    vector<Node> nodes;
    nodes.resize(2 * hlp.size() - 1);
    n = hlp.size();
    build(nodes, hlp, 0, 0, n);


    for (int i = 0; i < q; i++)
    {
        int l, r, a, b;
        cin >> a >> b >> l >> r;
        l -= 1;
        auto tmp = findMin(nodes, 0, l, r, 0, n);
        if (tmp == findMax(nodes, 0, l, r, 0, n) && tmp == a) {
            cout << "1" << "\n";
            set(nodes, 0, b, l, r, 0, n);
        } else {
            cout << "0" << "\n";
        }
    }
}