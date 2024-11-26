#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-1642
using ll = long long;

void wt(vector<ll> &a){
    for(auto&x:a){
        cout<<x<<' ';
    }
    cout<<'\n';
}

// https://vjudge.net/problem/CSES-1631

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int,pair<int,int> > mp;
    for (int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            if(mp.count(x-a[i]-a[j])){
                auto [x1,y1]=mp[x-a[i]-a[j]];
                cout<<x1<<' '<<y1<<' '<<i+1<<' '<<j+1<<'\n';
                return 0;
            }
        }
        for(int j=0;j<i;++j){
            mp[a[i]+a[j]]={j+1,i+1};
        }
    }
    cout<<"IMPOSSIBLE\n";
    return 0;
}
