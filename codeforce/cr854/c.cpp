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
/*
a
aba
bab
bca
abba
abbba
ababa
bbab
bbabb
bbcca
agea
acffba
*/
void ac_yyf(int tt) {
	cin >> s;
	int  n = s.size();
	vector<int> c(26);
    for(auto &x : s)
        c[x - 'a']++;
    vector<array<int,2>> a;
    for (int i = 0; i < 26; ++i) {
        if (c[i] > 0) {
            a.push_back({i, c[i]});
        }
    }
    m = a.size();
    string t(n, ' ');
    int l = 0, r = n - 1;
    for (int i = 0; i < m; ++i) {
        char ch = a[i][0] + 'a';
        int cnt = a[i][1];
        for (int j = 0; j < cnt / 2; ++j) {
            t[l++] = ch;
            t[r--] = ch;
        }
        if (cnt % 2 != 0) {
            if (l == r) t[l] = ch;
            else {
                if (i == m - 2) {
                    char rem = a[m - 1][0] + 'a';
                    int x = a[m - 1][1];
                    for (int j = 0; j < x / 2; ++j) {
                        t[l++] = t[r -- ] = rem;
                    }
                    if (x % 2 != 0) {
                        t[l++] = rem;
                    }
                    t[r] = ch;
                } else {
                    for (int j = i + 1; j < m; ++j) {
                        for (int k = 0; k < a[j][1]; ++k) 
                            t[l++] = 'a' + a[j][0];
                    }
                    t[r] = ch;
                }
            }

            break;
        }
    }
    cout << t << "\n";
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
