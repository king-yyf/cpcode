#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void dbg(A x) { cout<<x<<' ';}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

// 集合最多有11个

struct DSU {
    vector<int> p, siz;
    DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) { return siz[get(x)]; }
    vector<vector<int>> groups() {
        vector<vector<int>> res(p.size());
        for (int i = 0; i < p.size(); i++) res[get(i)].push_back(i);
        res.erase(
            remove_if(res.begin(), res.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
};

// struct Bits {
//     int clz(int x) {return x == 0 ? 64 : __builtin_clz(x);} // 二进制中前导0的个数
//     int clz(long long x) {return x == 0 ? 64 : __builtin_clzll(x);} // 前导0
//     int ctz(int x) {return x == 0 ? 0 : __builtin_ctz(x);} // 二进制中后缀0的个数
//     int ctz(long long x) {return x == 0 ? 0 : __builtin_ctzll(x);} // 后缀0 (long long)
//     int pct(int x) {return __builtin_popcount(x);} // 二进制中1的个数
//     int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
//     int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
//     int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);} // ceil(log(2)), minimum x s.t. n <= 2^x
//     int ffs(int x) {return __builtin_ffs(x);} // x的最后一位1的是从后向前第几位,eg: 100100, return 3.
//     int prt(int x) {return __builtin_parity(x);} //x二进制中1的个数模2的结果
//     int prt(long long x) {return __builtin_parityll(x);} //prt long long
//     bool get(int x, int i) {return (x & (1 << i)) != 0;} // 获取第i位
//     void set(int &x, int i) {x |= (1 << i);}            // 将x第i位设为1
//     void reset(int &x, int i) {x &= (~(1 << i));}      //  将x第i位清0
//     void flip(int &x) {x = ~x;};        // 翻转x的每一位
//     void flip(int &x, int i) {x ^= (1 << i);};        // 翻转第i位
//     void flip(int &x, int l, int r) {x ^= makemask(l, r);} // 翻转第l位到第r位
//     void resetleft(int &x, int i) {x &= ((1 << i) - 1);} // 清零最高位至第i位(包括第i位和最高位)
//     void resetright(int &x, int i) {x &= (-1 << (i + 1));} // 清零第i位至第0位(包括第i位和第0位)
//     void set(int &x, int i, int v) { v ? set(x, i) : reset(x, i);} // 将x的第i位设置为v
//     bool ispow(int x) {return (x & (x - 1)) == 0;}   // 判断x是否为2的整数次方
//     vector<int> gray(int n) {vector<int> a(1<<n); for(int i=0; i<(1<<n); ++i) a[i]=i^(i>>1); return a;}
//     int hamming(int x, int y){return pct(x ^ y);} // x,y 二进制的汉明距离
//     int setback1(int k) {return (1 << k) - 1;}  // 返回低k位全为1的数(k从1开始)
//     int countback1(int x) {return ctz(~x);} //  二进制中后缀1的个数
//     int makemask(int l, int r) {return setback1(r + 1) ^ setback1(l);} // 第l位到第r位为1，其余为0的数
//     string tostr(int x) {string s; for(int i=lg(x);i>=0;--i) s.push_back(get(x, i) + '0'); return s;} // 转为二进制字符串
// } B;

// template<typename F> // 按递增顺序枚举二进制包含k个1且小于2^n的数字
// void kbits(int n, int k, F &&f) {
//     if (k == 0) { f(0); return;}
//     for (int s = (1 << k) - 1, x, y; s < 1 << n;) {
//         f(s);
//         x = __builtin_ctz(s), y = __builtin_ctz(~s >> x);
//         s += (1 << x) + (1 << (y - 1)) - 1;
//     }
// }
// template<typename F> // 按递减顺序枚举二进制包含k个1且小于2^n的数字
// void kbits_rev(int n, int k, F &&f) {
//     if (k == 0) { f(0); return;}
//     for (int s = B.makemask(n - k, n - 1), x = 0, y; x != k;) {
//         f(s);
//         x = __builtin_ctz(~s), s = s ^ ((1 << x) - 1), y = __builtin_ctz(s);
//         B.flip(s, y - x - 1, y);
//     }
// }
// template<typename F>  // 递增枚举二进制状态x的所有子集
// void submasks(int x, F &&f) {
//     for (int s = 0;;s = s ^ (1 << __builtin_ctz(s ^ x) + 1) - 1 & x) { f(s); if (s == x) break;}
// }
// template<typename F>  // 递减枚举二进制状态x的所有子集
// void submasks_rev(int x, F &&f) {
//     for (int s = x;;s = (s - 1) & x) { f(s); if (s == 0) break;}
// }
// template<typename F> // 枚举二进制状态x的所有小于2^n的超集，
// void supermasks(int n, int x, F &&f) {
//     for (int s = x; s < 1 << n; s = (s + 1) | x) { f(s);}
// }
// template<typename F>  // 递增枚举某个元素的所有含有 k 个 1 的子状态
// void subkbits(int x, int k, F &&f) {
//     if (k > __builtin_popcount(x)) return;
//     vector<int> res(33);
//     for (int i = 0, j = 0; i < 32; ++i)
//         if (x & (1 << i)) res[++j] = x & ((1 << (i + 1)) - 1);
//     for (int s = res[k], back, a;;) {
//         f(s);
//         back = B.setback1(B.ctz(s)) & x;
//         if (back >= (s ^ x)) break;
//         a = B.ctz(x - s - back);
//         int md = B.setback1(a) & s;
//         s += (1 << a) + res[B.pct(md) - 1] - md;
//     }
// }
// template<typename F>  // 递减枚举某个元素的所有含有 k 个 1 的子状态
// void subkbits_rev(int x, int k, F &&f) {
//     if (k > __builtin_popcount(x)) return;
//     vector<int> res(33);
//     for (int i = 0, j = 0; i < 32; ++i)
//         if (x & (1 << i)) res[++j] = x & ((1 << (i + 1)) - 1);
//     for (int s = x - res[B.pct(x) - k], back;;) {
//         f(s);
//         back = B.setback1(B.ctz(x ^ s)) & x;
//         if (back >= s) break;
//         s ^= back ^ (B.setback1(B.ctz(s ^ back) + 1) & x);
//         s ^= res[B.pct(s) - k];
//     }
// }

struct SCC {
    int n, cnt = 0;
    vector<pair<int, int>> edges;
    vector<int> low, dfn, ids, in, out;
    explicit SCC(int n) : n(n), low(n), dfn(n, -1), ids(n){}
    void add_edge(int from, int to) { edges.push_back({from, to}); }

    void scc_ids() {
        vector<int> start(n + 1), elist(edges.size()), visited;
        for (auto &e : edges) 
            start[e.first + 1]++;
        for (int i = 1; i <= n; ++i) 
            start[i] += start[i - 1];
        auto counter = start;
        for (auto &e : edges)
            elist[counter[e.first]++] = e.second;
        int now_dfn = 0;
        visited.reserve(n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = dfn[v] = now_dfn++;
            visited.push_back(v);
            for (int i = start[v]; i < start[v + 1]; i++) {
                auto to = elist[i];
                if (dfn[to] == -1) {
                    self(self, to);
                    low[v] = min(low[v], low[to]);
                } else {
                    low[v] = min(low[v], dfn[to]);
                }
            }
            if (low[v] == dfn[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    dfn[u] = n, ids[u] = cnt;
                    if (u == v) break;
                }
                cnt++;
            }
        };
        for (int i = 0; i < n; i++) if (dfn[i] == -1) dfs(dfs, i);
        in.assign(cnt, 0);
        for (auto& x : ids) {
            x = cnt - 1 - x;
            in[x]++;
        }
    }

    vector<vector<int>> scc(bool cal_degree = false) {
        scc_ids();
        vector<vector<int>> groups(cnt);
        for (int i = 0; i < cnt; ++i) groups[i].reserve(in[i]);
        for (int i = 0; i < n; i++) groups[ids[i]].push_back(i);
        if (cal_degree) {
            in.assign(cnt, 0), out.assign(cnt, 0);
            for (auto &[from, to]: edges) {
                int x = ids[from], y = ids[to];
                if (x != y) in[y]++, out[x]++;
            }
        }
        return groups;
    }
};



int cal(int x){
	int c=0;
	while(x){
		c+=x%10;
		x/=10;
	}
	return c;
}

map<int,int>mp;
int get(int x){
	if(x<10)return x;
	if(mp.count(x)) return mp[x];
	return mp[x]=get(cal(x));
}

void ac_yyf(int tt) {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    SCC g(n);

    for(int i=1;i+11<=n;++i){
    	g.add_edge(i-1,i+11-1);
    	g.add_edge(i+11-1,i-1);
    	// d.merge(i-1,i+11-1);
    }
    vector<int> f(n);
    f0(n)f[i]=get(a[i]);
    for(int i=0;i<n;++i){
    	for(int j=i+1;j<n;++j){
    		if(f[i]==f[j]) {
    			g.add_edge(i,j);
    			g.add_edge(j,i);
    		}
    	}
    }
    auto p=d.groups();
    int m=sz(p);

    // for(auto&x:p)wt(x);
    // 	wt("----\n");
    vector<int> ans(n);
    ans[n-1]=n;
    for(int i=1;i<(1<<m);++i) {
    	int cnt=pct(i);
    	vector<int> vis(n); 
    	for(int j=0;j<m;++j){
    		if((i>>j)&1) {
    			for(auto&x:p[j]){
    				vis[x]=1;
    			}
    		}
    	}
    	int x1=0;
    	f0(n)if(vis[i])x1++;
    	// dbg("i=",i,"cnt=",cnt,"x1=",x1,nl);
    	cmx(ans[cnt-1],x1);
    }
    for(int i=1;i<n;++i)
    	cmx(ans[i],ans[i-1]);
    wt(ans);
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
