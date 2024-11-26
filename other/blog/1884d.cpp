#include<bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T> void multiple_zeta(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = N / p; j > 0; --j) f[j] += f[j * p];
    }
}
// inverse of multiple_zeta O(N loglog N)
template <class T> void multiple_moebius(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = 1; j * p <= N; ++j) f[j] -= f[j * p];
    }
}
// 对于n的所有约数m,求f(m)的总和 O(N loglog N)
template <class T> void divisor_zeta(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; ++p) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = 1; j * p <= N; ++j) f[j * p] += f[j];
    }
}
// inverse of divisor_zeta()
template <class T> void divisor_moebius(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; ++p) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = N / p; j > 0; --j) f[j * p] -= f[j];
    }
} 
// GCD convolution, ret[k] = \sum_{gcd(i, j) = k} f[i] * g[j]
template <class T> vector<T> gcdconv(vector<T> f, vector<T> g) {
    assert(f.size() == g.size());
    multiple_zeta(f); multiple_zeta(g);
    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];
    multiple_moebius(f);
    return f;
}
// LCM convolution ret[k] = \sum_{lcm(i, j) = k} f[i] * g[j]
template <class T> vector<T> lcmconv(vector<T> f, vector<T> g) {
    assert(f.size() == g.size());
    divisor_zeta(f); divisor_zeta(g);
    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];
    divisor_moebius(f);
    return f;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >>a[i];
    }
   
    vector<long long> f(n+1);
    for(int x:a)
        f[x]++;
    auto g=gcdconv(f,f);
    vector<char> p(n+1,0);
    for(int i=1;i<=n;++i){
        if(!f[i]) continue;
        for(int j=i;j<=n;j+=i)p[j]=1;
    }
    ll c=0;
    for(int i=1;i<=n;++i){
        if(!p[i])c+=g[i];
    }
    c/=2;
    cout<<c<<'\n';

}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
