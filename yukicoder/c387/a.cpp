#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
https://yukicoder.me/problems/no/2289
给定一个由 1 到 N 的 N 个不同元素组成的排列 P = (P1, P2, ..., PN)。对于排列 P，可以进行以下操作：
选择整数 i, j (1 ≤ i < j ≤ N)，交换 Pi 和 Pj。输出将给定的排列 P 按升序排列所需的最少操作次数。
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
    
    int n;
    cin >> n;
    vector<int> a(n), vis(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    	a[i]--;
    }

    DSU d(n);

    int ans = 0;

    for (int i = 0; i < n; ++i) {
    	int x = i;
    	while (!vis[x]) {
    		d.merge(x, a[x]);
    		vis[x] = 1;
    		x = a[x];
    	}
    }

    auto p = d.groups();

    for (auto &v : p) {
    	ans += v.size() - 1;
    }

    cout << ans << '\n';
    return 0;
}
