#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
mt19937 mrand(random_device{}()); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=1010000;
VI e[N],te[N];
int dfn[N],low[N],mt,w[N],tfa[N];
int lev[N],deg[N];
int _,n,m;
stack<int> st;
vector<PII> ble[N];

void adde(int u,int v) {
	te[u].pb(v); te[v].pb(u);
	tfa[v]=u;
}

void tarjan(int u,int f) {
	st.push(u);
	dfn[u]=low[u]=++mt;
	for (auto v:e[u]) {
		if (v==f) continue;
		if (!dfn[v]) {
			tarjan(v,u);
			if (low[v]>=dfn[u]) {
				te[m].clear();
				adde(u,m); adde(m,v);
				while (st.top()!=v) 
					adde(m,st.top()),st.pop();
				st.pop();
				ble[m].clear();
				++m;
			} else low[u]=min(low[u],low[v]);
		} else low[u]=min(low[u],dfn[v]);
	}
}

vector<PII> aux[N],eg[N];
int dir[N],fae[N],fa[N],dep[N],lnk[N],vst[N];
void orientation(int n,int s,int t,VI &a,VI &b) {
	int m=SZ(a);
	rep(i,0,n) {
		vst[i]=0;
		aux[i].clear();
		eg[i].clear();
	}
	rep(i,0,m) {
		eg[a[i]].pb(mp(b[i],i));
		eg[b[i]].pb(mp(a[i],i));
		dir[i]=-1;
	}
	function<void(int)> dfs=[&](int u) {
		for (auto p:eg[u]) {
			int v=p.fi;
			if (v==fa[u]) continue;
			if (!vst[v]) {
				vst[v]=1; lnk[u]=v; dep[v]=dep[u]+1;
				fa[v]=u; fae[v]=p.se;
				dfs(v);
			} else if (dep[v]<dep[u]) {
				aux[lnk[v]].pb(mp(u,p.se));
			}
		}
	};
	fa[s]=-1; dep[s]=0; vst[s]=1;
	dfs(s);
	assert(vst[t]);
	queue<PII> q; q.push(mp(t,1));
	while (!q.empty()) {
		int v=q.front().fi,d=q.front().se; q.pop();
		while (fa[v]!=-1&&dir[fae[v]]==-1) {
			dir[fae[v]]=d;
			for (auto p:aux[v]) {
				dir[p.se]=d;
				q.push(mp(p.fi,d^1));
			}
			v=fa[v];
		}
	}
	rep(i,0,m) assert(dir[i]!=-1);
//	printf("faq %d %d\n",s,t);
	rep(i,0,m) {
		if ((dep[a[i]]<dep[b[i]])!=dir[i]) swap(a[i],b[i]);
//		printf("gg %d %d\n",a[i],b[i]);
	}
}

int god[N],mark[N];
void dfs2(int u,int f) {
	if (u>=n&&god[u]==f) god[u]=-1;
	for (auto v:te[u]) {
		if (v==f) continue;
		if (u>=n&&god[u]==-1&&!lev[v]) god[u]=v;
		dfs2(v,u);
	}
	if (u>=n) {
		int lab=0;
		for (auto v:te[u]) {
			mark[v]=lab++;
		}
		VI a,b;
		for (auto p:ble[u]) a.pb(mark[p.fi]),b.pb(mark[p.se]);
//		printf("qaf %d %d\n",f,god[u]);
		orientation(lab,mark[f],mark[god[u]],a,b);
		rep(i,0,SZ(a)) {
			PII &p=ble[u][i];
			if (a[i]!=mark[p.fi]) swap(p.fi,p.se);
//			printf("ff %d %d\n",p.fi,p.se);
			e[p.fi].pb(p.se);
			deg[p.se]++;
		}
	}
}

int ans[N];


class Solution {
public:
    long long minimumCost(vector<int>& c, vector<vector<int>>& rs) {
    	n=SZ(c),m=SZ(rs);
		memset(dfn,0,sizeof dfn);
		memset(low,0,sizeof low);
		memset(w,0,sizeof w);
		memset(tfa,0,sizeof tfa);
		memset(lev,0,sizeof lev);
		memset(deg,0,sizeof deg);
    	for(int i=0;i<n;++i){
    		w[i]=c[i];
    		e[i].clear(),te[i].clear();
    	}
    	for(int i=0;i<m;++i){
    		e[rs[0]].pb(es[1]);
    		e[rs[1]].pb(es[0]);
    	}
    	m=n,mt=0;
    }
};