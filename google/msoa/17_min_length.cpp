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


int minLength(vector<int> &blubs, vector<int> &d) {
    int n = blubs.size(), cnt1 = 0;
    DSU p(n + 1);
    vector<vector<int>> es;
    for (int i = 0; i < n; ++i) {
        if (blubs[i] == 1) {
            p.merge(i, n);
            cnt1++;
        } else {
            if (i > 0) es.push_back({i, i - 1, d[i] - d[i - 1]});
            if (i < n - 1) es.push_back({i, i + 1, d[i + 1] - d[i]});
        }
    }
    if (cnt1 == 0) return -1;
    int ans = 0;
    sort(es.begin(), es.end(),[&](auto &x, auto &y){
        return x[2] < y[2];
    });

    for(auto &e : es) {
        int x = e[0], y = e[1], c = e[2];
        if (!p.same(x, y)) {
            ans += c;
            p.merge(x, y);
        }
    }
    return ans;
}

int main() {
	vector<int> b{1,0,0};
	vector<int> e{1,5,6};
	auto c=minLength(b,e);
	cout<<c<<"\n";
}