#include<bits/stdc++.h>
using namespace std;


template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int N=2e5+5;


long long a[N];

struct tree
{
    long long l,r,pre,add;
}t[N<<2];
void build(long long p,long long x,long long y)
{
    t[p].l=x;t[p].r=y;
    if(x==y)
    {
        t[p].pre=a[x];
        return ;
    }
    long long mid=x+y>>1;
    build(p<<1,x,mid);
    build(p<<1|1,mid+1,y);
    t[p].pre=max(t[p<<1].pre,t[p<<1|1].pre);
}
void change(long long p,long long x,long long y,long long z)
{
    if(x<=t[p].l&&t[p].r<=y)
    {
        t[p].pre=z;
        return ;
    }
    long long mid=t[p].l+t[p].r>>1;
    if(x<=mid)
        change(p<<1,x,y,z);
    if(y>mid)
        change(p<<1|1,x,y,z);
    t[p].pre=max(t[p<<1].pre,t[p<<1|1].pre);
}
long long ask(long long p,long long x,long long y)
{
    long long ans=0;
    if(x<=t[p].l&&t[p].r<=y)
    {
        ans=max(ans,t[p].pre);
        return ans;
    }
    long long mid=t[p].l+t[p].r>>1;
    if(x<=mid)
        ans=max(ans,ask(p<<1,x,y));
    if(y>mid)
        ans=max(ans,ask(p<<1|1,x,y));
    return ans;
}



class Solution{
public:
    long long maxScore(int n, vector<vector<int>>& b) {

    	memset(t,0,sizeof t);
    	memset(a,0,sizeof a);
        sort(b.begin(), b.end(),[&](auto&x, auto &y){
        	if(x[1]==y[1]) return x[0]<y[0];
        	return x[1]<y[1];
        });

        build(1,1,n);
        long long s;
        long long mx=0;
        for(int i=0;i<n;++i){
        	int x=b[i][0],y=b[i][1];
        	//[x,y]
        	
        	s=ask(1,1,y);
    
        	long long p=b[i][2];
        	p=p+ask(1,1,x);
        	s=max(s,p);
        	change(1,y,y,s);
        	mx=max(mx,s);
        }
        mx=max(mx,ask(1,1,n));
        return mx;
    
    }
};

int main(){
    Solution so;
    long long n=5;
    vector<vector<int>> a={{1,5,4}, {1,3,10}, {3,5,5}, {1,2,1}, {2,3,2}};
    auto s=so.maxScore(n,a);
    cout<<s<<"\n";
    return 0;
}
