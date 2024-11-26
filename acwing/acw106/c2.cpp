#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n;
	cin >> n;
	string s;
	cin >> s;
	priority_queue<pair<int, pair<int, int> >  > q;
	int a[n + 1];
	for(int i = 0; i < n; i++){
		cin >> a[i]; 
	}
	bool visited[n + 1];
	int l[n + 1]; int r[n + 1];
	for(int i = 0; i < n; i++){
		visited[i] = false;
		l[i] = i - 1;
		r[i] = i + 1; 
	} 
	for(int i = 0; i < n - 1; i++){
		if(s[i] != s[i + 1]){
			q.push(make_pair(-abs(a[i] - a[i + 1]), make_pair(-i, -i - 1)));
		}
	}
	vector<pair<int, int> > ans;
	while(!q.empty()){
		pair<int, pair<int, int> > temp;
		temp = q.top();
		q.pop();
		if(visited[-temp.second.second] || visited[-temp.second.first])
			continue;
		ans.push_back(temp.second);
		visited[-temp.second.second] = true;
		visited[-temp.second.first] = true;
		int lc = l[-temp.second.first];
		int rc = r[-temp.second.second];
		if(lc < 0 || rc >= n)
			continue;
		r[lc] = rc;
		l[rc] = lc;
		if(s[rc] != s[lc])
			q.push(make_pair(-abs(a[rc] - a[lc]), make_pair(-lc,-rc)));
	}
	cout << ans.size() << endl;
	for(int i = 0; i < ans.size(); i++){
		cout << -ans[i].first + 1 << ' ' << -ans[i].second + 1 << endl;
	}
	return 0;
} 
  				    	   	 							 				  	