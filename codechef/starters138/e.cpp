#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,q;
    cin>>n>>q;
    vector<int> a(n),cnt(n+1);
    for (int i = 0; i < n; ++i) {
        cin>>a[i]; 
        cnt[a[i]]++;
    }
    ll c=0;
    for (int i = 1; i <= n; ++i) {
        c+=1ll*cnt[i]*(cnt[i]+1)/2;
    }
    for(int i=0;i<q;++i){
        int p,x;
        cin>>p>>x;
        p--;
        c-=cnt[a[p]];
        cnt[a[p]]--;
        a[p]=x;
        cnt[x]++;
        c+=cnt[x];
        cout<<c<<'\n';
    }
    return 0;
}
