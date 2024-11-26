#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, u, v, x, y;
long long f[N], dep[N], siz[N];
vector<int> g[N];
void dfs(int u, int fa){
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    for (auto &v: g[u]) {
        if (v != fa) {
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
}
void dfs1(int u, int fa) {
    for (auto &v: g[u]) 
        if (v != fa) {
            f[v] = f[u] - siz[v] * 2 + n;
            dfs1(v, u);
        }
}
int main(){
    scanf("%d",&n);
    for (int i = 0; i <= n; ++i) g[i].clear();
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 1);
    for (int i = 1; i <= n; ++i) f[1] += dep[i];
    dfs1(1, 1);
    long long ans = -1, id;

    for (int i = 1; i <= n; ++i) {
        cout << f[i] << " \n"[i == n];
    }
    for (int i = 1; i <= n; ++i) {
        if (f[i] > ans) ans = f[i], id = i;
    }
    printf("%d\n", id);
}
