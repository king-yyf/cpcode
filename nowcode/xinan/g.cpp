#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ar(x) array<int,x> 
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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> T f_div(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0));}
template <class T> T c_div(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0));}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
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
#ifdef sigma-yyf
#define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    cerr << s << ": " << h, ((cerr << ", " << t), ..., (cerr << "\n"));
}
#else
#define dbg(...) void(0)
#endif
template<class Fun> class Y_comb {
    Fun _f;
public:
    template<class T> explicit Y_comb(T &&fun): _f(forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...As) {return _f(ref(*this), forward<Args>(As)...);}
};
template<class Fun> decltype(auto) y_comb(Fun &&fun) { return Y_comb<decay_t<Fun>>(forward<Fun>(fun));}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;
constexpr char nl = '\n';
constexpr int inf = 1'061'109'567;
constexpr ll infll = 2'000'000'000'000'000'000;
constexpr int N = 2e5 + 5;
int n, m, q;
int x, y, k;
string s, t;

vector<vector<int>> mp = {
	{},
	{2,4},
	{1,2,9},
	{3,5},
	{2,3},
	{4,4},
	{1,4,9},
	{5,5},
	{2,5},
	{5,6},
	{1,2,6},
	{6,7},
	{2,2,7},
	{7,8},
	{2,2,8},
	{7,9},
	{2,2,9},
	{1,8},
	{1,2,3},
	{1,1,7},
	{1,1,2,2},
	{1,2,6},
	{1,1,2,2},
	{1,6},
	{1,2}
};

// map<int, vector<int>> mp = {
// 	{1,},
// 	{2,},
// 	{3,},
// 	{4,},
// 	{5,},
// 	{6,},
// 	{7,},
// 	{8,},
// 	{9,},
// 	{10,},
// 	{11,},
// 	{12,},
// 	{13,},
// 	{14,},
// 	{15,},
// 	{16,},
// 	{17,},
// 	{18,},
// 	{19,},
// 	{20,},
// 	{21,},
// 	{22,},
// 	{23,},
// 	{24,}
// };

