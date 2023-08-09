#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

vector<vector<int>> lst;
vector<int> parent;

void make_set (int v) {
    lst[v] = vector<int> (1, v);
    parent[v] = v;
}

int find_set (int v) {
    return parent[v];
}

void union_sets (int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (lst[a].size() < lst[b].size())
            swap(a, b);
        while (!lst[b].empty()) {
            int v = lst[b].back();
            lst[b].pop_back();
            parent[v] = a;
            lst[a].push_back (v);
        }
    }
}

int fromTwoNumsOne(int a, int b) {
    return (a + b + 1) * (2 + a + b) / 2 - (a + 1);
}


struct Cell {
    bool isFrame;
    vector<bool> isPainted;
    int ind;
    Cell() {}

    Cell(int i, int j) {
        ind = fromTwoNumsOne(i, j);
        make_set(ind);

        isFrame = false;
        isPainted.resize(4);
        fill(isPainted.begin(), isPainted.end(), false);
    }

    void makeFrame(int ind) {
        isFrame = true;
        isPainted[ind] = true;
    }
};

void readHorizontal(string &d, vector<int> &widthOfCell, int h) {
    int vertShift = 0, cellId = 1;

    for (int curWidth : widthOfCell) {
        vertShift++;
        if (d[vertShift] != '-') {
            union_sets(fromTwoNumsOne(h, cellId), fromTwoNumsOne(h - 1, cellId));
        }
        cellId++;
        vertShift += curWidth;
    }
}


void readVertical(string &d, vector<int> &widthOfCell, int j) {
    int ind = 0, cellId = 0;

    for (int curWidth : widthOfCell) {
        if (d[ind] != '|') {
            union_sets(fromTwoNumsOne(j, cellId), fromTwoNumsOne(j, cellId + 1)); // fixme indeces!!!
        }
        cellId++;
        ind += curWidth + 1;
    }
}

//    1
//   ---
// 0 | | 2
//   ___
//    3

void initTable(int up, int wide, int n, int m,
               vector<string> &inData, vector<int> &heightOfCell, vector<int> &widthOfCell,
               vector<vector<Cell>> &table) {

    // init snm
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            table[i][j] = Cell(i, j);
        }
    }

    // fill frames
    for (int i = 1; i <= n + 1; i++) {
        table[i][0].makeFrame(2);
        union_sets(fromTwoNumsOne(i, 0), fromTwoNumsOne(i - 1, 0));
        table[i][m + 1].makeFrame(0);
        union_sets(fromTwoNumsOne(0, m + 1), fromTwoNumsOne(0, m + 1));
    }

    for (int i = 1; i <= m + 1; i++) {
        table[0][i].makeFrame(3);
        union_sets(fromTwoNumsOne(0, i - 1), fromTwoNumsOne(0, i));
        table[n + 1][i].makeFrame(1);
        union_sets(fromTwoNumsOne(n + 1, i - 1), fromTwoNumsOne(n + 1, i));
    }

    int i = 0, h = 1;
    bool flag = true;

    while (i < inData.size()) {
        if (flag) {
            readHorizontal(inData[i], widthOfCell, h);
            flag = false;
            i += 1;
        } else {
            readVertical(inData[i], widthOfCell, h);
            flag = true;
            i += heightOfCell[h - 1];
            h++;
        }
    }
}

bool checkVerticalLine(int h, int cellId, vector<vector<Cell>> &table) {
    return (h > 0 && find_set(fromTwoNumsOne(h, cellId)) != find_set(fromTwoNumsOne(h, cellId - 1))) ||
           (h < table.size() - 2 && find_set(fromTwoNumsOne(h + 1, cellId)) != find_set(fromTwoNumsOne(h + 1, cellId - 1))) ||
           table[h][cellId - 1].isFrame && table[h][cellId - 1].isPainted[2] ||
           table[h + 1][cellId - 1].isFrame && table[h + 1][cellId - 1].isPainted[2];
}

bool checkHorizontalLine(int h, int cellId, vector<vector<Cell>> &table) {
    return find_set(fromTwoNumsOne(h, cellId)) != find_set(fromTwoNumsOne(h + 1, cellId)) ||
           table[h + 1][cellId].isFrame && table[h + 1][cellId].isPainted[1] ||
           table[h][cellId].isFrame && table[h][cellId].isPainted[3];
}

bool checkHorizontalPlus(int h, int cellId, vector<vector<Cell>> &table) {
    return find_set(fromTwoNumsOne(h + 1, cellId)) != find_set(fromTwoNumsOne(h, cellId)) ||
           find_set(fromTwoNumsOne(h + 1, cellId - 1)) != find_set(fromTwoNumsOne(h, cellId - 1)) ||
           table[h + 1][cellId].isFrame && table[h + 1][cellId].isPainted[1] ||
           table[h][cellId].isFrame && table[h][cellId].isPainted[3];
}


