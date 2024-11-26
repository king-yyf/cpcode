#include <bits/stdc++.h>
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
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

void ac_yyf(int tt) {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    if(is_sorted(all(a))){
    	wt("Yes\n");
    	wt("0");
    	return;
    }
    if(n==2){
    	wt("No\n");
    	return;
    }
    if(n==3){
    	if(a==vector<int>{1,2,3}){
    		wt("Yes\n");
    		wt("0");
    	}else if(a==vector<int>{2,3,1}){
    		wt("Yes\n");
    		wt("1\n1 1\n");
    	}else if(a==vector<int>{3,1,2}){
    		wt("Yes\n");
    		wt("1\n2 0\n");
    	}else{
    		wt("No\n");
    		return;
    	}
    	return;
    }

    

    vector<int> q;
    vector<ar2> c; 
    int k=n-2;
    for(int i=n;i>=4;--i){
    	int id=-1;
    	for(int j=0;j<n;++j){
    		if(a[j]==i) {
                id=j;
                break;
    		}
    	}
        if(id>0){
            int d=k-(n-i);
            c.push_back({id,d});
            q.clear();
            for(int j=0;j<id-1;++j){
                q.push_back(a[j]);
            }
            for(int j=id+1;j<n;++j){
                if(a[j]>i)break;
                q.push_back(a[j]);
            }
            q.push_back(a[id-1]);
            q.push_back(a[id]);
            while(sz(q)<n){
                q.push_back(q.back()+1);
            }
            a=q;
        }else{
            int d=k-(n-i);
            c.push_back({1,d});
            c.push_back({d,d});
            q.clear();
            for(int j=2;j<n;++j)
                q.push_back(a[j]);
            q.push_back(a[0]);
            q.push_back(a[1]);

            a=q;
            q.clear();
            for(int j=0;j<d-1;++j){
                q.push_back(a[j]);
            }
            for(int j=d+1;j<n;++j){
                if(a[j]>i)break;
                q.push_back(a[j]);
            }
            q.push_back(a[d-1]);
            q.push_back(a[d]);
            while(sz(q)<n){
                q.push_back(q.back()+1);
            }
            a=q;

        }
    }

    vector<int> b={a[0],a[1],a[2]};

    if(b==vector<int>{1,2,3}){
        ;
    }else if(b==vector<int>{2,3,1}){
        c.push_back({1,1});
    }else if(b==vector<int>{3,1,2}){
        c.push_back({2,0});
    }else if(b==vector<int>{1,3,2}){
        wt("No\n");
            return;
    }else if(b==vector<int>{3,2,1}){
        wt("No\n");
            return;
    }else if(b==vector<int>{2,1,3}){
        wt("No\n");
            return;
    }
    wt("Yes\n");
    wt(sz(c),nl);
    for(auto&e:c){
        wt(e[0],' ',e[1],nl);
    }
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
