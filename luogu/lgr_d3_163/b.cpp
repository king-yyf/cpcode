#include <bits/stdc++.h>
using namespace std;
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx2")

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

const char nl = '\n';

const int M=4e6+4;
int n,m,root,l,r,p,cnt;

struct node{
	int l,r,size,val,lazy,key;
}tree[M];

void adde(int x){//建树,由于它是依次增加的,所以可以用x,不需要cnt 
	tree[x].val=x;
	tree[x].size=1;
	tree[x].key=rand();
	tree[x].l=tree[x].r=0;
}

void pushdown(int u){//下传懒标记,注意先交换,再下传,原因自己悟 
	swap(tree[u].l,tree[u].r);//交换节点
	//下传懒标记 
	tree[tree[u].l].lazy^=1;
	tree[tree[u].r].lazy^=1;
	tree[u].lazy=0;//清除标记 
}

void update(int u){//更新操作 
	tree[u].size=tree[tree[u].l].size+tree[tree[u].r].size+1;
}

void split(int u,int x,int &l,int &r){
	if(!u){
		l=r=0;
		return ;
	}
	if(tree[u].lazy)//处理当时的懒标记 
		pushdown(u);//下传懒标记 
	//按照区间分割 
	if(tree[tree[u].l].size+1<=x){//确定左儿子 
		l=u;
		split(tree[u].r,x-tree[tree[u].l].size-1,tree[u].r,r);//!注意右儿子的此时的size满足的值需要减去左儿子的个数  
	}
	else{//确定右儿子 
		r=u;
		split(tree[u].l,x,l,tree[u].l);//!注意左儿子此时的size不需要减去,理由建范浩强平衡树模板 
	}
	update(u);//同模板一样,更新size的值 
}

int merge(int l,int r){//合并操作 
	if(!l || !r)
		return l+r;
	//按照键值维护一个小根堆 
	if(tree[l].key<tree[r].key){//l当父节点 
		if(tree[l].lazy)//下传懒标记 
			pushdown(l);
		tree[l].r=merge(tree[l].r,r);//确定l的右儿子 
		update(l);return l;
	}
	else{//r当父节点 
		if(tree[r].lazy)//下传懒标记 
			pushdown(r);
		tree[r].l=merge(l,tree[r].l);//确定r的左儿子 
		update(r);return r;
	}	
}
vector<int> P;
void print(int u){//按照中序遍历 
	if(tree[u].lazy)//如果还存在懒标记则下传 
		pushdown(u);
	if(tree[u].l)//先遍历左儿子 
		print(tree[u].l);
	// printf("%d ",);//再遍历父节点  
	P.push_back(tree[u].val-1);
	if(tree[u].r)//最后遍历右儿子 
		print(tree[u].r);
}

template <class S,           // 线段树维护的数据信息
          S (*op)(S, S),    // 左右子节点信息合并到当前节点
          S (*e)(),
          class F,          // 懒标记维护的信息
          S (*tag)(F, S),  // 查询时给当去节点打上懒标记
          F (*merge)(F, F),  // 懒标记合并
          F (*id)()>        // 懒标记的默认值, 用于清空父节点的懒标记
struct LazySegTree {
    int n, size, log;
    vector<S> d;
    vector<F> lz;
    void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void push_down(int k, F f) {
        d[k] = tag(f, d[k]);
        if (k < size) lz[k] = merge(f, lz[k]);
    }
    void push(int k) {
        push_down(2 * k, lz[k]), push_down(2 * k + 1, lz[k]);
        lz[k] = id();
    }
    LazySegTree() : LazySegTree(0) {}
    explicit LazySegTree(int N) : LazySegTree(vector<S>(N, e())) {}
    explicit LazySegTree(const vector<S>& v) : n(int(v.size())) {
        log = ceil_lg(n), size = 1 << log;
        d = vector<S>(2 * size, e()), lz = vector<F>(size, id());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) pull(i);
    }
    int ceil_lg(int x) {   // minimum non-neg x s.t. `n <= 2^x`
        return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);
    }
    void set(int p, S x) {   // 0 <= p < n
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) pull(p >> i);
    }
    S get(int p) {     // Assert 0 <= p < n
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
    S get(int l, int r) {   // op(a[l], ..., a[r - 1])
        if (l == r) return e();
        l += size, r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sl = e(), sr = e();
        while (l < r) {
            if (l & 1) sl = op(sl, d[l++]);
            if (r & 1) sr = op(d[--r], sr);
            l >>= 1, r >>= 1;
        }
        return op(sl, sr);
    }
    S get_all() { return d[1]; }
    void apply(int p, F f) {   // 0 <= p < n
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = tag(f, d[p]);
        for (int i = 1; i <= log; i++) pull(p >> i);
    }
    void apply(int l, int r, F f) {  // a[i] = f(a[i]), [l, r)
        if (l == r) return;
        l += size, r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) push_down(l++, f);
            if (r & 1) push_down(--r, f);
            l >>= 1, r >>= 1;
        }
        l = l2, r = r2;
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) pull(l >> i);
            if (((r >> i) << i) != r) pull((r - 1) >> i);
        }
    }
    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) { // 0 <= l <= n, g(e()) is true
        if (l == n) return n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) sm = op(sm, d[l]), l++;
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) { // 0 <= r <= n, g(e()) is true
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm)))  sm = op(d[r], sm), r--;
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};

struct S {
    int sum, size;
    S():sum(0),size(0){}
    S(int s, int siz): sum(s), size(siz){}
};
using F = int;
S op(S x, S y) {
    return S{x.sum + y.sum, x.size + y.size};
}
S e() {
    return S();
};
S tag(F f, S s) { 
    return f == 0 ? s : S{s.size - s.sum, s.size};
}
F merge1(F x, F y) { 
    return x ^ y;
}
F id() { return 0; }  // 0: no tag

int main(){

	// freopen("/Users/yangyf/Downloads/KDOI_Round_6_J_down/revflip/revflip3.in","r",stdin);
	// freopen("/Users/yangyf/Downloads/KDOI_Round_6_J_down/revflip/ans3.out","w",stdout);

	scanf("%d",&n);

	for(int i=1;i<=n;i++){
		adde(i);
		root=merge(root,i);
	}
	for(int i=1,x,y;i<=n;i++){
		x=1,y=i;
		split(root,y,l,r);
		split(l,x-1,l,p);
		tree[p].lazy^=1;
		root=merge(merge(l,p),r);//合并 
	}
	P.reserve(n);
	print(root);//输出 
	vector<S> v(n);
	for (int i = 0,x; i < n; ++i) {
	    cin>>x;
	    v[i]={x,1};
	}

	LazySegTree<S, op, e, F, tag, merge1, id> seg(v);
	f0(n){
		seg.apply(0,i+1,1);
	}
	f0(n){
		printf("%d ", seg.get(P[i]).sum);
	}
	return 0;
} 

