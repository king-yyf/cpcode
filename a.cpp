#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * ImplicitGraph g : (int u, auto f) -> { for (int v : adjacent(u)) f(v); }
 */
class EulerTour {
    public:
        template <typename ImplicitGraph>
        EulerTour(const ImplicitGraph g, int n, int root = 0) : n(n), m(clg(2 * n)) {
            dep.resize(n + 1), visit.resize(n), leave.resize(n);
            seg.assign(2 * m, n);
            dfs(g, root);
            for (int k = m - 1; k > 0; --k) seg[k] = argmin(seg[(k << 1) | 0], seg[(k << 1) | 1]);
        }
        template <typename Edge, typename EdgeToNode>
        EulerTour(const vector<vector<Edge>> &g, const EdgeToNode eton, int root = 0) :
            EulerTour([&](int u, auto f) { for (const Edge &e : g[u]) f(eton(e)); }, g.size(), root) {}
        EulerTour(const vector<vector<int>> &g, int root = 0) :
            EulerTour([&](int u, auto f) { for (int v : g[u]) f(v); }, g.size(), root) {}
        int lca(int u, int v) const {
            if (visit[u] > visit[v]) return lca(v, u);
            int res = n;
            for (int l = m + visit[u], r = m + visit[v] + 1; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res = argmin(res, seg[l++]);
                if (r & 1) res = argmin(res, seg[--r]);
            }
            return res;
        }
        inline int dist(int u, int v) const { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
        inline int depth(int u) const { return dep[u]; }
        inline int visit_time(int u) const { return visit[u]; }
        inline int leave_time(int u) const { return leave[u]; }
        inline int parent(int u) const {
            int p = seg[m + leave[u]];
            return p == n ? -1 : p;
        }
    private:
        const int n, m;
        vector<int> visit, leave, dep, seg;
        template <typename ImplicitGraph>
        void dfs(ImplicitGraph g, int root) {
            dep[root] = 0, dep[n] = numeric_limits<int>::max();
            int k = 0;
            auto f = [&](auto self, int u, int p) -> void {
                visit[u] = k, seg[m + k++] = u;
                g(u, [&](int v){ if (v != p) dep[v] = dep[u] + 1, self(self, v, u); });
                leave[u] = k, seg[m + k++] = p;
            };
            f(f, root, n);
        }
        inline int argmin(int u, int v) const { return dep[u] < dep[v] ? u : v; }
        static int clg(const int x) { return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s;
    cin >> s;

    auto runs = run_enum(s);
    sort(begin(runs), end(runs));

    cout << runs.size() << '\n';
    for (const auto &run : runs) {
        cout << run.period << ' ' << run.l << ' ' << run.r << '\n';
    }

    return 0;
}
