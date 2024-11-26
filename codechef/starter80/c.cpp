#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))

// template <bool _Forward, typename _Iterator>
// void FWT_bitxor(_Iterator first, _Iterator last) {
//     const uint32_t length = last - first;
//     for (uint32_t i = 1; i < length; i <<= 1)
//         for (uint32_t j = 0; j < length; j += i << 1)
//             for (auto it = first + j, it2 = first + j + i, end = first + j + i; it != end; ++it, ++it2) {
//                 auto x = *it, y = *it2;
//                 if constexpr (_Forward)
//                     *it = x + y, *it2 = x - y;
//                 else
//                     *it = (x + y) / 2, *it2 = (x - y) / 2;
//             }
// // }
// const int N=1<<4;
// int c[N];
void ac_yyf(int tt) {
	int n;
	cin>>n;
    vector<vector<pair<int,int>> > g(n);
    for(int i=1,u,v,w;i<n;++i){
    	cin>>u>>v>>w;
    	u--,v--;
    	g[u].emplace_back(v,w);
    	g[v].emplace_back(u,w);
    }
    vector<int> a(n);
    function<void(int, int, int)> dfs = [&](int u, int fa, int sum) {
    	a[u] = sum;
    for (auto v : g[u]) {
        if (v.first != fa) {
            dfs(v.first, u, sum ^ v.second);
        }
    }
    };
    dfs(0, -1,0);
    
    map<int,vector<int>>mp;
    f0(n)mp[a[i]].push_back(i);
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
    map<int,vector<array<int,2>>>mp2; 
    for(int i=0;i<n;i++) 
    { 
        for(int j=i+1;j<n;j++){ 
            mp2[a[i]^a[j]].push_back({i,j}); 
            if(mp2[a[i]^a[j]].size()>1){ 
                cout<<mp2[a[i]^a[j]][0][0]+1<<" "<<mp2[a[i]^a[j]][0][1]+1<<" "<<mp2[a[i]^a[j]][1][0]+1<<" "<<mp2[a[i]^a[j]][1][1]+1<<endl; 
                return; 
            } 
        } 
    } 
    cout<<-1<<endl; 
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
