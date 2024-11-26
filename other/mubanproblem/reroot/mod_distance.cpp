#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<long long> &a){
	for(auto&x:a)cout<<x<<' ';cout<<'\n';
}

int numberOfWays(int n, int k, vector<int> &a, vector<int> &b) {
    int mod = 1e9 + 7;
    for (int i = 0; i < n; ++i) {
    	a[i]--, b[i]--;
    }
    vector<int> used(n), unused;
    for (int i = 0; i < n; ++i) {
    	if (b[i] == -1) {
    		unused.push_back(a[i]);
    	} else {
    		if (a[i] - b[i] > k) return 0;
    		used[b[i]] = 1;
    	}
    }
    sort(unused.begin(), unused.end());
    int ans = 1, m = unused.size(), pos = m;
    for (int i = 0; i < n; ++i) {
    	if (used[i]) continue;
    	int p = upper_bound(unused.begin(), unused.end(), i + k) - unused.begin();
    	int x = m - p, y = pos - x;
    	if (y < 0) y = y + mod;
    	ans = ( ans * 1ll * y) % mod;
    	pos--;
    }
    return ans;
}

long long happyString(string s) {
	int n = s.size();
	long long ans = 0;
	map<int, int> mp;
	mp[0] = 1;
	int x = 0;
	for (int i = 0; i < n; ++i) {
		x ^= (1 << (s[i] - 'a'));
		ans += mp[x];
		mp[x]++;
	}
	return ans;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >>t;
    while(t--){
    	
    	int n;
    	cin>>n;
    	string s;
    	cin>>s;
    	cout<<happyString(s)<<"\n";
    }
    return 0;
}
