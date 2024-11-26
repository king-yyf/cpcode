#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int minDiffSwaps(vector<int> &a, vector<int> &b) {
    int n = a.size();
    vector<pair<int,int> > c(n);
    for (int i = 0; i < n; ++i) {
        c[i] ={min(a[i],b[i]), max(a[i],b[i])};	
    }

    sort(c.begin(), c.end());
    multiset<int> s;
    for (int i = 0; i < n; ++i) {
    	s.insert(c[i].first);
    } 

    int ans = *(s.rbegin()) - *(s.begin());
    for (int i = 0; i < n; ++i) {
        s.erase(c[i].first);
        s.insert(c[i].second);
        ans = min(ans, *(s.rbegin()) - *(s.begin()));
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
    	int n;
    	cin >> n;
    	vector<int> a(n),b(n);
    	for(auto&x:a)
    		cin>>x;
    	for(auto&x:b)
    		cin>>x;
    	cout<<minDiffSwaps(a,b)<<"\n";
    }
    return 0;
}
