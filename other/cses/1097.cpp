#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1097


long long calc(vector<int> &a){
    int n = a.size();
    vector dp(n, vector<long long>(n));
    for(int l = 1; l <= n; ++l) 
        for (int i = 0; i + l <= n; ++i) {
            int j = i + l - 1;
            if (l == 1) dp[i][j] = a[i];
            else dp[i][j] = max(a[i] - dp[i+1][j], a[j] - dp[i][j-1]);
        }
    return dp[0][n-1];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    long long s = accumulate(a.begin(), a.end() , 0ll);
    
    cout << (s + calc(a)) / 2 << '\n';

    return 0;
}
