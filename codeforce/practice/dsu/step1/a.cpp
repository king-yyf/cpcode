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
    
    int n, m;
    cin >> n >> m;
    DSU d(n);
    string s;

    for (int i = 0, x, y; i < m; ++i) {
    	cin >> s >> x >> y;
    	if (s[0] == 'u') {
    		d.merge(--x, --y);
    	} else {
    		cout << (d.same(--x, --y) ? "YES" : "NO") << '\n';
    	}

    }

    return 0;
}
