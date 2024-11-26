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

int a[5][5],b[5][5];
int s1[10],s2[10];

void get(int x[][5], int p[]){
    int temp = 0;
    for (int j = 1; j <= 4; j++){
        if (x[1][j]) temp = x[1][j];
    }
    for (int j = 1; j <= 4; j++){
        if (x[3][j]){
            p[temp] = x[3][j];
            p[x[3][j]] = temp;
            break;
        }
    }
    p[x[2][1]] = x[2][3];
    p[x[2][3]] = x[2][1];
    p[x[2][2]] = 7;
    for (int i = 1; i <= 3; i++){
        for (int j = 1; j <= 4; j++){
            if (x[i][j] != 0 && p[x[i][j]] == 0){
                p[x[i][j]] = x[2][2];
                p[x[2][2]] = x[i][j];
                break;
            }
        }
    }
}

int get(int x[][5],int p[]){
	int c=0;
	f1(4){
		if(x[1][i])c=x[1][i];
	}
}
bool ac_yyf(int tt) {
    f1(3)for(int j=1;j<=4;++j)rd(a[i][j]);
    f1(3)for(int j=1;j<=4;++j)rd(b[i][j]);

    get(s,s1);get(a,s2);

    f1(6){
    	if(s1[i]!=s2[i])return 0;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        YN(ac_yyf(cas));
    }

    return 0;
}
