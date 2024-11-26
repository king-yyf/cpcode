#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
	for(int x:a)cout<<x<<' ';cout<<"\n";
}

int solve(vector<int> &a) {
	map<int,int> mp;
	for (int x : a) {
		while (x) {
			mp[x]++;
			x /= 2;
		}
	}
	int mx = 0, n = a.size(), ans = 0;
	for (auto &[x, v]: mp) {
		if (v == n) mx = x;
	}
	auto get = [&](int x, int y) {
		int res = 0;
		while (x != y) {
			res++;
			x >>= 1;
		}
		return res;
	};
	for (int i = 0; i < n; ++i) {
 		ans += get(a[i], mx);
	}
	return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    vector<int> a{4,1,2,5, 4};
    cout << solve(a) << "\n";
    return 0;
}
