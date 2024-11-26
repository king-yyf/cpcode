#include<bits/stdc++.h>
using namespace std;

int minCost(vector<vector<int>> &es) {
    int n = es.size() + 1;
    vector<vector<int>> g(n);
    for (auto &e: es) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }
    int ans = 0;
    function<array<int,2>(int,int)> dfs = [&](int u, int fa) {
        int cnt = 1;
        for (int v: g[u]) {
            if (v == fa) continue;
            auto res = dfs(v, u);
            cnt += res[0], ans += res[1];
        }
        array<int,2> ret = {cnt, (cnt + 4) / 5};
        return ret;
    };

    dfs(0, -1);
    return ans;
}

int main() {
	int n;
	cin >> n;
	vector<vector<int>> es(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		es[i] = {x, y};
	}
	for(int i=0;i<n;++i){
		cout<<"{"<<es[i][0]<<","<<es[i][1]<<"},";
	}
	auto ans = minCost(es);
	cout << ans << "\n";
}