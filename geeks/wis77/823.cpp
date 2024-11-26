#include <bits/stdc++.h>
using namespace std;


int numFactoredBinaryTrees(vector<int>& a) {
    int n = a.size(), mod = 1e9 + 7;
    set<int> s(a.begin(), a.end());
    sort(a.begin(), a.end());
    map<int, set<pair<int,int>>> mp;
    vector<int> deg(n);
    for(int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            long long m = a[i] * 1ll * a[j];
            if (s.count(m)) {
                mp[m].insert({a[i],a[j]});
                deg[a[i]]++;
                if (a[i] != a[j]) deg[a[j]]++;
            }
        }
    }

    long long ans = 0;

    function<int(int, int)> dfs = [&](int u, int fa) {
    	long long res = 1;
    	for (auto &[x, y] : mp[u]) {
    		int p1 = dfs(x, u), p2 = dfs(y, u);
    		long long mm = p1 * 1ll * p2;
    		res = (res + mm) % mod;

    	}
    	ans = (ans + res) % mod;
    	return res;
    };

    for (int i = 0; i < n; ++i) {
        if (deg[a[i]] == 0) {
        	dfs(i, -1);
        }
    }
    return ans;
}



int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

   
    return 0;
}
