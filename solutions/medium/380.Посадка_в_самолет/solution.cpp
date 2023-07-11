#include <bits/stdc++.h>

using namespace std;

struct Man {
    bool isAlive;
    int placement_time;
    int waiting_time = -1;
    int ch;
    int seat;

    Man(int plt, string &p) {
        if (p.size() > 2) {
            ch = p[2] - 'A';
            stringstream ss;
            ss << p[0] << p[1];
            seat = atoi( ss.str().c_str());
        } else {
            ch = p[1] - 'A';
            seat = p[0] - '0';
        }
        placement_time = plt;
        isAlive = true;
    }

    Man() {
        isAlive = false;
        placement_time = 1;
        waiting_time = -1;
        ch = '!';
        seat = -1;
    }
};

deque<Man> ZERO_LEVEL;

bool isEmptyCorridor(vector<Man> &c) {
    for (auto &el : c) {
        if (el.isAlive) {
            return false;
        }
    }
    return true;
}

void seatDown(Man &m, vector<vector<int>> &seats) {
    seats[m.seat][m.ch] = true;
}

void checkIsReadyToSeat(vector<Man> &c, vector<vector<int>> &seats) {
    for (int ind = 1; ind < c.size(); ind++) {
        if (c[ind].isAlive && c[ind].waiting_time == 0) {
            seatDown(c[ind], seats);
            c[ind] = Man();

        } else if (c[ind].isAlive && c[ind].waiting_time > 0) {
            c[ind].waiting_time--;
        }
    }
}

int recalcWaiting(vector<vector<int>> &seats, Man &m, int ind) {
    if (m.seat == ind) {
        int addition = 0;
        int tmp = 0;

        if (m.ch <= 2) {
            tmp += (m.ch < 1) ? seats[m.seat][1] : 0;
            tmp += (m.ch < 2) ? seats[m.seat][2] : 0;
        } else {
            tmp += (m.ch > 3) ? seats[m.seat][3] : 0;
            tmp += (m.ch > 4) ? seats[m.seat][4] : 0;

        }

        switch (tmp) {
            case 0:
                break;
            case 1 :
                addition += 5;
                break;
            case 2:
                addition += 15;
                break;
        }

        return m.placement_time + addition;
    }
    return -1;
}


void movePeople(vector<Man> &c, vector<vector<int>> &seats) {
    int s = c.size() - 1;
    while (s > 0) {
        if (c[s].isAlive &&
            c[s].waiting_time == -1 &&
            !c[s + 1].isAlive) {

            c[s + 1] = c[s];
            c[s] = Man();
            c[s + 1].waiting_time = recalcWaiting(seats, c[s + 1], s + 1);
        }
        s--;
    }

    // fixme продвинь из ZERO_LEVEL
    if (!c[1].isAlive && !ZERO_LEVEL.empty()) {
        c[1] = ZERO_LEVEL.front();
        ZERO_LEVEL.pop_front();
        c[1].waiting_time = recalcWaiting(seats, c[s + 1], s + 1);
    }
}

int solution() {
    int timer = 0;
    vector<Man> corridor(31);
    vector<vector<int>> seats(31, vector<int>(6, 0));


    while (!isEmptyCorridor(corridor) || !ZERO_LEVEL.empty()) {
        // сначала +1 ко времени ожидания на нужном месте
        checkIsReadyToSeat(corridor, seats);

        // добавь из начала и продвинь вперед кого можешь
        movePeople(corridor, seats);
        timer++;
    }

    return timer - 1;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);

    int n, tmp;
    cin >> n;
    string s;

    for (int i = 0; i < n; i++) {
        cin >> tmp >> s;
        ZERO_LEVEL.emplace_back(Man(tmp, s));
    }
    cout << solution();
}