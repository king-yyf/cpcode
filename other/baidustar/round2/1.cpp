#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 7;
int root[MAXN],n,q,sze,num;//size 内存池的大小
ll a[MAXN],s[MAXN],b[MAXN];

struct HJT_tree{
	int l,r,cnt;//cnt记录出现次数 sum记录和 val记录节点的值
	ll sum,val;
}tree[MAXN*40];

void build(int &now,int l,int r){
	now = ++sze;
	tree[now].cnt = tree[now].sum = tree[now].val = 0;
	if(l == r) return ;
	int mid = (l+r)>>1;
	build(tree[now].l,l,mid);
	build(tree[now].r,mid+1,r);
}

void modify(int &now,int pre,int l,int r,int p,int val){
	tree[now = ++sze] = tree[pre];
	tree[now].cnt++,tree[now].sum += val;
	if(l == r){
		tree[now].val = val;
		return ;
	}
	int mid = (l+r)>>1;
	if(p <= mid) modify(tree[now].l,tree[pre].l,l,mid,p,val);
	else modify(tree[now].r,tree[pre].r,mid+1,r,p,val);
}
//查前k大值，因为节点存的是值 所以找大的 应该先往右边找 看右边（也就是大的）的数量符合情况嘛
ll query(int now,int pre,int l,int r,int k){
	if(l == r) return tree[now].val * k;//因为一个值可能出现多次 那么计算答案的时候要把他们都算上
	int mid = (l+r)>>1;
	int tmp = tree[tree[now].r].cnt - tree[tree[pre].r].cnt;
	if(tmp >= k) return query(tree[now].r,tree[pre].r,mid+1,r,k);
	else return query(tree[now].l,tree[pre].l,l,mid,k-tmp) + 
				tree[tree[now].r].sum - tree[tree[pre].r].sum;//注意左边的k要变成k-tmp的形式
}

int getid(ll x){ return lower_bound(b+1,b+1+num,x)-b; }

int main(){
	memset(root,0,sizeof(root));
	sze = 0;
	int q,k,x;
	scanf("%d%d%d%d",&n,&q,&k,&x);
	for(int i = 1;i <= n;i ++){
		scanf("%lld",&a[i]);
		b[i] = a[i];
		s[i] = s[i-1] + (1ll*i*i);//这里i会爆 所以开ll
	}
	/*****离散化 + 初始化****/
	sort(b+1,b+1+n);
	num = unique(b+1,b+1+n)-b-1;
	build(root[0],1,num);
	for(int i = 1;i <= n;i ++){
		int p = getid(a[i]);
		modify(root[i],root[i-1],1,num,p,a[i]);
	}
	int l,r;
	while(q--){
		scanf("%d%d",&l,&r);
		ll ans = query(root[r],root[l-1],1,num,k);
		// cout<<"l="<<l<<", r="<<r<<", ans="<<ans<<", \n";
		if(ans>=x){
			puts("Y");
		}else{
			puts("N");
		}
	}
	return 0;
}
