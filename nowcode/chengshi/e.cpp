#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
#define maxn 200005
using namespace std;
typedef long long ll;
int read() {
    int x = 0, f = 1, ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
    return x * f;
}
 
int root[maxn], tot = 0, cnt = 0;
int t[maxn << 5][2], num[maxn << 5], tm[maxn << 5];
int insert(int rt, int x, int k) {
     int p = ++tot;
    if(k < 0)  {num[p] = x; tm[p] = cnt; return p;}
     int c = x >> k & 1;
    t[p][c ^ 1] = t[rt][c ^ 1], t[p][c] = insert(t[rt][c], x, k - 1);
    tm[p] = max(tm[t[p][c]], tm[t[p][c ^ 1]]);
    return p;
}
 
int ask(int p, int lim, int x, int k) {//ask是查询连续区间内的异或最大值。
    if(k < 0) {return num[p];}
     int c = x >> k & 1;
    if(tm[t[p][c ^ 1]] >= lim) return ask(t[p][c ^ 1], lim, x, k - 1);
    else return ask(t[p][c], lim, x, k - 1);
}
 
struct edge {int to, nxt;}e[maxn << 1];
int head[maxn], k = 0;
void add(int u, int v) {e[k] = {v, head[u]}; head[u] = k++;}
 
int n, m, w[maxn];
int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn], sub[maxn], dfn[maxn];
void dfs1(int u) {
    siz[u] = 1;
    for(int i = head[u], v; ~i; i = e[i].nxt) {
        v = e[i].to; if(v == fa[u]) continue;
        dep[v] = dep[u] + 1, fa[v] = u; 
        dfs1(v); siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}
 
void dfs2(int u, int tp) {
    top[u] = tp; dfn[u] = ++cnt;
    root[cnt] = insert(root[cnt - 1], w[u], 30);
    if(son[u]) dfs2(son[u], tp);
    for(int i = head[u], v; ~i; i = e[i].nxt) {
        v = e[i].to; if(v != fa[u] && v != son[u]) dfs2(v, v);
    }
    sub[u] = cnt;
}
 
int query(int u, int v, int x) {//树剖跳链
     int ans = 0, tmp;
    while(top[u] != top[v]) {
        if(dep[top[u]] > dep[top[v]]) swap(u, v);
        tmp = ask(root[dfn[v]], dfn[top[v]], x, 30);
        if(ans < (tmp ^ x)) ans = tmp ^ x;//注意一定是用与x的异或值比较大小
        v = fa[top[v]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    tmp = ask(root[dfn[v]], dfn[u], x, 30);
    if(ans < (tmp ^ x)) return tmp ^ x;
    return ans;
}
 
signed main() {
    memset(head, -1, sizeof head);
    n = read();
    for(int i = 1; i <= n; i++) w[i] = read();
    for(int i = 1, u, v; i < n; i++) u = read(), v = read(), add(u, v), add(v, u);
    dfs1(1); dfs2(1, 1);//树剖预处理
    m = read();
    int x, y, z;
    for(int i = 1; i <= m; i++) {
        y= read(), x = read();
        printf("%d\n", w[y] ^ ask(root[sub[x]], dfn[x], w[y], 30));
    }
    return 0;
}