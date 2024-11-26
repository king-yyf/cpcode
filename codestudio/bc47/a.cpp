#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

int minimalTimeRequired(int n, int m, vector<string> &g) {
    vector<vector<int>> c(n,vector<int>(m,n*m));
    for(int i=0;i<m;++i){
    	if(g[n-1][i]=='1') c[n-1][i]=0;
    }
    for(int i=n-2;i>=0;--i){
    	for(int j=0;j<m;++j){
    		if(g[i][j]=='1') c[i][j]=0;
    		else c[i][j]=c[i+1][j]+1;
    	}
    }

    int mn=m*n;
    for(int i=0;i<n;++i){
    	int cu=0;
    	for(int j=0;j<m;++j){
    		if(c[i][j]>cu)cu=c[i][j];
    	}
    	if(cu<mn)mn=cu;
    }
    return mn;
}

template <typename T, class LF, class RF>
void monoStack(vector<T> &a, vector<int> &lt, vector<int> &rt, LF F1, RF F2) {
    int n = a.size();
    lt.assign(n, -1), rt.assign(n, n);
    stack<int> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && F1(a[i],a[sk.top()])) {
            rt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    sk = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && F2(a[i],a[sk.top()])) {
            lt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
}
template <typename T>  // 左右第一个更小的数，即以当前元素为最小值的区间
void le_le(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, less<T>(), less<T>());
}
template <typename T>  // 左右第一个更小的数，右侧是小于等于
void le_le_eq(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, less<T>(), less_equal<T>());
}
template <typename T> // 左右第一个更大的数，即以当前元素为最大值的区间
void gt_gt(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, greater<T>(), greater<T>());
}
template <typename T> // 左右第一个更大的数，右侧是大于等于
void gt_gt_eq(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, greater<T>(), greater_equal<T>());
}

struct BFS {
    static constexpr int unreachable = -1;

    BFS(int n = 0) : n(n), g(n) {}
    template <typename Edges>
    BFS(const vector<vector<int>>& g) : n(g.size()), g(g) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> bfs(const vector<int>& src) const {
        vector<int> dist(n, unreachable);
        queue<int> q;
        for (int v : src) {
            dist[v] = 0;
            q.push(v);
        }
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) if (dist[v] == unreachable) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return dist;
    }
    vector<int> bfs(int s) const { return bfs(vector<int>{ s });}

    vector<vector<int>> connected_components() const {
        vector<vector<int>> res;
        vector<int8_t> vis(n, false);
        for (int i = 0; i < n; ++i) if (not exchange(vis[i], true)) {
            auto& cmp = res.emplace_back();
            queue<int> q;
            q.push(i);
            while (q.size()) {
                int u = q.front();
                q.pop();
                cmp.push_back(u);
                for (int v : g[u]) if (not exchange(vis[v], true)) {
                    q.push(v);
                }
            }
        }
        return res;
    }
private:
    int n;
    vector<vector<int>> g;
};

vector<int> jumpsOnSkyscrapers(int n, vector<int>& a) {
	vector<int> l, r;
	gt_gt(a,l,r);
	BFS g(n);
	for (int i = 0; i < n; ++i) {
	    if(l[i]!=-1) {
	    	g.add_edge(l[i],i);
	    }
	    if(r[i]!=n){
	    	g.add_edge(r[i],i);
	    }
	}
	int mx=a[0],x=0;
	for (int i = 0; i < n; ++i) {
	    if(a[i]>mx){
	    	mx=a[i];x=i;
	    }	
	}
	auto c= g.bfs(x);
	return c;
}

void ac_yyf(int tt) {
    vector<int> a{21, 1, 9, 12, 25, 26, 17};
    auto c=jumpsOnSkyscrapers(a.size(),a);
    int n=a.size();
    for (int i = 0; i < a.size(); ++i) {
        cout<<c[i]<<" \n"[i==n-1];
    }
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
