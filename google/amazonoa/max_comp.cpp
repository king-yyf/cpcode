#include<bits/stdc++.h>
using namespace std;

struct DSU {
  public:
    DSU() : _n(0) {}
    explicit DSU(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = get(a), y = get(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return get(a) == get(b);
    }

    int get(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = get(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[get(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = get(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};


void solve () {
	int n, na, nb, x, y;
	cin >> n >> na >> nb;
    DSU d(n),d2(n);
	for (int i = 0; i < na; ++i) {
		cin >> x >> y;
		x--,y--;
		d.merge(x, y);
        d2.merge(x, y);
	}

    set<int> s;
    for (int i = 0; i < nb; ++i) {
        cin >> x >> y;
        x--, y--;
        if (d2.same(x, y)) {
            s.insert(d.get(x));
        }
        d2.merge(x, y);
    }

    for (auto &x : s) {
        s.insert(d2.get(x));
    }

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        int p = d.get(i);
        if (s.count(p)) continue;
        ans = max(ans,  d.size(p));
    }
    cout << ans << "\n";
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}