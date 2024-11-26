#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct DsuOnTree {
    int n, lst_rt;
    vector<vector<int>> g;
    vector<int> siz, ver, in, out;
    DsuOnTree(int n_ = 0) : n(n_), lst_rt(-1), g(n_), in(n_), out(n_), siz(n_, 1){}

    void add_edge(int u, int v, bool bi_dre = true) {
        g[u].push_back(v);
        if(bi_dre) g[v].push_back(u);
    }

    void dfs1(int u, int p) {
        if (p != -1) g[u].erase(find(g[u].begin(), g[u].end(), p));
        in[u] = ver.size(), ver.push_back(u);
        for (int& v : g[u]) if (v != p) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[g[u][0]]) {
                swap(v, g[u][0]);  // g[u][0] 存储u节点的重儿子
            }
        }
        out[u] = ver.size();
    }

    template <class F1, class F2, class F3>
    void build(int root, F1& Add, F2& Del, F3& Calc) {
        dfs1(root, -1);

        auto dfs = [&](auto &dfs, int u, bool keep) -> void {
            int son = g[u].size() ? g[u][0] : -1;
            for (int i = 1; i < g[u].size(); ++i) 
                dfs(dfs, g[u][i], false);
            
            if (son != -1) dfs(dfs, son, true);
            for (int i = 1; i < g[u].size(); ++i) 
                for (int j = in[g[u][i]]; j < out[g[u][i]]; ++j) 
                    Add(ver[j]);
            Add(u);
            Calc(u);
            if (!keep) for (int i = in[u]; i < out[u]; ++i) Del(ver[i]);
        };

        dfs(dfs, 0, false);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) 
    	cin >> x;

    vector<int> cnt(n + 1);
    vector<long long> res(n);
    int mx = 0;
    long long sum = 0;
    vector<int> his;

    DsuOnTree g(n);
 
    for (int i = 1; i < n; ++i) {
    	int u, v;
    	cin >> u >> v;
    	u--, v--;
    	g.add_edge(u, v);
    }

    auto Add = [&](int v) {
        int x = a[v];
        cnt[x]++;
        his.push_back(x);
        if (mx < cnt[x]) {
        	mx = cnt[x], sum = x;
        } else if (mx == cnt[x]) sum += x;
    };

    auto Del = [&](int v) {
        for (auto &&x : his){
        	cnt[x] = 0;
        }
        his = {};
        mx = sum = 0;
    };

    auto Calc = [&](int v) {
        res[v] = sum;
    };

    g.build(0, Add, Del, Calc);

    for (int i = 0; i < n; ++i) {
        cout << res[i] << " \n"[i == n - 1];	
    }
    return 0;
}
