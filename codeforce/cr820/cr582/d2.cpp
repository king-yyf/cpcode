#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
	for(int x:a)cout<<x<<' ';cout<<"\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    int mx = (*max_element(a.begin(), a.end()));

    vector<vector<int>> p(mx + 1);
    for (int i = 0; i < n; ++i) {
    	int x = a[i], t = 0;
    	while (x) {
    		p[x].push_back(t);
    		x /= 2;
    		t++;
    	}
    	p[0].push_back(t);
    }

    int ans = 1e9;
    for (int i = 0; i <= mx; ++i) {
    	if (p[i].size() < k) continue;
    	sort(p[i].begin(), p[i].end());
    	int s = 0;
    	for (int j = 0; j < k; ++j) {
    		s += p[i][j];
    	}
    	ans = min(ans, s);
    }
    cout << ans << "\n";

    return 0;
}
