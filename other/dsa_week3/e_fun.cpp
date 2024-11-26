#include <bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30732/problems/359090

using ll = long long;
map<ll,ll> dp;
ll get(ll x){
    if(x==0) return 1;
    if(dp.count(x)) return dp[x];
    return dp[x]=get(x/2)+get(x/3);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const int mod=123456789;
    ll n;
    cin>>n;
    cout<<get(n)<<"\n";
    return 0;
}
