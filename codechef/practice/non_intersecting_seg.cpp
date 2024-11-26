#include <bits/stdc++.h>
using namespace std;

// https://www.codechef.com/problems/CHSGMNTS?tab=statement

/*
 find number of pairs of non-intersecting segments [a, b] and [c, d] 
 (1 ≤ a ≤ b < c ≤ d ≤ N) such there is no number that occurs in the 
 subarray A[a..b] and A[c..d] simultaneously.

1 ≤ T ≤ 5
1 ≤ N ≤ 1000
1 ≤ Ai ≤ 109

*/

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


int count_non_intersec_seg(vector<int> &a) {
	Discrete<int> v(a);
	for(int &x:a)
		x=v(x);
	int n=a.size();
	vector<vector<int>> p(n);
	for (int i = 0; i < n; ++i) {
	    p[a[i]].push_back(i);	
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
	    set<int> b{i - 1, n};
	    vector<int> vis(n);
	    int tot = (n - i) * (n - i + 1) / 2;
	    for (int j = i; j < n; ++j) {
	    	if (vis[a[j]]) {
	    		ans += tot;
	    		continue;
	    	}
	    	vis[a[j]] = 1;
	    	for (int x : p[a[j]]) {
	    		auto it = b.lower_bound(x);
		    	int r = *it, l = *prev(it);
		    	tot -= (x - l) * (r - x);
		    	b.insert(x);
	    	}
	    	ans += tot;
	    }
	    p[a[i]].erase(p[a[i]].begin());

	}
	return ans;
}

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;cin>>t;while(t--){
    	int n;cin>>n;
    	vector<int> a(n);
    	for (int i = 0; i < n; ++i) {
    	    cin>>a[i];	
    	}
    	auto ans=count_non_intersec_seg(a);
    	cout<<ans<<"\n";

    }

    return 0;
}