void solve(int tt) {
    int a,b,c,d,e;
    rd(a,b,c,d,e);
    // 公共，A,B,A,B

    auto sm=[&](int x){
    	int ss=0;
    	for(auto&e:mp[x])
    		ss+=e;
    	return ss;
    };
    int s1=sm(a)+sm(b)+sm(d);
    int s2=sm(a)+sm(c)+sm(e);
    // dbg(s1,s2,nl);
    if(s1>16)s1=0;
    if(s2>16)s2=0;
    bool o1=0;
    if(s1>s2){
    	o1=1;
    }
    if(o1==0) {
    	wt("Who Will Win\n");
    	return;
    }


    auto get_max=[&](vector<int> &v)->pair<pair<int,vector<int>>,vector<int>>  {
    	map<int,int> m1;
    	each(x,v){
    		m1[x]++;
    	}
    	bool o=0,mx=0;
    	for(auto&[k,u]:m1){
    		if(u>=4){
    			o=1;
    			mx=k;
    		}
    	}
    	if(o){
    		vector<int> v1,v2;
    		each(x,v){
    			if(x==mx &&sz(v1)<4){
    				v1.push_back(x);
    			}else{
    				v2.push_back(x);
    			}
    		}
    		return {{1,v1},v2};
    	}

    	o=0;

    	vector<int> v3,v2;
    	for(auto&[k,u]:m1){
    		if(u==3){
    			v3.push_back(k);
    		}else if(u==2){
    			v2.push_back(k);
    		}
    	}

    	if(sz(v3)>0) {
    		int n1=sz(v3);
    		if(n1>=2) {
    			if (sz(v2)>0) {
    				int mx2=v2.back();
    				if(mx2>v3[n1-2]) {
    					// v3[n1-1], mx2
    					vector<int> ans1,ans2;
    					int cnt1=0,cnt2=0;
    					each(x,v){
    						if(x==v3[n1-1]) {
    							if(cnt1<3){
    								ans1.push_back(x);
    								cnt1++;
    							}
    							else ans2.push_back(x);
    						}else if(x==mx2){
    							if(cnt2<2){
    								ans1.push_back(x);
    								cnt2++;
    							}
    							else ans2.push_back(x);
    						}else{
    							 ans2.push_back(x);
    						}
    					}
    					return {{2,ans1},ans2};
    				}else{
    					// v3[n1-1], v3[n1-2]
    					vector<int> ans1,ans2;
    					int cnt1=0,cnt2=0;
    					each(x,v){
    						if(x==v3[n1-1]) {
    							if(cnt1<3){
    								ans1.push_back(x);
    								cnt1++;
    							}
    							else ans2.push_back(x);
    						}else if(x==v3[n1-2]){
    							if(cnt2<2){
    								ans1.push_back(x);
    								cnt2++;
    							}
    							else ans2.push_back(x);
    						}else{
    							 ans2.push_back(x);
    						}
    					}
    					return {{2,ans1},ans2};
    				}
    			}else{
    				// v3[n1-1], v3[n1-2]
    				vector<int> ans1,ans2;
					int cnt1=0,cnt2=0;
					each(x,v){
						if(x==v3[n1-1]) {
							if(cnt1<3){
								ans1.push_back(x);
								cnt1++;
							}
							else ans2.push_back(x);
						}else if(x==v3[n1-2]){
							if(cnt2<2){
								ans1.push_back(x);
								cnt2++;
							}
							else ans2.push_back(x);
						}else{
							 ans2.push_back(x);
						}
					}
					return {{2,ans1},ans2};
    			}
    		}else{
    			if(sz(v2)>0) {
    				// v3[n1-1], v2.back()
    				int mx2=v2.back();
    				vector<int> ans1,ans2;
					int cnt1=0,cnt2=0;
					each(x,v){
						if(x==v3[n1-1]) {
							if(cnt1<3){
								ans1.push_back(x);
								cnt1++;
							}
							else ans2.push_back(x);
						}else if(x==mx2){
							if(cnt2<2){
								ans1.push_back(x);
								cnt2++;
							}
							else ans2.push_back(x);
						}else{
							 ans2.push_back(x);
						}
					}
					return {{2,ans1},ans2};
    			}
    		}
    	}

    	sort(all(v));

    	o=0,mx=0;
    	
    	for(auto&[k,u]:m1){
    		if(m1.count(k+1)&&m1.count(k+2)&&m1.count(k+3)&&m1.count(k+4)){
    			o=1;mx=k;
    		}
    	}
    	if(o) {
    		set<int> s{mx,mx+1,mx+2,mx+3,mx+4};
    		vector<int> v1,v2;
    		each(x,v){
    			if(s.count(x)){
    				v1.push_back(x);
    				s.erase(x);
    			}else{
    				v2.push_back(x);
    			}
    		}
    		return {{3,v1},v2};
    	}

    	if(sz(v3)>0){
    		int mx=v3.back();
    		vector<int> ans1,ans2;
    		each(x,v){
    			if(x==mx&&sz(ans1)<3){
    				ans1.push_back(x);
    			}else{
    				ans2.push_back(x);
    			}
    		}
    		return {{4,ans1},ans2};
    	}


    	v2.clear();
    	for(auto&[k,u]:m1){
    		if(u==2){
    			v2.push_back(k);
    		}
    	}

    	if(sz(v2)>=2) {
    		int n1=sz(v2);
    		vector<int> ans1,ans2;
    		each(x,v){
    			if(x==v2[n1-1]||x==v2[n1-2]){
    				ans1.push_back(x);
    			}else{
    				ans2.push_back(x);
    			}
    		}
    		return {{5,ans1},ans2};
    	}else if(sz(v2)>0) {
    		vector<int> ans1,ans2;
    		each(x,v){
    			if(x==v2.back()){
    				ans1.push_back(x);
    			}else{
    				ans2.push_back(x);
    			}
    		}
    		return {{6,ans1},ans2};
    	}

    	vector<int> ans1,ans2;
    	// sort(all(v));
    	ans1.push_back(v.back());
    	v.pop_back();
    	ans2=v;
    	ans2.pop_back();
    	return {{7,ans1},ans2};
    };

    vector<int> c1,c2;
    for(auto&x:mp[a]){
    	c1.push_back(x);
    	c2.push_back(x);
    }
    for(auto&x:mp[b]){
    	c1.push_back(x);
    }
    for(auto&x:mp[c]){
    	c2.push_back(x);
    }
    for(auto&x:mp[d]){
    	c1.push_back(x);
    }
    for(auto&x:mp[e]){
    	c2.push_back(x);
    }
    // wt(c1);
    // wt(c2);

    bool o2=0; // 0：draw, 1:win, -1:loss

    sort(all(c1));
    sort(all(c2));

    if(c1==c2){
    	wt("Who Will Win\n");
    	return;
    }

    while(o2==0) {
    	auto p1=get_max(c1);
	    auto p2=get_max(c2);
	    auto x1=p1.first.first;
	    auto x2=p2.first.first;

	    // dbg(x1,x2);
	    // wt(p1.first.second);
	    // wt(p2.first.second);
	    if(x1!=x2) {
	    	if(x1>x2){
	    		o2=1;break;
	    	}
	    	else {
	    		o2=-1;break;
	    	}
	    }
	    auto &v1=p1.first.second;
	    auto &v2=p2.first.second;
	    sort(rall(v1));
	    sort(rall(v2));
	    if(v1!=v2){
	    	if(v1>v2){
	    		o2=1;break;

	    	}else {
	    		o2=-1;break;
	    	}
	    }
	    c1=p1.second;
	    c2=p2.second;
	    if(sz(c1)==0) {
	    	if(sz(c2)==0) {
	    		break;
	    	}
	    	o2=-1;
	    	break;
	    }
	    if(sz(c2)==0) {
	    	o2=1;
	    	break;
	    }
    }

    if(o1 && o2) {
    	wt("I Will Win\n");
    }else{
    	wt("Who Will Win\n");
    }

}
bool boolf(int tt) {
    return 0;
}

int main() {
    int T = 1, fun_type = 0;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        if (fun_type == 0) solve(cas);
        else if (fun_type == 1) cout << (boolf(cas) ? "Yes" : "No") << '\n';
        else cout << (boolf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
