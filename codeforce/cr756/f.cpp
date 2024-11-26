#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestAwesome(string s) {
    	map<int,vector<int>> mp;
    	int n = s.size();
    	vector p(n+1,vector<int>(10));
    	for(int i=0;i<n;++i){
    		mp[s[i]-'0'].push_back(i);
    		for(int j=0;j<10;++j){
    			p[i+1][j]=p[i][j]+(s[i]=='0'+j);
    		}
    	}

    	int cnt = 1;

    	set<int> v;
    	for(auto&[x,y]:mp){
    		if(y.size()%2==1)v.insert(x);
    	}

    	if(v.size()<=1){
    		return n;
    	}

    	for(int i=0;i<n;++i){
    		int l=i,r=n-1,mx=-1;
    		while(l<=r){
    			int md=(l+r)/2;
    			set<int> c;
    			for(auto&x:v){
    				int d=p[md+1][x]-p[i][x];
    				
    			}
    			if(c<=1){
    				mx=md;
    				l=md+1;
    			}else r=md-1;
    		}
    		if(mx!=-1)cnt=max(cnt,mx-i+1);
    	}
        
    	return cnt;
    }
};

void solve() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) 
    	cin >> a[i];

    long long s = t;
    int mx = 0, x, y, l = 0;
    for (int r = 0; r < n; ++r) {
    	s += a[r];
    	while (l <= r && s < 0) {
    		s -= a[l];
    		l++;
    	}
    	if (r - l + 1 > mx) {
    		mx = r - l + 1, x = l, y = r;
    	}
    }
    if (mx) cout << x + 1 << ' ' << y + 1 << '\n';
    else cout << "-1\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--) solve();

    return 0;
}
