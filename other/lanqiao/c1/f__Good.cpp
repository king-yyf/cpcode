#include <bits/stdc++.h>
using namespace std;
#define all(a) a.begin(), a.end()
#define pb push_back
#define ios ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
typedef unsigned long long ULL;
typedef long long LL;

const int N = 200010;

int n, q, tr[N], ans[N];
vector<int> l[N];
vector<pair<int, int>> qry[N];

struct seg{
    int l, r;
    
    seg(int l, int r): l(l), r(r) {};
    
    bool operator>(const seg &o) const {
        return r > o.r;
    };
};

void add(int x, int p){
    for(int i = x; i < N; i += i & -i)
        tr[i] += p;
}

int pre(int x){
    if(x == 0) return 0;
    int res = 0;
    for(int i = x; i; i -= i & -i)
        res += tr[i];
    return res;
}

void solve(){
    cin >> n >> q;
    while(n --){
        int L, R;
        cin >> L >> R;
        l[L].pb(R);
    }
    for(int i = 1; i <= q; i ++){
        int a, b;
        cin >> a >> b;
        qry[a].emplace_back(b, i);
    }
    
    priority_queue<seg, vector<seg>, greater<seg>> pq;
    
    for(int i = 1; i < N; i ++){
        for(int r: l[i]){
            add(i, 1), add(r + 1, -1);
            pq.emplace(i, r);
        }
        while(pq.size() && pq.top().r < i){
            auto [l, r] = pq.top(); pq.pop();
            add(l, -1), add(r + 1, 1);
        }
        int sz = pq.size();
        for(auto &[b, id]: qry[i]){
            // if(i==4&&sz==2){
            //     for(int k=1;k<=b;++k){
            //         cout<<pre(k)<<" ";
            //     }
            //     cout<<endl;
            // }
            
            // cout<<"i="<<i<<", sz="<<sz<<", "<<pre(b) - pre(b - 1)<<endl;
            ans[id] = sz - pre(b);
        }
    }
    
    cout << ans[1];
    for(int i = 2; i <= q; i ++)
        cout << "\n" << ans[i];
}

int main() {
    ios
    int t = 1; //cin >> t;
    while(t --) solve();

    return 0;
}

