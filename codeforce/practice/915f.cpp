#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct DSU {
    vector<int> p, siz;
    DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        siz[y] += siz[x];
        p[x] = y;
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
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    using E = tuple<int, int, int, int>;
    vector<E> edges;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        u--, v--;
        if (a[u] > a[v]) swap(u, v);
        edges.emplace_back(u, v, a[u], a[v]);
    }

    auto work = [&](auto comp, bool mx) {
        sort(edges.begin(), edges.end(), comp);
        DSU d(n);
        long long sum = 0;
        for (auto &e : edges) {
            auto [u, v, w1, w2] = e;
            sum += d.size(u) * 1LL * d.size(v) * (mx ? w2 : w1);
            d.merge(u, v);
        }
        return sum;
    };

    cout << work([&](E &x, E &y){return get<3>(x) < get<3>(y);}, true) - work([&](E &x, E &y){return get<2>(x) > get<2>(y);}, false) << "\n";

    return 0;
}
