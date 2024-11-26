#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define fr(i,a,b) for (int i=(a);i<(b);i++)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define yn(cond) if (cond) cout<<"Yes\n"; else cout << "No\n";
#define YN(cond) if (cond) cout<<"YES\n"; else cout << "NO\n";
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<A>& x) {wt(x);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}


// 最小字母CH是'a'，字母集大小K是26
template<char CH = 'a', int K = 26>
struct trie {
    struct node {
        array<int, K> child;
        int cnt[2]{0, 0};
        node () { memset(&child[0], -1, K * sizeof(int));}
    };

    vector<node> tr = {node()};

    trie(int tot_len = -1) {
        if (tot_len >= 0) tr.reserve(tot_len + 1);
    }

    int add(const string &s) {
        int p = 0; 
        for (char ch: s) {
            int u = ch - CH;
            if (tr[p].child[u] < 0) {
                tr[p].child[u] = int(tr.size());
                tr.emplace_back();
            }
            p = tr[p].child[u];
            tr[p].cnt[0]++;
        }
        tr[p].cnt[1]++;
        return p;
    }

    // prefix_of_s=1: trie中多少个字符串等于 s (如果count_prefix=1，求多少个字符串是s的前缀)
    // prefix_of_s=0: s是trie中多少个字符串的前缀 (如果count_prefix=1，对s的每个前缀也进行累加)
    int get(const string &s, int len, bool prefix_of_s = 0, bool count_prefix = 0) {
        int p = 0, ans = 0;
        for (int i = 0; i < len; ++i) {
        	char ch = s[i];
            if (count_prefix) ans += tr[p].cnt[prefix_of_s];
            p = tr[p].child[ch - CH];
            if (p < 0) break;
        }
        if (p >= 0) ans += tr[p].cnt[prefix_of_s];
        return ans;
    }
};



void solve(int tt) {
	int n;
    rd(n);
    trie<'a', 26> t;
    vector<string> a(n);
    f0(n){
    	cin>>a[i];
    	t.add(a[i]);
    }

    f0(n){
    	int l = 0, r = a[i].size();
    	while (l < r) {
    		int md = (l + r + 1) / 2;
    		int p = t.get(a[i], md, 0, 0);
    		if (p >= 2) l = md;
    		else r = md - 1;
    	}
    	cout<<l<<"\n";
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