void writeHorizontal(vector<int> &widthOfCell, vector<vector<Cell>> &table, int h) {
    int cellId = 1;

    bool flag = false;
    for (int curWidth : widthOfCell) {
        flag = false;
        if (checkVerticalLine(h, cellId, table) && checkHorizontalPlus(h, cellId, table)) {
            cout << "+";
        } else if (checkVerticalLine(h, cellId, table)) {
            cout << "|";
        } else if (checkHorizontalPlus(h, cellId, table)) {
            cout << "-";
        } else {
            cout << " ";
        }

        for (int i = 0; i < curWidth; i++) {
            if (checkHorizontalLine(h, cellId, table)) {
                cout << "-";
                flag = true;
            } else {
                cout << " ";
            }
        }
        cellId++;
    }
    if (flag) {
        cout << "+";
    } else {
        cout << "|";
    }

    cout << "\n";
}

bool checkForWriteVert(int h, int cellId, vector<vector<Cell>> &table) {
    return (h > 0 && find_set(fromTwoNumsOne(h, cellId)) != find_set(fromTwoNumsOne(h, cellId - 1))) ||
           table[h][cellId - 1].isFrame && table[h][cellId - 1].isPainted[2];
}

void writeVertical(vector<int> &widthOfCell, vector<vector<Cell>> &table, int h, int i1) {
    for (int i = 0; i < i1; i++) {
        int cellId = 1;

        for (int curWidth : widthOfCell) {
            if (checkForWriteVert(h, cellId, table)) {
                cout << "|";
            } else {
                cout << " ";
            }

            for (int i = 0; i < curWidth; i++) {
                cout << " ";
            }
            cellId++;
        }
        cout << "|\n";
    }
}


void printAns(int up, int n, int m, vector<int> &heightOfCell, vector<int> &widthOfCell,
              vector<vector<Cell>> &table) {
    int i = 0, h = 0;
    bool flag = true;


    while (i < up) {
        if (flag) {
            writeHorizontal(widthOfCell, table, h);
            flag = false;
            i += 1;
        } else {
            writeVertical(widthOfCell, table, h + 1, heightOfCell[h]);
            flag = true;
            i += heightOfCell[h];
            h++;
        }
    }
}

void parse_add(string &s, int &row, int &column) {
    row = 0;
    column = 0;
    string r,c;

    for (char ch : s) {
        if (isdigit(ch)) r.push_back(ch);
        else c.push_back(ch);
    }

    for (char ch : c) {
        column = column * 26 + int(ch - 'A') + 1;
    }

    for (char ch : r) {
        row = row * 10 + int(ch - '0');
    }
}

int split(vector<vector<Cell>> &table, int x_i, int y_j) {
    int c = 0;
    int mem = find_set(fromTwoNumsOne(x_i, y_j));

    for (int i = 1; i <= table.size(); i++) {
        for (int j = 1; j <= table[0].size(); j++) {
            if (find_set(fromTwoNumsOne(i, j)) == mem) {
                make_set(fromTwoNumsOne(i, j));
                c++;
            }
        }
    }
    return c;
}

bool condition(int i, int j, int r1, int c1, int r2, int c2, int i_shift, int j_shift) {
    return find_set(fromTwoNumsOne(i, j)) == find_set(fromTwoNumsOne(r1, c1)) &&
           find_set(fromTwoNumsOne(i + i_shift, j + j_shift)) == find_set(fromTwoNumsOne(r2, c2));
}

