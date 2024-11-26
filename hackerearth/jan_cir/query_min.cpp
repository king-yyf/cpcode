#include<bits/stdc++.h>
using namespace std;
const int mxn=3e5+100;
vector<pair<int,int>> queries[mxn];
vector<int> stk;
vector<long long> dp;
long long ans[mxn];
int a[mxn];
int get_idx(int r){
    int low = 0 , high = (int)stk.size()-1 , ans , mid ;
    for(;low<=high;){
        mid=(low+high)/2;
        if(stk[mid]<=r)ans=mid,high=mid-1;
        else low=mid+1;
    }
    return ans;
}
long long ask(int l,int r){
    int idx = get_idx(r), sz = (int)stk.size();
    return dp.back() - dp[idx] + 1LL * a[stk[idx]] * ( r-stk[idx]+1);
}
 
void solve(){
     int n,q;
     scanf("%d%d",&n,&q);
     
     for(int i=1;i<=n;++i)scanf("%d",&a[i]);
     for(int i=1,l,r;i<=q;++i){
         scanf("%d%d",&l,&r);
         queries[l].emplace_back(r,i);
     }
     a[n+1]=0 , stk = {n+1}, dp = {0};
     
     for(int i=n;i;--i){
         for(; a[i] <= a[stk.back()] ; stk.pop_back(),  dp.pop_back());
         long long now = dp.back();
         dp.push_back( now + 1LL * (stk.back()-i)*a[i]);
         stk.push_back(i);
         for(auto it : queries[i]) ans[it.second] = ask(i,it.first);
         queries[i].clear();
     }
     stk.clear(),dp.clear();
     for(int i=1;i<=q;++i)printf("%lld\n",ans[i]);
}
 
int main(){
    solve(); 
}