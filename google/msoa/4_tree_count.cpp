#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct FenwickTree2D{
    vector<vector<T>> tr;
    int n, m;
    FenwickTree2D(int N, int M){
        n = N, m = M; 
        tr.assiingn(n + 1, vector<T>(m + 1 , 0));
    }
    void add(int x, int y, int val){
        for(int i = x;i <= n; i += i & -i){
            for(int j = y;j <= m; j += j & -j){
                tr[i][j] += val;
            }
        }
    }
 
    T ask(int x, int y) {
        T ret = 0;
        for(int i = x; i >= 1;i -= i & -i)
            for(int j = y; j >= 1;j -= j & -j)
                ret += tr[i][j];
        return ret;
    }
    T ask(int x1, int y1, int x2, int y2) {
        return ask(x2, y2) - ask(x2, y1 - 1) - ask(x1 - 1, y2) + ask(x1 - 1, y1 - 1);
    }
};


template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T qry(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T qry(int l, int r) {
        if (l > r) return 0;
        return qry(r) - qry(l - 1);
    }
};

vector<long long> getValue(vector<int> &a, vector<vector<int>> &es) {
    int n = a.size();
    vector<long long> ans(n);

    vector<vector<int>> g(n);
    for(auto&e : es) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    Fenwick<long long> t1(n + 1), t2(n + 1);

    auto v = a;
    sort(v.begin(), v.end());
    v.erase(unique(begin(v), end(v)), end(v));

    auto get = [&](long long x) {
        return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    };

    function<void(int, int)> dfs = [&](int u, int fa) {
        int t = get(a[u]);
        long long x = t1.qry(1, t - 1), y = t2.qry(t + 1, n) * a[u];
        ans[u] = x + y;
        cout << "u = " << u + 1 << ", x = " << x << ", y = " << y << ", ans = " << ans[u] <<  "\n";
        t1.add(t, a[u]);
        t2.add(t, 1);
        for (auto &v : g[u]) {
            if (v == fa) continue;
            dfs(v, u);
        }
        t1.add(t, -a[u]);
        t2.add(t, -1);
    };

    dfs(0, -1);

    return ans;
}

int main() {
    vector<int> a={4,4,7,6,3,5,4};
    vector<vector<int>> es{
        {0,1},{0,2},{1,3},{2,4},{2,5},{4,6}
    };
    auto c=getValue(a,es);
}