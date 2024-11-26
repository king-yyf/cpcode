#include<bits/stdc++.h>
using namespace std;

int goodPaths(vector<vector<int>> &es, vector<int> &a) {
    int n = a.size();
    vector<vector<int>> g(n);
    for (auto &e: es) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }
    int ans = 0;
    map<int, int> mp;
    function<void(int, int)> dfs = [&](int u, int fa) {
        mp[a[u]]++;

        if (mp.size() == 1) ans++;
        else if (mp.size() == 2) {
            int u = mp.begin()->second, v = mp.rbegin()->second;
            if (abs(u - v) <= 1) ans++;
        }
        for (int v: g[u]) {
            if (v == fa) continue;
            dfs(v, u);
        }
        mp[a[u]]--;
        if (mp[a[u]] == 0) mp.erase(a[u]);
    };
    dfs(0, -1);
    return ans;
}

int main(){
	vector<vector<int>> es{
		{0,1},{0,2},{2,3},{2,4},{2,5},{4,6}
	};
	vector<int> a{3,2,4,5,4,3,3,3};
	auto c = goodPaths(es, a);
	cout<<c<<"\n";
}