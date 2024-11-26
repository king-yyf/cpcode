#include <bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30732/problems/359088

using ll = long long;
ll n,p,q,x,y;
const int N=1e6;
ll a[N+4];
ll get(ll t){
	if(t<=0) return 1;
	if(t<=N) return a[t];
	return get(t/p-x)+get(t/q-y);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
   cin>>n>>p>>q>>x>>y;
   a[0]=1;
   for(int i=1;i<=N;++i){
   	 long long x1=i/p-x,x2=i/q-y;
   	 a[i]=(x1>=0?a[x1]:1)+(x2>=0?a[x2]:1);
   }
   cout<<get(n)<<"\n";
    return 0;
}
