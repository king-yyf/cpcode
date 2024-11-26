#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, m, d;
int g[N];
vector<int> v[N];
int d1[N], d2[N], up[N];
int p[N];

int dfs(int u, int fa) {
   for (auto j:v[u]) {
       if (j == fa)     continue;
       int d = dfs(j, u) + 1;
       // 底下没有任何怪物 
      
       if (d >= d1[u])   d2[u] = d1[u], d1[u] = d, p[u] = j;
       else if (d >= d2[u])   d2[u] = d;
   } 
   if (g[u])    d1[u] = max(d1[u], 0);
   return d1[u];
}

void dfs1(int u, int fa) {
    for (auto j:v[u]) {
        if (j == fa)    continue;
        if (p[u] == j) {
            up[j] = max(up[u], d2[u]) + 1;
        } else {
            up[j] = max(up[u], d1[u]) + 1;
        }
        if (g[u])
            up[j] = max(up[j], 1);
        dfs1(j, u);
    }
}

int main() {
    cin >> n >> m >> d;
    for (int i = 0; i < m; i++) {
        int x;  cin >> x;
        g[x] = 1;
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b), v[b].push_back(a);
    }
    memset(d1, -0x3f, sizeof d1);
    memset(d2, -0x3f, sizeof d2);
    memset(up, -0x3f, sizeof up);
    dfs(1, -1);
    
    dfs1(1, -1);
    for (int i = 0; i < n; ++i) {
        cout << d1[i + 1] << " \n"[i == n - 1];
    }
    for (int i = 0; i < n; ++i) {
        cout << d2[i + 1] << " \n"[i == n - 1];
    }
    for (int i = 0; i < n; ++i) {
        cout << up[i + 1] << " \n"[i == n - 1];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int mx = max(d1[i], up[i]);
      //  cout << i << " " << d1[i] << " " << up[i] << endl;
        if (mx <= d)
            ans++;
    }
    cout << ans << endl;
    return 0;
}