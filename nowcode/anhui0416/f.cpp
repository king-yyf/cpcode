#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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
#define yn(o) cout << ((o) ? "Yes" : "No") << "\n";
#define YN(o) cout << ((o) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
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
const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

template <typename Cost = long, typename CostSum = Cost>
auto fast_dense_hungarian(const vector<vector<Cost>>& cost) {
    static constexpr CostSum inf = numeric_limits<CostSum>::max() / 3;
    int V = cost.size();

    vector<int> row_mate(V, -1), col_mate(V, -1);
    vector<CostSum> pi(V, 0);

    auto residual = [&](int r, int c) { return cost[r][c] - pi[c]; };

    // column reduction, mate columns greedily
    vector<bool> transferrable(V, false);
    for (int col = 0; col < V; col++) {
        int row = 0;
        for (int u = 1; u < V; u++) {
            if (cost[row][col] > cost[u][col]) {
                row = u;
            }
        }
        pi[col] = cost[row][col];
        if (row_mate[row] == -1) {
            row_mate[row] = col;
            col_mate[col] = row;
            transferrable[row] = true;
        } else {
            transferrable[row] = false;
        }
    }

    // reduction transfer
    for (int row = 0; row < V; row++) {
        if (transferrable[row]) {
            int col = row_mate[row];
            int c = -1;
            for (int v = 0; v < V; v++) {
                if (v != col && (c == -1 || residual(row, c) > residual(row, v))) {
                    c = v;
                }
            }
            pi[col] -= residual(row, c);
        }
    }

    // augmenting row reduction
    for (int it = 0; it < 2; it++) {
        for (int row = 0; row < V; row++) {
            if (row_mate[row] != -1) {
                continue;
            }
            auto u1 = residual(row, 0);
            auto u2 = inf;
            int c1 = 0;
            for (int c = 0; c < V; c++) {
                auto u = residual(row, c);
                if (u < u1 || (u == u1 && col_mate[c1] != -1)) {
                    u2 = u1, u1 = u, c1 = c;
                } else if (u < u2) {
                    u2 = u;
                }
            }
            if (u1 < u2) {
                pi[c1] -= u2 - u1;
            }
            if (int r1 = col_mate[c1]; r1 != -1) {
                row_mate[r1] = col_mate[c1] = -1;
            }
            row_mate[row] = c1;
            col_mate[c1] = row;
        }
    }

    vector<int> cols(V);
    iota(begin(cols), end(cols), 0);

    for (int row = 0; row < V; row++) {
        if (row_mate[row] != -1) {
            continue;
        }
        vector<CostSum> dist(V);
        for (int c = 0; c < V; c++) {
            dist[c] = residual(row, c);
        }
        vector<int> pred(V, row);

        int scanned = 0, labeled = 0, last = 0;
        int col = -1;

        while (true) {
            if (scanned == labeled) {
                last = scanned;
                auto min = dist[cols[scanned]];
                for (int j = scanned; j < V; j++) {
                    int c = cols[j];
                    if (dist[c] <= min) {
                        if (dist[c] < min) {
                            min = dist[c];
                            labeled = scanned;
                        }
                        swap(cols[j], cols[labeled++]);
                    }
                }
                for (int j = scanned; j < labeled; j++) {
                    if (int c = cols[j]; col_mate[c] == -1) {
                        col = c;
                        goto done;
                    }
                }
            }
            assert(scanned < labeled);
            int c1 = cols[scanned++];
            int r1 = col_mate[c1];
            for (int j = labeled; j < V; j++) {
                int c2 = cols[j];
                auto len = residual(r1, c2) - residual(r1, c1);
                assert(len >= 0);
                if (dist[c2] > dist[c1] + len) {
                    dist[c2] = dist[c1] + len;
                    pred[c2] = r1;
                    if (len == 0) {
                        if (col_mate[c2] == -1) {
                            col = c2;
                            goto done;
                        }
                        swap(cols[j], cols[labeled++]);
                    }
                }
            }
        }

done:;
        for (int i = 0; i < last; i++) {
            int c = cols[i];
            pi[c] += dist[c] - dist[col];
        }

        int t = col;
        while (t != -1) {
            col = t;
            int r = pred[col];
            col_mate[col] = r;
            swap(row_mate[r], t);
        }
    }

    CostSum total = 0;
    for (int u = 0; u < V; u++) {
        total += cost[u][row_mate[u]];
    }
    return make_pair(total, move(row_mate));
}

void ac_yyf(int tt) {
    rd(n,m);

    vector<string> a(n);
    rd(a);
    if(m>4*n-4){
    	wt("-1\n");
    	return;
    }

    auto chk=[&](int x, int y){
    	if(x==0||y==0||x==n-1||y==n-1) return 1;
    	return 0;
    };

    int ans=0;
    vector<pair<int,int> > d,c;
    f0(n)f2(j,n){
    	if(a[i][j]=='#'&& !(chk(i,j))) d.emplace_back(i,j);
    	if(a[i][j]=='.'&&chk(i,j)) c.emplace_back(i,j);
    }

    int n1=sz(d),m1=sz(c);

    auto get=[&](int x,int y){
        return abs(d[x].first-c[y].first)+abs(d[x].second-c[y].second);
    };

    fast_dense_hungarian<int,int> g(n1+m1+2);

    // suisen:: MinCostFlow<int,int> g(n1+m1+2);
    int s=n1+m1,t=s+1;

    for(int i=0;i<n1;++i){
        g.add_edge(s,i,n1,0);
    }
    for(int i=0;i<m1;++i){
        g.add_edge(i+n1,t,1,0);
    }
    for(int i=0;i<n1;++i){
        for(int j=0;j<m1;++j){
            g.add_edge(i,j+n1,1,get(i,j));
        }
    }

    // auto [cap,cost]=g.min_cost_max_flow(s,t);
    // cout<<cost<<nl;
    auto [cost, assignment] = suisen::assignment_problem(d,c);
    std::cout << cost << '\n';

    // int m1=sz(c);
    // vector<int> vis(m1);

    // for(auto&[x,y]:d){
    // 	// if(tt==1){
    // 	// 	dbg(x,y,nl);
    // 	// }
    // 	int dis=1e9,p=-1;
    // 	f0(m1){
    // 		if(vis[i])continue;
    // 		int x1=c[i].first,y1=c[i].second;
    // 		int dis1=abs(x-x1)+abs(y-y1);
    // 		// dbg(dis1,dis,nl);
    // 		if(dis1<dis){
    // 			dis=dis1;
    // 			p=i;
    // 		}
    // 	}
    // 	// if(tt==1)dbg("ans=",ans,nl);
    // 	// vis[p]=1;
    // 	ans+=dis;
    // }
    // wt(ans,nl);

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
