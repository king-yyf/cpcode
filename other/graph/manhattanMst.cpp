#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://judge.yosupo.jp/problem/manhattanmst


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

template <typename T, typename Comp>
struct KruscalMST {
    KruscalMST() : KruscalMST(0) {}
    explicit KruscalMST(const int n) : _n(n) {}

    void add_edge(const int u, const int v, const T& cost) { _built = false; es.emplace_back(u, v, cost);}
    void add_edge(const tuple<int, int, T>& e) { _built = false; es.push_back(e);}
    bool build() {
        _built = true, _weight_sum = 0;
        if (_n == 0) return true;
        DSU uf(_n);
        sort(es.begin(), es.end(), [this](const auto& u, const auto& v) { return _comp(std::get<2>(u), std::get<2>(v));});
        for (auto& [u, v, w] : es) {
            if (uf.same(u, v)) u = v = _n;
            else { uf.merge(u, v); _weight_sum += w;}
        }
        es.erase(std::remove_if(es.begin(), es.end(), [this](auto& e) { return std::get<0>(e) == _n; }), es.end());
        return int(es.size()) == _n - 1;
    }
    T get_weight() const { assert(_built); return _weight_sum;}
    const std::vector<tuple<int, int, T>>& get_mst() const { assert(_built); return es;}
private:
    int _n;
    T _weight_sum;
    Comp _comp{};
    vector<tuple<int, int, T>> es;
    bool _built = false;
};
template <typename T> using minMst = KruscalMST<T, less<T>>;
template <typename T> using maxMst = KruscalMST<T, greater<T>>;

template <typename WeightType, typename T>
minMst<WeightType> manhattan_mst(vector<pair<T, T>> points) {
    const int n = points.size();
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    auto makees = [&](minMst<WeightType> &mst) {
        std::sort(
            p.begin(), p.end(),
            [&points](int i, int j) {
                const auto &[xi, yi] = points[i];
                const auto &[xj, yj] = points[j];
                return yi - xi == yj - xj ? xi < xj : yi - xi < yj - xj;
            }
        );

        vector<T> comp_x(n);
        for (int i = 0; i < n; ++i) comp_x[i] = points[i].first;
        sort(comp_x.begin(), comp_x.end());
        comp_x.erase(unique(comp_x.begin(), comp_x.end()), comp_x.end());
        const int m = comp_x.size();

        auto get = [&](const T& x) { return lower_bound(comp_x.begin(), comp_x.end(), x) - comp_x.begin();};

        struct PrefixMaxQuery {
            const std::pair<T, int> _neg_inf{ std::numeric_limits<T>::min(), -1 };
            int _n;
            std::vector<std::pair<T, int>> _dat;
            PrefixMaxQuery(int n) : _n(n), _dat(_n + 1, _neg_inf) {}
            void chmax(int i, const std::pair<T, int>& val) {
                for (++i; i <= _n; i += -i & i) if (_dat[i].first < val.first) _dat[i] = val;
            }
            std::pair<T, int> prefix_max(int r) const {
                std::pair<T, int> res = _neg_inf;
                for (; r; r -= -r & r) if (res.first < _dat[r].first) res = _dat[r];
                return res;
            }
        } pmq{ m };

        for (int i : p) {
            const auto& [x, y] = points[i];
            const int cx = get(x);
            if (const auto p = pmq.prefix_max(cx + 1); p != pmq._neg_inf) {
                const auto& [v, j] = p;
                mst.add_edge(i, j, x + y - v);
            }
            pmq.chmax(cx, { x + y, i });
        }
    };

    minMst<WeightType> mst(n);
    for (int x_rev = 0; x_rev < 2; ++x_rev) {
        for (int y_rev = 0; y_rev < 2; ++y_rev) {
            for (int xy_rev = 0; xy_rev < 2; ++xy_rev) {
                makees(mst);
                for (auto& [x, y] : points) std::swap(x, y);
            }
            for (auto& [x, _] : points) x = -x;
        }
        for (auto& [_, y] : points) y = -y;
    }
    assert(mst.build());
    return mst;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> points(n);
    for (auto &[x, y] : points) std::cin >> x >> y;

    auto mst = manhattan_mst<long long>(points);
    std::cout << mst.get_weight() << '\n';
    for (auto [i, j, _] : mst.get_mst()) {
        std::cout << i << ' ' << j << '\n';
    }

    return 0;
}
