#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

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
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;
int n, m, k;

class Solution {
public:
    vector<int> stringIndices(vector<string>& a, vector<string>& q) {
        int n = a.size(), m = q.size();
        for (auto & s : a) {
        	reverse(s.begin(), s.end());
        }
        for (auto & s : q) {
        	reverse(s.begin(), s.end());
        }

        vector<pair<string ,int> > v(n + m);
        for (int i = 0; i < n; ++i) {
        	v[i] = {a[i], i};
        }
        for (int i = 0; i < m; ++i) {
        	v[i + n] = {q[i], i + n};
        }

        sort(v.begin(), v.end(), [&](auto &x, auto &y){
        	return x.first < y.first;
        });

        for (int i = 0; i < n + m; ++i) {
        	cout << v[i].first << ' ' << v[i].second << '\n';
        }


        vector<int> pre(m, -1), suf(m, n + m);

        for (int i = 0, cur = -1; i < n + m; ++i) {
        	if (v[i].second >= n) {
        		pre[v[i].second - n] = cur;
        	} else {
        		cur = i;
        	}
        }

        for (int i = n + m - 1, cur = n + m; i >= 0; --i) {
        	if (v[i].second >= n) {
        		suf[v[i].second - n] = cur;
        	} else {
        		cur = i;
        	}
        }

        // wt(pre);
        // wt(suf);


        vector<int> ans(n);

        auto calc_pre = [&](int x, int y) {
        	string &s = v[x].first;
        	string &t = v[y].first;

        	int c = 0;
        	for (int i = 0; i < s.size() && i < t.size(); i++) {
        		if (s[i] == t[i]) c++;
        		else break;
        	}
        	return c;
        };

        for (int i = 0; i < n + m; ++i) {
        	if (v[i].second >= n) {
        		int t = v[i].second - n;

        		int l = pre[t], r = suf[t];

        		int pre_len1 = -1, pre_len2 = -1;
        		int len1, len2, id1, id2;
        		if (pre[t] >= 0) {
        			pre_len1 = calc_pre(pre[t], i);
        			len1 = v[pre[t]].first.size();
        			id1 = v[pre[t]].second;
        		}
        		if (suf[t] < n + m) {
        			pre_len2 = calc_pre(suf[t], i);
        			len2 = v[suf[t]].first.size();
        			id2 = v[suf[t]].second;
        		}

        		if (pre_len1 >= 0) {
        			if (pre_len2 >= 0) {
        				if (pre_len1 > pre_len2) {
        					ans[t] = id1;
        				}else if (pre_len1 < pre_len2) {
        					if (len1 < len2) {
        						ans[t] = id1;
        					} else if (len1 > len2) {
        						ans[t] = id2;
        					} else {
        						ans[t] = min(id1, id2);
        					}
        				} else {
        					ans[t] = id2;
        				}
        			} else {
        				ans[t] = id1;
        			}
        		} else {
        			ans[t] = id2;
        		}
        	}
        }

        return ans;

    }
};


#ifdef sigma-yyf
int main(){
    vector<string> a{"abcdefgh","poiuygh","ghghgh"};
    vector<string> b{"gh","acbfgh","acbfegh"};
    Solution so;
    auto d = so.stringIndices(a, b);
    wt(d);
    cout<<'\n';
    return 0;
}
#endif
