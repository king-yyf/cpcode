#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct DSU {
    vector<int> p, siz, mx;
    DSU(int n) : p(n), siz(n, 1), mx(n) { iota(p.begin(), p.end(), 0); iota(mx.begin(), mx.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (x < y) {
            siz[x] += siz[y];
            p[y] = x;
            mx[x] = max(mx[x], mx[y]);
        } else {
            siz[y] += siz[x];
            p[x] = y;
            mx[y] = max(mx[x], mx[y]);
        }
        
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
    	cin >> s;
    	if (s[0] == 'u') {
            cin >> x >> y;
    		d.merge(--x, --y);
    	} else {
            cin >> x;
            x--;
    		cout << d.get(x) + 1 << ' ' << d.mx[d.get(x)] + 1 << ' ' << d.size(x) << '\n';
    	}

    }

    return 0;
}
