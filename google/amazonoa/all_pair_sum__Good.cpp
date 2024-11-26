#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int m=998244353;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin>>n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    long long c=0;
    for (int i = 0; i < n; ++i) {
        for(int j=i+1;j<n;++j){
            string s=a[i]+a[j];
            ll t=stoll(s);
            c=(c+t)%m;
        }
    }
    cout<<c<<'\n';

    return 0;
}
