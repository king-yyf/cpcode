#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://judge.yosupo.jp/problem/static_range_frequency

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
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    Discrete<int> v(a);
    vector<int> pos[v.size()];
    for (int i = 0; i < n; ++i) {
        pos[v(a[i])].push_back(i);
    }

    int l, r, x;

    while(q--) {
    	cin >> l >> r >> x;
    	auto p = v(x);
    	if (p >= n || v[p] != x) cout << "0\n";
    	else {
    		auto &v = pos[p];
    		cout <<  lower_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l) << '\n';
    	}
    }

    return 0;
}