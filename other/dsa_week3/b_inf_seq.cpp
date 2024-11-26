#include <bits/stdc++.h>
using namespace std;


// https://www.eolymp.com/en/contests/30732/problems/359087

using ll = long long;
map<ll,ll>dp;
ll n, p, q;
long long get(ll x) {
    if (x == 0) return 1;
    if(dp.count(x)) return dp[x]; 
    return dp[x]=get(x / p) + get(x / q);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> p >> q; cout << get(n) << "\n";
    return 0;
}
