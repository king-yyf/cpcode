#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 22;

int a[N];

long long f[N][10];

void init() {
    for (int i = 0; i <= 9; ++i) 
        f[1][i] = 1;

    for (int i = 2; i < N; ++i) 
        for (int j = 0; j <= 9; ++j) 
            for (int k = 0; k <= 9; ++k) 
                if (j != k) f[i][j] += f[i - 1][k];
}

long long dp(long long n) {
    if (n < 0) return 0;
    if (!n) return 1;
    int cnt = 0;
    while (n) {
        a[++cnt] = n % 10, n /= 10;
    }
    int last = 0;
    long long res = 0;
    for (int i = cnt; i >= 1; --i) {
        int now = a[i];
        for (int j = 0; j < now; ++j) {
            if (j != last) res += f[i][j];
        }
        if (now == last) break;
        last = now;
        if (i == 1) res++;
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long a, b;
    cin >> a >> b;

    init();

    cout << dp(b) - dp(a - 1) << '\n';

    return 0;
}
