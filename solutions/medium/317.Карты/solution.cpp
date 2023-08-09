#include <iostream>

using namespace std;

void main1() {
    long long n, n1, n2, n3, n1Full, n2Full, n3Full, s1, s2, s3;

    cin >> n;
    cin >> n1 >> n2 >> n3;

    n1Full = (n * (1 + n)) / 2;
    n2Full = (n * (n + 1) * (2 * n + 1)) / 6;
    n3Full = (n * n * (n + 1) * (n + 1)) / 4;
    s1 = n1Full - n1;
    s2 = n2Full - n2;
    s3 = n3Full - n3;
    for (long long i = 0; i < n + 1; i++) {
        for (long long j = i + 1; j < n + 1; j++) {
            long long k = s1 - j - i;
            if (k == i || k == j) {
                continue;
            }
                if (k * k + j * j + i * i == s2 \
                        && k * k * k + j * j * j + i * i * i == s3) {
                    cout << i << " " << j << " " << k << endl;
                    return;
                }
        }
    }


}

int main() {
    main1();
    return 0;
}