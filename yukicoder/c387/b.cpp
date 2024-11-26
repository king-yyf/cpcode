#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://yukicoder.me/submissions/866171

/*
n个点，初始没有边，q次操作，(1 <= n, q <= 2e5) 每次操作有以下两种。
1 u v 在顶点 u, v 间连接一条边
2 v 输出一个不在一个联通块中的节点，如果没有，输出-1

*/

struct DSU {
    vector<int> p, siz;
    DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) { return siz[get(x)]; }
    vector<vector<int>> groups() {
        vector<vector<int>> res(p.size());
        for (int i = 0; i < p.size(); i++) res[get(i)].push_back(i);
        res.erase(
            remove_if(res.begin(), res.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;

    DSU d(n);
    set<int> s;
    for (int i = 0; i < n; ++i) {
        s.insert(i);    
    }

    int t, u, v;
    while(q--) {
        cin >> t;
        if (t == 1) {
            cin >> u >> v;
            u--, v--;
            u = d.get(u), v = d.get(v);
            if (u != v) {
                d.merge(u, v);
                int e = d.get(u) ^ u ^ v;
                s.erase(e);
            }
        } else {
            cin >> v;
            v--;
            v = d.get(v);
            if (*s.begin() == v) {
                cout << (s.size() == 1 ? -1 : (*next(s.begin()) + 1)) << '\n';
            } else {
                cout << *s.begin() + 1 << '\n';
            }
        }
    }

    return 0;
}
