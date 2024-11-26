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
#define yn(cond) cout << ((cond) ? "Yes" : "No") << "\n";
#define YN(cond) cout << ((cond) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI = acos(-1.0);
const int N = 2e5 + 5;

const int N = 200005,int ML = 5000005,K = 26;
struct Node {
    int cid[K];
    int odd_count[K];
    int end_count;
};

Node trie[ML];
int node_count = 1;

void addw(string& word) {
    int node = 0;
    for (char c : word) {
        int index = c - 'a';
        if (!trie[node].cid[index]) {
            trie[node].cid[index] = node_count++;
            memset(trie[node_count-1].odd_count, 0, sizeof(trie[node_count-1].odd_count));
        }
        node = trie[node].cid[index];
    }
    trie[node].end_count++;
}

long long dfs(int node, int depth, int odd_mask) {
    long long count = 0;
    if (depth % 2 == 1 && __builtin_popcount(odd_mask) == 25 && trie[node].end_count > 0) {
        count += trie[node].end_count;
    }
    for (int i = 0; i < K; i++) {
        if (trie[node].cid[i]) {
            int new_odd_mask = odd_mask ^ (1 << i);
            count += dfs(trie[node].cid[i], depth+1, new_odd_mask);
            for (int j = 0; j < K; j++) {
                if (j != i && trie[node].odd_count[j] % 2 == 1) {
                    int another_odd_mask = new_odd_mask ^ (1 << j);
                    count += dfs(trie[node].cid[i], depth+1, another_odd_mask);
                }
            }
        }
    }
    for (int i = 0; i < K; i++) {
        if (trie[node].odd_count[i] % 2 == 1) {
            int new_odd_mask = odd_mask ^ (1 << i);
            count += dfs(node, depth+1, new_odd_mask);
        }
    }
    return count;
}


void ac_yyf(int tt) {
    
    int n;
    rd(n);
    f0(n){
        string s;
        cin >> s;
        addw(s);
        int node = 0;
        for (char c : s) {
            int index = c - 'a';
            trie[node].odd_count[index]++;
            node = trie[node].cid[index];
        }
    }
    ll ans=dfs(0, 0, 0);
   wt(ans,'\n');

}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}