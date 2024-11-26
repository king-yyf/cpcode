#include <bits/stdc++.h>
using namespace std;

int p[26];
void solve() {
    int n, k, m = 0,cnt=0;
    string s, t;
    cin >> n >> k >> s >> t;
    memset(p, -1, sizeof p);
    for (int i = 0; i < n; ++i) {
        if (s[i] != t[i] && !(~p[s[i] - 'a'])) {
            p[s[i] - 'a'] = m++;
        }
    }

    long long ans=0,cur=0;
    k = min(m, k);

    if (k == 0) {
        for (int i = 0; i < n; ++i) {
            if (s[i] == t[i]) {
                cur+=++cnt;
            }
            else {
                cnt=0;
            }
        }
        cout<<cur<<"\n";
        return;
    }

    int mask = (1 << k) - 1;
    while (mask < 1 << m) {
        cur=0,cnt=0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == t[i] || ((mask >> p[s[i] - 'a']) & 1)) {
                cur += ++cnt;
            }
            else {
                cnt=0;
            }
        }
        if (cur>ans)ans=cur;

        int zeros = __builtin_ctz(mask);
        int ones = __builtin_ctz(~mask >> zeros);
        mask += (1 << zeros) + (1 << (ones - 1)) - 1;
    }
    cout<<ans<<"\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    while(T--){
        solve();
    }

    return 0;
}
