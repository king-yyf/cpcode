#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007
#define SIZE 1e6+2
#define endl "\n"

void solve2(vector<vector<ll>>adj[],ll node,vector<ll>&vis,vector<ll>&dis){ 
    vis[node]=1; 
    for(auto x:adj[node]){ 
        if(!vis[x[0]]){ 
            dis[x[0]]=dis[node]^x[1]; 
            solve2(adj,x[0],vis,dis); 
        } 
    } 
} 

void solve(){
  ll n;  cin>>n; 
  vector<vector<ll>>adj[n]; 
  for(ll i=0;i<n-1;i++){ 
    ll u,v,w; 
    cin>>u>>v>>w; 
    u--; 
    v--; 
    adj[u].push_back({v,w}); 
    adj[v].push_back({u,w}); 
  } 

  vector<ll>dist(n),vis(n,0); 
  dist[0]=0; 
  solve2(adj,0,vis,dist); 
  map<ll,vector<ll>>mp; 
  for(ll i=0;i<n;i++){ 
    mp[dist[i]].push_back(i); 
     
  } 

  for(auto x:mp){ 
    if(x.second.size()>1){ 
        ll f=x.second[0]; 
        ll s=x.second[1]; 

        if(f==0 and s==n-1) cout<<1<<" "<<2<<" "<<2<<" "<<n-1<<endl; 
        else if(f==0) cout<<1<<" "<<n-1<<" "<<s+1<<" "<<n-1<<endl; 
        else if(s==n-1) cout<<1<<" "<<f+1<<" "<<1<<" "<<s+1<<endl; 
        else cout<<1<<" "<<f+1<<" "<<1<<" "<<s+1<<endl; 
        return; 
     } 
    } 
    map<ll,vector<vector<ll>>>mp2; 
    for(ll i=0;i<n;i++) 
    { 
        for(ll j=i+1;j<n;j++){ 
            mp2[dist[i]^dist[j]].push_back({i,j}); 
            if(mp2[dist[i]^dist[j]].size()>1){ 
                cout<<mp2[dist[i]^dist[j]][0][0]+1<<" "<<mp2[dist[i]^dist[j]][0][1]+1<<" "<<mp2[dist[i]^dist[j]][1][0]+1<<" "<<mp2[dist[i]^dist[j]][1][1]+1<<endl; 
                return; 
            } 
        } 
    } 
    cout<<-1<<endl; 
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll t; cin>>t;
    while(t--){
        solve();
    }
    return 0;
}