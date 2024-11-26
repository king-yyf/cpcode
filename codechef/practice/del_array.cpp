#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.codechef.com/problems/DELARRAY?tab=statement


long long countDelWays(vector<int> &a) {
    int n = a.size(), r = n;
    a.insert(a.begin(), INT_MIN);
    long long ans = 0;
    while (r - 1 >= 1 && a[r] > a[r - 1]) r--;
    ans = n - max(1, r - 1);
    for (int l = 1; l < n; l++) {
        if (not (a[l - 1] < a[l])) break;
        while (r <= n and not (a[l] < a[r])) r++;
        ans += n - max(l + 1, r - 1) + 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin>>t;
    while(t--){
        int n;
        cin >> n;
    	vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];    
        }
    	auto ans = countDelWays(a);
    	cout << ans << "\n";
    }

    return 0;
}
