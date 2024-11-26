#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
	for(auto&x:a)cout<<x<<' ';cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> dp(m + 1);
    for (int i = 0, k; i < n; ++i) {
        cin >> k;
        vector<int> s(k + 1), q(k + 1);
        for (int j = 1; j <= k; ++j) {
        	cin >> s[j];
            s[j] += s[j - 1];
        }
        for (int j = 1; j <= k; ++j) {
        	for (int l = 0; l <= j; ++l) {
        		q[j] = max(q[j], s[l] + s[k] - s[k - j + l]);
        	}
        } 
        for (int l = m; l >= 0; --l) 
            for (int j = 0; j <= k && j <= l; ++j) 
                dp[l] = max(dp[l], q[j] + dp[l - j]);
    }
    
    cout << dp[m] << '\n';

    return 0;
}
