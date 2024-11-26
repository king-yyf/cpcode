#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;
vector<int> fac[N];
void sieve(){
	if(fac[2].size()) return;
	for(int i = 2; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			fac[j].push_back(i);
		}
	}
}
using pi = pair<int,int>;
int solve(vector<int> &a) {
	sieve();
	set<int> s(a.begin(), a.end());
	a.clear();
	for(int x : s) 
		a.push_back(x);
	int n = s.size();
	priority_queue<pi, vector<pi>, greater<pi>> q;
	int mx = 0;
	vector<int> p(n);
	for (int i = 0; i < n; ++i) {
	    q.push({fac[a[i]][0], i});
	    mx = max(mx, fac[a[i]][0]);	
	}
	int ans = mx - q.top().first, idx;
	while(!q.empty()){
        int idx = q.top().second;
        q.pop();
        if(p[idx] + 1 == fac[a[idx]].size())
            break;
        p[idx]++;
        q.push({fac[a[idx]][p[idx]], idx});
        mx = max(mx, fac[a[idx]][p[idx]]);
        ans = min(ans, mx - q.top().first);
    }
    return ans;

}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    

    return 0;
}
