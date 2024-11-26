#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &v) {
    for (int x : v) {
        cout << x << " ";
    }
    cout << "\n";
}

struct Bits {
    int clz(int x) {return x == 0 ? 64 : __builtin_clz(x);} // 二进制中前导0的个数
    int clz(long long x) {return x == 0 ? 64 : __builtin_clzll(x);} // 前导0
    int ctz(int x) {return x == 0 ? 0 : __builtin_ctz(x);} // 二进制中后缀0的个数
    int ctz(long long x) {return x == 0 ? 0 : __builtin_ctzll(x);} // 后缀0 (long long)
    int pct(int x) {return __builtin_popcount(x);} // 二进制中1的个数
    int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
    int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
    int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);} // ceil(log(2)), minimum x s.t. n <= 2^x
    int ffs(int x) {return __builtin_ffs(x);} // x的最后一位1的是从后向前第几位,eg: 100100, return 3.
    int prt(int x) {return __builtin_parity(x);} //x二进制中1的个数模2的结果
    int prt(long long x) {return __builtin_parityll(x);} //prt long long
    bool get(int x, int i) {return (x & (1 << i)) != 0;} // 获取第i位
    void set(int &x, int i) {x |= (1 << i);}            // 将x第i位设为1
    void reset(int &x, int i) {x &= (~(1 << i));}      //  将x第i位清0
    void flip(int &x) {x = ~x;};        // 翻转x的每一位
    void flip(int &x, int i) {x ^= (1 << i);};        // 翻转第i位
    void flip(int &x, int l, int r) {x ^= makemask(l, r);} // 翻转第l位到第r位
    void resetleft(int &x, int i) {x &= ((1 << i) - 1);} // 清零最高位至第i位(包括第i位和最高位)
    void resetright(int &x, int i) {x &= (-1 << (i + 1));} // 清零第i位至第0位(包括第i位和第0位)
    void set(int &x, int i, int v) { v ? set(x, i) : reset(x, i);} // 将x的第i位设置为v
    bool ispow(int x) {return (x & (x - 1)) == 0;}   // 判断x是否为2的整数次方
    vector<int> gray(int n) {vector<int> a(1<<n); for(int i=0; i<(1<<n); ++i) a[i]=i^(i>>1); return a;}
    int hamming(int x, int y){return pct(x ^ y);} // x,y 二进制的汉明距离
    int setback1(int k) {return (1 << k) - 1;}  // 返回低k位全为1的数(k从1开始)
    int countback1(int x) {return ctz(~x);} //  二进制中后缀1的个数
    int makemask(int l, int r) {return setback1(r + 1) ^ setback1(l);} // 第l位到第r位为1，其余为0的数
    string tostr(int x) {string s; for(int i=lg(x);i>=0;--i) s.push_back(get(x, i) + '0'); return s;} // 转为二进制字符串
} B;

template<typename F> // 按递增顺序枚举二进制包含k个1且小于2^n的数字
void kbits(int n, int k, F &&f) {
    if (k == 0) { f(0); return;}
    for (int s = (1 << k) - 1, x, y; s < 1 << n;) {
        f(s);
        x = __builtin_ctz(s), y = __builtin_ctz(~s >> x);
        s += (1 << x) + (1 << (y - 1)) - 1;
    }
}
template<typename F> // 按递减顺序枚举二进制包含k个1且小于2^n的数字
void kbits_rev(int n, int k, F &&f) {
    if (k == 0) { f(0); return;}
    for (int s = B.makemask(n - k, n - 1), x = 0, y; x != k;) {
        f(s);
        x = __builtin_ctz(~s), s = s ^ ((1 << x) - 1), y = __builtin_ctz(s);
        B.flip(s, y - x - 1, y);
    }
}
template<typename F>  // 递增枚举二进制状态x的所有子集
void submasks(int x, F &&f) {
    for (int s = 0;;s = s ^ (1 << __builtin_ctz(s ^ x) + 1) - 1 & x) { f(s); if (s == x) break;}
}
template<typename F>  // 递减枚举二进制状态x的所有子集
void submasks_rev(int x, F &&f) {
    for (int s = x;;s = (s - 1) & x) { f(s); if (s == 0) break;}
}
template<typename F> // 枚举二进制状态x的所有小于2^n的超集，
void supermasks(int n, int x, F &&f) {
    for (int s = x; s < 1 << n; s = (s + 1) | x) { f(s);}
}
template<typename F>  // 递增枚举某个元素的所有含有 k 个 1 的子状态
void subkbits(int x, int k, F &&f) {
    if (k > __builtin_popcount(x)) return;
    vector<int> res(33);
    for (int i = 0, j = 0; i < 32; ++i)
        if (x & (1 << i)) res[++j] = x & ((1 << (i + 1)) - 1);
    for (int s = res[k], back, a;;) {
        f(s);
        back = B.setback1(B.ctz(s)) & x;
        if (back >= (s ^ x)) break;
        a = B.ctz(x - s - back);
        int md = B.setback1(a) & s;
        s += (1 << a) + res[B.pct(md) - 1] - md;
    }
}
template<typename F>  // 递减枚举某个元素的所有含有 k 个 1 的子状态
void subkbits_rev(int x, int k, F &&f) {
    if (k > __builtin_popcount(x)) return;
    vector<int> res(33);
    for (int i = 0, j = 0; i < 32; ++i)
        if (x & (1 << i)) res[++j] = x & ((1 << (i + 1)) - 1);
    for (int s = x - res[B.pct(x) - k], back;;) {
        f(s);
        back = B.setback1(B.ctz(x ^ s)) & x;
        if (back >= s) break;
        s ^= back ^ (B.setback1(B.ctz(s ^ back) + 1) & x);
        s ^= res[B.pct(s) - k];
    }
}


struct HLD {
    int n, cur = 0;
    vector<int> siz, top, dep, fa, in, out, seq;
    vector<vector<int>> g;
    HLD(int n) : n(n), siz(n), top(n), dep(n), fa(n, -1), in(n), out(n), seq(n), g(n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(int root = 0) {
        top[root] = root;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (fa[u] != -1)
            g[u].erase(find(g[u].begin(), g[u].end(), fa[u]));

        siz[u] = 1;
        for (auto &v : g[u]) {
            fa[v] = u, dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[g[u][0]]) {
                swap(v, g[u][0]);  // g[u][0] 存储u节点的重儿子
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : g[u]) {
            top[v] = v == g[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = fa[top[u]];
            } else {
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    template<typename F> 
    void path(int u, int v, F &&f) { // 处理从u到v的路径
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            f(in[top[u]], in[u]);
            u = fa[top[u]];
        }
    }
    template<typename F> 
    void tree(int u, F &&f) { // 处理以u为根的子树
        f(in[u], out[u]);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    HLD h(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        u--, v--;
        h.add_edge(u, v);
    }
    h.build();

    return 0;
}
