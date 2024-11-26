#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int primes[N], cnt;     // primes[]存储所有素数
bool st[N],vis[N];
void getPrimes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) 
            primes[cnt++] = i;
        for (int j = 0; primes[j] * 1ll * i <= n; ++j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) 
                break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    getPrimes(3e5);

    int n;
    cin >> n;

    vector<int> a(n);

    vector<array<int,3>> g(n + m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    return 0;
}
