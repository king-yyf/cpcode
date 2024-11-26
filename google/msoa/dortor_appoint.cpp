#include <bits/stdc++.h>
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

bool isGoodArrange(vector<int> &a, vector<int> &b, int m) {
	int n = a.size();
    DSU d(m);

    for (int i = 0; i < n; ++i) {
    	d.merge(a[i], b[i]);
    }
    vector<int> freq(m);
    for (int i = 0; i < n; ++i) {
    	freq[d.get(a[i])]++;
    }

    for (int i = 0; i < n; ++i) {
    	if (d.size(a[i]) < freq[d.get(a[i])]) {
    		return false;
    	}
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    return 0;
}
