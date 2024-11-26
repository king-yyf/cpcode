#include <bits/stdc++.h>
using namespace std;

// https://judge.yosupo.jp/problem/directedmst

struct rollback_dsu {
    explicit rollback_dsu(int n) : n(n), pa_or_siz(n, -1) {}
    int get(int u) const { return pa_or_siz[u] < 0 ? u : get(pa_or_siz[u]);}
    bool merge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        u = get(u), v = get(v);
        if (u == v) return false;
        if (-pa_or_siz[u] < -pa_or_siz[v]) std::swap(u, v);
        history.emplace(v, pa_or_siz[v]);
        pa_or_siz[u] += pa_or_siz[v];
        pa_or_siz[v] = u;
        return true;
    }
    int size(int u) const {
        assert(0 <= u && u < n);
        return -pa_or_siz[get(u)];
    }
    void rollback() {
        assert(!history.empty());
        auto [v, val] = history.top();
        auto u = pa_or_siz[v];
        pa_or_siz[v] = val;
        pa_or_siz[u] -= val;
        history.pop();
    }
    void rollback(int count) {
        for (auto i = 0; i < count; ++i) 
            rollback();
    }

private:
    int n;
    vector<int> pa_or_siz;
    stack<std::pair<int, int>> history;
};

template <typename Cost> struct directed_mst {
    explicit directed_mst(int _n) : n(_n), heap_(_n, -1) {}

    void add_edge(int from, int to, Cost cost) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        auto id = static_cast<int>(from_.size());
        from_.push_back(from); to_.push_back(to); cost_.push_back(cost);
        left_.push_back(-1); right_.push_back(-1); lazy_.push_back(Cost{});
        heap_[to] = merge(heap_[to], id);
    }

    pair<Cost, vector<int>> get(int root, bool build_solution = false) {
        rollback_dsu dsu(n);
        Cost result{};
        vector<int> seen(n, -1), path(n), q(n), in(n, -1);
        seen[root] = root;
        vector<std::pair<int, std::vector<int>>> cycles;
        for (auto s = 0; s < n; ++s) {
            auto u = s, pos = 0, w = -1;
            while (!~seen[u]) {
                if (!~heap_[u]) return {-1, {}};
                push(heap_[u]);
                auto e = heap_[u];
                result += cost_[e];
                lazy_[heap_[u]] -= cost_[e];
                heap_[u] = pop(heap_[u]);
                q[pos] = e;
                path[pos++] = u;
                seen[u] = s;
                u = dsu.get(from_[e]);
                if (seen[u] == s) {
                    auto cycle = -1;
                    auto end = pos;
                    do {
                        w = path[--pos];
                        cycle = merge(cycle, heap_[w]);
                    } while (dsu.merge(u, w));
                    u = dsu.get(u);
                    heap_[u] = cycle;
                    seen[u] = -1;
                    cycles.emplace_back(u,vector<int>(q.begin() + pos,q.begin() + end));
                }
            }
            for (auto i = 0; i < pos; ++i) 
                in[dsu.get(to_[q[i]])] = q[i];
        }
        vector<int> parent;
        if (build_solution) {
            for (auto it = cycles.rbegin(); it != cycles.rend(); ++it) {
                auto &[u, comp] = *it;
                auto count = static_cast<int>(comp.size()) - 1;
                dsu.rollback(count);
                auto inedge = in[u];
                for (auto e : comp) {
                    in[dsu.get(to_[e])] = e;
                }
                in[dsu.get(to_[inedge])] = inedge;
            }
            parent.reserve(n);
            for (auto i : in) {
                parent.push_back(~i ? from_[i] : -1);
            }
        }
        return {result, parent};
    }

private:
    void push(int u) {
        cost_[u] += lazy_[u];
        if (auto l = left_[u]; ~l) lazy_[l] += lazy_[u];
        if (auto r = right_[u]; ~r) lazy_[r] += lazy_[u];
        lazy_[u] = 0;
    }
    int merge(int u, int v) {
        if (!~u || !~v) return ~u ? u : v;
        push(u); push(v);
        if (cost_[u] > cost_[v]) swap(u, v);
        right_[u] = merge(v, right_[u]);
        std::swap(left_[u], right_[u]);
        return u;
    }
    int pop(int u) {
        push(u);
        return merge(left_[u], right_[u]);
    }
    const int n;
    vector<int> from_, to_, left_, right_, heap_;
    vector<Cost> cost_, lazy_;
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, S;
    cin >> N >> M >> S;
    directed_mst<long long> dmst(N);
    for (auto i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        dmst.add_edge(a, b, c);
    }
    auto [X, parent] = dmst.get(S);
    cout << X << '\n';
}
