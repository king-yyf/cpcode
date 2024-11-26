#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;

struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

template <typename T>
struct Range: map<T, T> {
    T siz = 0;
    using map<T, T>::map, map<T, T>::upper_bound, map<T, T>::begin, map<T, T>::end, map<T, T>::emplace, map<T, T>::erase;
    static T len(const pair<T, T> &p) {return p.second - p.first + 1;}
    pair<vector<pair<T, T>>, typename map<T, T>::iterator> add(pair<T, T> p) {
        vector<pair<T, T>> ds;
        auto it = upper_bound(p.first);
        if (it != begin() && prev(it)->second + 1 >= p.first) {
            if (prev(it)->second >= p.second) return {{*prev(it)}, prev(it)};
            p.first = prev(it)->first;
            ds.emplace_back(*prev(it));
            it = erase(prev(it));
        }
        for (; it != end() && it->first <= p.second + 1; it = erase(it)) {
            if (it->second > p.second) p.second = it->second;
            ds.emplace_back(*it);
        }
        for (auto &range : ds) siz -= len(range);
        auto inserted = emplace(p.first, p.second).first;
        siz += len(*inserted);
        return {ds, inserted};
    }
    pair<vector<pair<T, T>>, vector<pair<T, T>>> del(pair<T, T> p) {
        vector<pair<T, T>> ds, as;
        auto it = upper_bound(p.first);
        if (it != begin() && prev(it)->second + 1 >= p.first) {
            it = prev(it);
            ds.emplace_back(*it);
            if (it->second >= p.second) {
                if (it->second > p.second) as.emplace_back(*emplace(p.second + 1, it->second).first);
                if (it->first < p.first) {
                    it->second = p.first - 1;
                    as.emplace_back(*it);
                } else
                    erase(it);
                for (auto &range : ds) siz -= len(range);
                for (auto &range : as) siz += len(range);
                return {ds, as};
            }
            if (it->first < p.first) {
                it->second = p.first - 1;
                as.emplace_back(*it);
                it = next(it);
            } else
                it = erase(it);
        }
        for (; it != end() && it->first <= p.second; it = erase(it)) {
            ds.emplace_back(*it);
            if (it->second > p.second) as.emplace_back(*emplace(p.second + 1, it->second).first);
        }
        for (auto &range : ds) siz -= len(range);
        for (auto &range : as) siz += len(range);
        return {ds, as};
    }
    typename map<T, T>::const_iterator any(const pair<T, T> &p) const {
        if (auto it = upper_bound(p.second); it != begin() && prev(it)->second >= p.first) return prev(it);
        return end();
    }
    typename map<T, T>::const_iterator all(const pair<T, T> &p) const {
        if (auto it = upper_bound(p.second); it != begin() && prev(it)->first <= p.first && prev(it)->second >= p.second) return prev(it);
        return end();
    }
    template <typename OS>
    friend OS &operator<<(OS &os, const Range &t) {
        os << '[';
        uint32_t index = 0;
        for (auto &[l, r] : t) {
            if (index++) os << ", ";
            os << '[' << l << ", " << r << ']';
        }
        return os << ']';
    }
};


void ac_yyf(int tt) {
    int n, q;
    cin >> n >> q;
    Range<int> p;
    p.add({0, n-1});
    for(int i=0;i<q;++i){
    	int l,r,t;
    	cin>>l>>r>>t;
    	l--,r--;
    	if(t==1){
    		p.del({l,r});
    	}else{
    		p.add({l,r});
    	}
    	cout<<p.siz<<"\n";
    }
    
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
