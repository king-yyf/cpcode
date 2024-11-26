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
#define fi first
#define se second
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

const int mod = 1e9+7; // 998244353;
const double PI = acos(-1.0);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;


template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    // @param n `0 <= n`
    // @return minimum non-negative `x` s.t. `n <= 2**x`
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

int op(int a, int b){
    return a+b;
}

int e() {
    //INF ,满足 op(e(), a) = op(a, e()) = a,  min(a, e()) = a
    return 0; 
}

void solve(int tt) {
    rd(n,m);
    vector<int> a(n);
    rd(a);
    long long c=0;
    segtree<int, op, e> s1(n+1),s2(n+1),s3(n+1); 
    for(int i=0;i<n;++i){
    	if(a[i]==1){
    		s1.set(i,1);
    	}else if(a[i]==2){
    		s2.set(i,2);
    	}else{
    		s3.set(i,3);
    	}
    }
    for(int t=0;t<m;++t){
    	int x,y,z;
    	rd(x,y,z);
    	x--;z--;
    	int p=a[x];
    	if(p==1){
    		s1.set(x,0);
    	}else if(p==2){
    		s2.set(x,0);
    	}else{
    		s3.set(x,0);
    	}
    	a[x]=y;


    	// dbg(a);

    	if(y==1){
    		s1.set(x,y);
    	}else if(y==2){
    		s2.set(x,y);
    	}else{
    		s3.set(x,y);
    	}

    	int s=s1.all_prod()+s2.all_prod()+s3.all_prod();
    	if(s%2!=0) {
    		c+=-1;
    		continue;
    	}

    	int x1=s1.prod(0,z+1),y1=s1.prod(z+1,n);
    	int x2=s2.prod(0,z+1),y2=s2.prod(z+1,n);
    	int x3=s3.prod(0,z+1),y3=s3.prod(z+1,n);

    	int l=x1+x2+x3,r=y1+y2+y3;

    	if(l==r) continue;

    	int c1=x1+y1,c2=(x2+y2)/2,c3=(x3+y3)/3;

    	// dbg("c1=",c1,"c2=",c2,"c3=",c3,'\n');

    	int mi,mx,u=z+1;

    	if(u<=c1) {
    		mi=u;
    	}else if(u<=c1+c2){
    		mi=c1+(u-c1)*2;
    	}else{
    		mi=c1+2*c2+(u-c1-c2)*3;
    	}

    	if(u<=c3){
    		mx=3*u;
    	}else if(u<=c3+c2){
    		mx=3*c3+(u-c3)*2;
    	}else{
    		mx=3*c3+2*c2+(u-c3-c2);
    	}

    	// dbg("s=",s,"mi=",mi,"mx=",mx,'\n');

    	if(s/2<mi||s/2>mx){
    		c+=-1;
    		continue;
    	}

    	int ss=s/2;

    	int q;

    	// dbg("l=",l,"ss=",ss,'\n');
    	if(l<ss){
    		int p=ss-l;
    		int t=min(y3/3,x1);

    		int w=min(x1-t,y2/2)+min(x2/2,y3/3-t);

    		if(p%2==0){
    			if(t*2>=p){
    				q=p/2;
    			}else{
    				if(w<p-2*t) q=-1;
    				else q=t+p-2*t;
    			}
    		}else{
    			if(t*2>=p){

    				if(w<1)q=-1;
    				else q=p/2+1;

    			}else{
    				if(w<p-2*t) q=-1;
    				else q=t+p-2*t;
    			}
    		}
    	}else{
    		int p=l-ss;
    		int t=min(x3/3,y1);

    		int w=min(y1-t,x2/2)+min(y2/2,x3/3-t);

    		if(p%2==0){
    			if(t*2>=p){
    				q=p/2;
    			}else{
    				if(w<p-2*t) q=-1;
    				else q=t+p-2*t;
    			}
    		}else{
    			if(t*2>=p-1){
    				if(w<1)q=-1;
    				else q=p/2+1;

    			}else{
    				if(w<p-2*t) q=-1;
    				else q=t+p-2*t;
    			}
    		}
    	}

    	
    	// dbg("q=",q,"z=",z,'\n');
    	c+=q;

    }
    cout<<c<<"\n";
}
int main(){
	ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    // cout << fixed << setprecision(10);

    freopen("/Users/yangyf/Downloads/worklife_balance_chapter_1_validation_input.txt","r",stdin);
	freopen("/Users/yangyf/Desktop/cpcode/google/metaHackerCup/round2/d1_ans1.txt","w",stdout);


    int T = 1;
    cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
    	cout << "Case #" << case_i << ": ";
        solve(case_i);
    }

	return 0;
}
