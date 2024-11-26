#include<bits/stdc++.h>
using namespace std;

int treeSplit(vector<int> &a, vector<vector<int>> &es) {
    int n = a.size(), ans = 0;
    vector<vector<int>> g(n), s(n, vector<int>(32));

    for (auto &e : es) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    vector<int> cnt(n);

    function<void(int, int)> dfs = [&](int u, int fa) {
    	cnt[u] = 1;
        for (int i = 0; i < 32; ++i) if (a[u] & (1 << i))
        	s[u][i] = 1;

        for (auto &v : g[u]) {
            if (v == fa) continue;
            dfs(v, u);
            cnt[u] += cnt[v];
            for (int i = 0; i < 32; ++i) 
            	s[u][i] += s[v][i];
        }
    };

    auto get = [&](vector<int> &p, int k) {
    	int x = 0;
    	for (int i = 0; i < 32; ++i) if (p[i] == k)
    		x = x | (1 << i);
    	return x;
    };

    dfs(0, -1);

    for (auto &e : es) {
        int u = e[0], v = e[1];
        if (cnt[u] < cnt[v]) swap(u, v);
        vector<int> c(32);
        for (int i = 0; i < 32; ++i) 
        	c[i] = s[0][i] - s[v][i];
        if (get(c, cnt[0] - cnt[v]) == get(s[v], cnt[v])) ans++;

        // cout<<"u="<<u<<", v="<<v<<", "<<get(c, cnt[0] - cnt[v])<<", "<<get(s[v], cnt[v])<<"\n";
    }
    return ans;
}

int main(){
	/*
	case1
	vector<int> a{5,5,7,5};
	vector<vector<int>> es{
		{0,1},{0,2},{1,3}
	};
	*/
	vector<int> a{3,7,3,3};
	vector<vector<int>> es{
		{0,1},{0,2},{1,3}
	};
	auto c=treeSplit(a,es);
	cout<<c<<"\n";
}