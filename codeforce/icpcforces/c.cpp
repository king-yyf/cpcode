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

int n, m, q;
int x, y, k;
string s, t;

// #define ll long long
#define pb push_back
#define loop(a) for(int i = 0; i < a; i++)
#define loopv(i,a) for (int i = 0; i < a; i++)
#define rep(i,a,b) for (int i = a; i < b; i++)
// #define all(x) (x).begin(), (x).end()

struct segtree {
    struct node {
        int freq[41];
        ll cnt;
    };

    int size;
    vector<node> tree;
    node ZERO;

    node combine(node a, node b) {
        node result;
        memset(result.freq, 0, sizeof result.freq);

        loop(41) result.freq[i] = a.freq[i] + b.freq[i];
        ll count = a.cnt + b.cnt;

        rep (i, 0, 41) {
            rep (j, i + 1, 41) {
                count += b.freq[i] * a.freq[j];
            }
        }

        result.cnt = count;

        return result;
    }

    void build(vector<int> &a) {
        memset(ZERO.freq, 0, sizeof ZERO.freq);
        ZERO.cnt = 0;

        size = 1;
        while (size < a.size()) size *= 2;
        tree.assign(2 * size, ZERO);
        build(a, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx == lx + 1) {
            if (lx < a.size()) {
                memset(tree[x].freq, 0, sizeof tree[x].freq);
                tree[x].freq[a[lx]]++;
                tree[x].cnt = 0;
            }
        } else {
            int m = (lx + rx) / 2;
            build(a, 2*x+1, lx, m);
            build(a, 2*x+2, m, rx);
            tree[x] = combine(tree[2*x+1], tree[2*x+2]);
        }
    }

    void set(int idx, int v) {
        set(idx, v, 0, 0, size);
    }

    void set(int idx, int v, int x, int lx, int rx) {
        if (rx == lx + 1) {
            memset(tree[x].freq, 0, sizeof tree[x].freq);
            tree[x].freq[v]++;
            tree[x].cnt = 0;
        } else {
            int m = (lx + rx) / 2;
            if (idx < m)
                set(idx, v, 2*x+1, lx, m);
            else
                set(idx, v, 2*x+2, m, rx);
            tree[x] = combine(tree[2*x+1], tree[2*x+2]);
        }
    }

    ll calc(int l, int r) {
        return (calc(l, r, 0, 0, size)).cnt;
    }

    node calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r) return ZERO;
        if (rx <= l) return ZERO;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        return combine(calc(l, r, 2*x+1, lx, m), calc(l, r, 2*x+2, m, rx));
    }
};
void ac_yyf(int tt) {
    rd(n,k);
    auto get=[&](int x){
    	if(x==7)return 0;
    	else if(x==4)return 1;
    	else if(x==8)return 2;
    	return 3;
    };
    rd(s);
    vector<int> a(n);
    f0(n){
    	a[i]=get(s[i]-'0');
    }

    segtree st;
    st.build(a);
    int l=1,r=n,c=l;
    while(l<=r){
    	int md=(l+r)/2;
    	bool o=0;
    	for(int i=0;i+md<=n;++i){
    		int x=i,y=i+md;
    		if(st.calc(x,y)<=k){
    			o=1;
    			break;
    		}
    	}
    }
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
