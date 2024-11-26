#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
        auto v = history.top().first;
        auto val = history.top().second;
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
        return {result, parent};
    }

private:
    void push(int u) {
        cost_[u] += lazy_[u];
        if (~left_[u]) lazy_[left_[u]] += lazy_[u];
        if (~right_[u]) lazy_[right_[u]] += lazy_[u];
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
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, X, Y, Z, k, x;
    while (cin >> n >> X >> Y >> Z ) {
        if (!n) break;
        directed_mst<long long> d(n + 1);
        vector<array<int, 3>> ps(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> ps[i][0] >> ps[i][1] >> ps[i][2];
        } 
        auto dis = [&](int i, int j) {
            long long d = abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1]) + abs(ps[i][2] - ps[j][2]);
            d *= Y;
            if (ps[i][2] < ps[j][2]) d += Z;
            return d;
        };

        for (int i = 1; i <= n; ++i) {
            d.add_edge(0, i, ps[i][2] * 1ll * X);
            cin >> k;
            for (int j = 0; j < k; ++j) {
                cin >> x;
                auto ds = dis(i, x);
                if(i != x && ds < ps[x][2] * X) d.add_edge(i, x, ds);
            }
        }

        cout << d.get(0).first << '\n';      
    }
    return 0;
}
