#include <bits/stdc++.h>
using namespace std;

int countUniqueSeq(vector<int> &a) {
    int n = a.size(), mod = 1e9 + 7;
    sort(a.begin(), a.end());
    vector dp(n + 1, vector<int>(2));
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        if (!mp.count(a[i])) mp[a[i]] = i;
        dp[i + 1][0] = (dp[i][0] + dp[i][1]) % mod;
        dp[i + 1][1] = (dp[mp[a[i]]][0] + dp[mp[a[i]]][1] + 1) % mod;
        
    }
    return (dp[n][0] + dp[n][1]) % mod;
}


int cal1(vector<int> &a){
    int n=a.size(),c=0;
    for(int i=0;i<(1<<n);++i){
        vector<int> p;
        for(int j=0;j<n;++j){
            if((i>>j)&1)p.push_back(a[j]);
        }
        set<int> s(p.begin(), p.end());
        if(s.size()==p.size())c++;
    }
    return c-1;
}

void solve(int tt) {
    int n = 5;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 5; ++j) {
            for (int k = 1; k <= 5; ++k) {
                for (int l = 1; l <= 5; ++l) {
                    for (int x = 1; x <= 5; ++x) {
                        vector<int> a{i, j, k, l, x};
                        int x1=cal1(a),x2=countUniqueSeq(a);
                        cout<<x1<<", "<<x2<<","<<(x1==x2)<<"\n";
                    }
                }
            }
        }
    }
    // vector<int> a{1,2,3};
    // cout<<countUniqueSeq(a)<<"\n";


    // cout<<c<<"\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
