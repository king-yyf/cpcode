#include <bits/stdc++.h>
using namespace std;

const int N = 6e5 + 4, K = 24, M = K * N;
int tr[M][2], rt[N], sum[M], idx, tot;

void add(int x) {
	int p = rt[idx];
	rt[++idx] = tot + 1;
	for (int i = K - 1; ~i; --i) {
		sum[++tot] = sum[p] + 1;
		bool b = x & (1 << i);
		tr[tot][b] = tot + 1, tr[tot][!b] = tr[p][!b];
		p = tr[p][b];
	}
}

int query(int l, int r, int x) {
	if (l > r) return 0;
	l = rt[l], r = rt[r];
	int ans = 0;
	for (int i = K - 1; ~i; --i) {
		bool b = x & (1 << i);
		if (sum[tr[r][!b]] - sum[tr[l][!b]]) 
			ans += (1 << i), l = tr[l][!b], r = tr[r][!b];
		else 
			l = tr[l][b], r = tr[r][b];
	}
	return ans;
}

int n,m,x,y,k,q;
int main(){
	scanf("%d%d",&n,&m);
	add(0);
	y=0;
	for(int i=0;i<n;++i){
		scanf("%d",&x);
		add(y^=x);
	}
	while(m--){
		char op[4];
		scanf("%s",op);
		if(op[0]=='A'){
			scanf("%d",&x);
			add(y^=x);
		}else{
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			cout<<query(l-1,r,y^x)<<"\n";
		}
	}
	return 0;
}