bool merge_function(vector<vector<Cell>> &table, int r1, int c1, int r2, int c2) {
    if (find_set(fromTwoNumsOne(r1, c1)) == find_set(fromTwoNumsOne(r2, c2))) {
        cout << "Can not merge cell with itself\n";
        return false;
    }

    int shift_i = -1, shift_j = -1, i = 1, j = 1;
    for (; i <= table.size(); i++) {
        bool flag = false;
        for (; j <= table[0].size(); j++) {
            // horizontal touch fixme
            if (condition(i, j, r1, c1, r2, c2, 0, 1)) {
                shift_i = 0;
                shift_j = 1;
                flag = true;
                break;
            }
            if (condition(i, j, r1, c1, r2, c2, 0, -1)) {
                shift_i = 0;
                shift_j = -1;
                flag = true;
                break;
            }
            // vertical touch fixme
            if (condition(i, j, r1, c1, r2, c2, 1, 0)) {
                shift_i = 1;
                shift_j = 0;
                flag = true;
                break;
            }
            if (condition(i, j, r1, c1, r2, c2, -1, 0)) {
                shift_i = -1;
                shift_j = 0;
                flag = true;
                break;
            }
        }
        if (flag) {
            break;
        }
        j = 1;
    }

    if (shift_i == -1 && shift_j == -1) {
        cout << "Can not merge unaligned cells\n";
        return false;
    }
    // horiz touch
    if (shift_i == 0) {
        while (i - 1 > 0 && find_set(fromTwoNumsOne(i - 1, j)) == find_set(fromTwoNumsOne(i, j))) {
            i--;
        }
        if (find_set(fromTwoNumsOne(i - 1, j + shift_j)) == find_set(fromTwoNumsOne(i, j + shift_j))) {
            cout << "Can not merge unaligned cells\n";
            return false;
        }
        while (i + 1 < table.size() && find_set(fromTwoNumsOne(i + 1, j)) == find_set(fromTwoNumsOne(i, j)) &&
               find_set(fromTwoNumsOne(i + 1, j + shift_j)) == find_set(fromTwoNumsOne(i, j + shift_j))) {
            i++;
        }

        if (find_set(fromTwoNumsOne(i + 1, j + shift_j)) == find_set(fromTwoNumsOne(i, j + shift_j))) {
            cout << "Can not merge unaligned cells\n";
            return false;
        }
        if (find_set(fromTwoNumsOne(i + 1, j)) == find_set(fromTwoNumsOne(i, j))) {
            cout << "Can not merge unaligned cells\n";
            return false;
        }
        cout << "Merged horizontally-aligned cells\n";
        union_sets(fromTwoNumsOne(i, j + shift_j), fromTwoNumsOne(i, j));
        return true;
    }
    // vert touch
    if (shift_j == 0) {
        while (j - 1 > 0 && find_set(fromTwoNumsOne(i, j - 1)) == find_set(fromTwoNumsOne(i, j))) {
            j--;
        }
        if (find_set(fromTwoNumsOne(i + shift_i, j - 1)) == find_set(fromTwoNumsOne(i + shift_i, j))) {
            cout << "Can not merge unaligned cells\n";
            return false;
        }
        while (j + 1 < table[0].size() && find_set(fromTwoNumsOne(i, j + 1)) == find_set(fromTwoNumsOne(i, j)) &&
               find_set(fromTwoNumsOne(i + shift_i, j + 1)) == find_set(fromTwoNumsOne(i + shift_i, j))) {
            j++;
        }

        if (find_set(fromTwoNumsOne(i + shift_i, j + 1)) == find_set(fromTwoNumsOne(i + shift_i, j))) {
            cout << "Can not merge unaligned cells\n";
            return false;
        }
        if (find_set(fromTwoNumsOne(i, j + 1)) == find_set(fromTwoNumsOne(i, j))) {
            cout << "Can not merge unaligned cells\n";
            return false;
        }
        cout << "Merged vertically-aligned cells\n";
        union_sets(fromTwoNumsOne(i + shift_i, j), fromTwoNumsOne(i, j));
        return true;
    }

    return true;
}

void solve() {
    int up, wide;
    cin >> up >> wide;
    string trash;
    getline(cin, trash);


    vector<string> inData(up);
    for (int i = 0; i < up; i++) {
        getline(cin, inData[i]);
    }

    int n, m, tmp;
    vector<int> heightOfCell;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> tmp;
        heightOfCell.push_back(tmp);
    }

    vector<int> widthOfCell;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> tmp;
        widthOfCell.push_back(tmp);
    }

    vector<vector<Cell>> table(n + 2, vector<Cell>(m + 2));
    lst = vector<vector<int>>(2000000);
    parent = vector<int>(2000000);

    initTable(up, wide, n, m, inData, heightOfCell, widthOfCell, table);
    //printAns(up, n, m, heightOfCell, widthOfCell, table);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        string op;
        cin >> op;
        if (op == "split") {
            string o1;
            int r1, c1;
            cin >> o1;
            parse_add(o1, r1, c1);
            int c = split(table, r1, c1);

            if (c > 1) {
                cout << "Split onto " << c << " cells\n";
                printAns(up, n, m, heightOfCell, widthOfCell, table);
            } else {
                cout << "Can not split elementary cell\n";
            }
        }
        if (op == "merge") {
            string o1,o2;
            int r1, c1, r2, c2;
            cin >> o1 >> o2;
            parse_add(o1,r1,c1);
            parse_add(o2,r2,c2);

            if (merge_function(table, r1, c1, r2, c2)) {
                printAns(up, n, m, heightOfCell, widthOfCell, table);
            }
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

/*
7 4
+--+
|  |
+--+
|  |
|  |
|  |
+--+
3
1 1 1
1
2
2
merge A1 A2
split A1

5 11
+---------+
|         |
+---------+
|         |
+---------+
2
1 1
3
2 4 1
2
merge A1 A2
split A1
*/