#include <bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30732/problems/359089

using ll = long long;
long long  qpow(long long m, long long k, long long p) {
    long long res = 1 % p, t = m;
    while (k) {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const int mod=123456789;
    int n;
    cin>>n;
    long long res=1;
    if(n<=2)cout<<res<<"\n";
    else{
       res=qpow(2,n-2,mod);
       cout<<res<<"\n";
    }
    return 0;
}
