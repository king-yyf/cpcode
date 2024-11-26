#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void ac(){
    int n;cin>>n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    auto b=a;
    sort(b.begin(), b.end());
    if(a==b){
        cout<<"0\n";
        return;
    }
    map<int,vector<int> > mp;
    for (int i = 0; i < n; ++i) {
        mp[b[i]].push_back(i);    
    }
    int ans=0;
    vector<vector<int>> p;
    vector<int> vis(n);
    for(int i=0;i<n;++i){
        if(!mp[a[i]].size()) continue;
        vector<int> tmp;
        int j=i;
        while(!vis[j]){
            tmp.push_back(j);
            int k=j;
            vis[j]=1;
            j=mp[a[j]].back();
            mp[a[k]].pop_back();
        }
        if(tmp.size()>1){
            ans+=tmp.size()+1;
            p.push_back(tmp);
        }
    }
    cout<<ans<<"\n";
    for(auto&v:p){
        int m=v.size();
        for(int i=0;i<=m;++i){
            cout<<v[i%m]+1<<" "<<m<<"\n";
            for(auto&x:v){
                cout<<x+1<<" ";
            }cout<<"\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;cin>>t;while(t--){
        ac();
    }

    return 0;
}
