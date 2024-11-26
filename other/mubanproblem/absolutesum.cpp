#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T>
struct AbsSum{
    multiset<T> lp, rp;
    T s;
    AbsSum() : s(0) {}
    T insert(T x) {
        if (lp.empty()) {
            lp.insert(x), rp.insert(x);
            return T(0);
        }
        auto p = interval();
        lp.insert(x), rp.insert(x);
        if (p.first <= x and x <= p.second) return T(0);
        if (*lp.rbegin() > *rp.begin()) {
            T a = *lp.rbegin(), b = *rp.begin();
            lp.erase(lp.find(a));
            rp.erase(rp.find(b));
            rp.insert(a), lp.insert(b);
        }
        T res = min(abs(p.first - x), abs(p.second - x));
        s += res;
        return res;
    }
    T erase(T x) {
        assert(lp.count(x) + rp.count(x) >= 2);
        if (lp.count(x) and rp.count(x)) {
            lp.erase(lp.find(x)), rp.erase(rp.find(x));
            return T(0);
        }
        if (lp.count(x)) {
            lp.erase(lp.find(x));
            lp.erase(lp.find(x));
            lp.insert(*rp.begin());
            rp.erase(rp.begin());
        } else {
            rp.erase(rp.find(x));
            rp.erase(rp.find(x));
            rp.insert(*lp.rbegin());
            lp.erase(prev(lp.end()));
        }
        auto p = interval();
        if (p.first <= x and x <= p.second) return T(0);
        T res = min(abs(p.first - x), abs(p.second - x));
        s -= res;
        return res;
    }
    pair<T, T> interval() {
        assert(!lp.empty());
        return make_pair(*lp.rbegin(), *rp.begin());
    }
    T val() {return s;}
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int q;
    cin >> q;
    AbsSum<ll> p;
    long long s = 0;
    for (int i = 0, t; i < q; ++i) {
        cin >> t;
        if (t == 1) {
            long long x, y;
            cin >> x >> y;
            p.insert(x);
            s += y;
        } else {
            cout << p.interval().first << " " << s + p.val() << '\n';
        }
    }
    return 0;
}


