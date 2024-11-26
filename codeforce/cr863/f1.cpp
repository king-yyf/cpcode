#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 5;
const ll MOD = 998244353;

ll fact[MAXN], inv_fact[MAXN];
int t, n, k, cnt[MAXN], dp[MAXN];

ll power(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[MAXN - 1] = power(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

ll binom(int n, int k) {
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main() {
    precompute();
    cin >> t;
    while (t--) {
        cin >> n >> k;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            cnt[x]++;
        }
        int max_color = 0;
        for (int i = 1; i <= n; i++) {
            max_color = max(max_color, cnt[i]);
        }
        if (max_color * k > n || n % k != 0) {
            cout << "0\n";
            continue;
        }
        int block_size = n / k;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            dp[i] = 1;
            for (int j = i - 1; j >= 1 && i - j <= block_size; j--) {
                if (cnt[j] >= cnt[i]) {
                    dp[i] = (dp[i] + dp[j] * binom(i - j - 1, block_size - (i - j - 1))) % MOD;
                }
            }
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == max_color) {
                ans = (ans + dp[i]) % MOD;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}