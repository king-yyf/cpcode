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

void solve(int tt) {
    rd(n);
    vector<long long> a(n);
    rd(a);
    long long ss=Sum(a);
    int mx=Max(a);
    if(ss-mx<=mx){
        cout<<"Internationale!\n";
        return;
    }

    vector<pair<long long,int> > b(n);
    f0(n){
        b[i]={a[i],i};
    }
    sort(rall(b));

    long long x=b[0].first,y=b[1].first,z=b[2].first;

    string s(n,'B'),s1(n,'B'),s2(n,'B');
    s[b[0].second]='B';s[b[1].second]='Y',s[b[2].second]='Z';
    for(int i=3;i<n;++i){
        long long t=min({x,y,z});
        if(t==z){
            z+=b[i].first;
            s[b[i].second]='Z';
        }else if(t==y){
            y+=b[i].first;
            s[b[i].second]='Y';
        }else{
            x+=b[i].first;
            s[b[i].second]='B';
        }
    }

    long long x1=0,y1=0,z1=0;

    for(int i=n-1;i>=0;--i){
        long long t=min({x1,y1,z1});
        if(t==z1){
            z1+=b[i].first;
            s1[b[i].second]='Z';
        }else if(t==y1){
            y1+=b[i].first;
            s1[b[i].second]='Y';
        }else{
            x1+=b[i].first;
            s1[b[i].second]='B';
        }
    }

    random_device rd;

    shuffle(all(b),rd);

    long long x2=0,y2=0,z2=0;

    for(int i=n-1;i>=0;--i){
        long long t=min({x2,y2,z2});
        if(t==z2){
            z2+=b[i].first;
            s2[b[i].second]='Z';
        }else if(t==y2){
            y2+=b[i].first;
            s2[b[i].second]='Y';
        }else{
            x2+=b[i].first;
            s2[b[i].second]='B';
        }
    }


    vector<long long> c1={x,y,z},c2={x1,y1,z1},c3={x2,y2,z2};
    sort(all(c1));sort(all(c2));sort(all(c3));

    long long c=min({c1[0],c2[0],c3[0]});

    if(c1[0]+c1[1]>c1[2]){
        cout<<s<<"\n";
    }else if(c2[0]+c2[1]>c2[2]){
        cout<<s1<<"\n";
    }else if(c3[0]+c3[1]>c3[2]){
        cout<<s2<<"\n";
    }else{
        cout<<"Internationale!\n";
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
