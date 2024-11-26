#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MXN = 5e6 + 2;
int primes[MXN], euler[MXN], prime_cnt; 
bool st[MXN];
void sieve_eulers(int n) { // 筛法求欧拉函数
    euler[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) {
            primes[prime_cnt++] = i;
            euler[i] = i - 1;
        }
        for (int j = 0; primes[j] * 1ll * i <= n; ++j) {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0) {
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }
}

template <class T>
struct Discrete {
    vector<T> xs;
    Discrete(const vector<T>& v) {
        xs = v;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }
    int get(const T& x) const {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    inline int operator()(const T& x) const { return get(x); }
    T operator[](int i) { return xs[i]; }
    int size() const { return xs.size(); }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    sieve_eulers(5e6);
    
    int n, m;
    cin >> n >> m;

    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
         cin >> a[i];	
    }

    for (auto x : a) {
    	while (x > 1) {
    		a.push_back(euler[x]);
    		x = euler[x];
    	}
    }
    a.push_back(1);

    Discrete<int> v(a);

    return 0;
}
