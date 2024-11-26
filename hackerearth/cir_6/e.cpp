#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
bool st[N];
int primes[N], cnt; // primes[]存储所有素数
void getPrimes(int n) {
    st[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) 
            primes[cnt++] = i;
        for (int j = 0; primes[j] * i <= n; ++j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) 
                break;
        }
    }
}
long long prime_pairs(int n, vector<vector<int>> &es) {
    vector<vector<int>> g(n);
    for (auto &e: es) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }
    long long ans = 0;
    vector<int> down(n), up(n), pa(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
        for (int v : g[u]) if (v != fa) {
            dfs(v, u);
            pa[v] = u;
            if (st[v + 1]) down[u] += down[v] + 1;
        }
    };
    dfs(0, -1);
    function<void(int, int)> dfs2 = [&](int u, int fa) {
        int d = st[u + 1] ? down[u] + 1: 0;
        if (fa != -1 && st[fa + 1]) up[u] += up[fa] + down[fa] + 1 - d;
        for (int v : g[u]) if (v != fa) {
            dfs2(v, u);
        }
    };
    dfs2(0, -1);
    for (int i = 0; i < n; ++i) {
        if (!st[i + 1]) {
            ans += (down[i] + 1ll) * (up[i] + 1ll) - 1;
            long long sum = down[i];
            for (auto & v : g[i]) if (v != pa[i]) {
                if (st[v + 1]) {
                    sum -= down[v] + 1;
                    ans += sum * (down[v] + 1);
                }
            }
        }
    }
    return ans;
}
int main() {
    getPrimes(100000);
    int n;
    cin >> n;
    vector<vector<int>> es(n-1,vector<int>(2));

    for(auto&e:es){
     cin>>e[0]>>e[1];
     e[0]--,e[1]--;
    }
    cout << prime_pairs(n, es) << "\n";
}