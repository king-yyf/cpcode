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
const int N = 400 + 5;
int a[N]={0},b[N]={0},c[N]={0},d[N]={0};
char str1[N],str2[N];

void ac_yyf(int tt) {
    int i,j,k;
    scanf("%s %s",str1,str2);
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    memset(d,0,sizeof(d));
    int len1=strlen(str1),len2=strlen(str2);
    for (i=0;str1[i]!='.'&&i<len1;i++);
    k=0;
    for (j=i+1;j<len1;j++)  //小数从高位到低位 
        a[k++]=str1[j]-'0';
    k=0;
    for (j=i-1;j>=0;j--)        //整数从低位到高位 
        b[k++]=str1[j]-'0';
    k=0; 
    for (i=0;str2[i]!='.'&&i<len2;i++);
    for (j=i+1;j<len2;j++)  //小数从高位到低位 
        c[k++]=str2[j]-'0';
    k=0;
    for (j=i-1;j>=0;j--)        //整数从低位到高位 
        d[k++]=str2[j]-'0';
    k=0;
    for (i=N;i>=0;i--)      //小数部分相加 
    {
        a[i]+=c[i];
        if (i!=0&&a[i]>9)
        {
            a[i]%=10;
            a[i-1]++;
        }
        else if (i==0&&a[i]>9)
        {
            a[i]%=10;
            b[0]++;
        }
    }
    for (i=0;i<N;i++)       //处理整数部分相加 
    {
        b[i]+=d[i];
        if (b[i]>9)
        {
            b[i]%=10;
            b[i+1]++;
        }
    }
    for (i=N;i>=0&&b[i]==0;i--); //输出整数部分 
    for (j=i;j>=0;j--)
        printf("%d",b[j]);
    for (i=N;i>=0&&a[i]==0;i--);    //输出小数部分 
    if (i>=0)
    {
        printf(".");
        for (j=0;j<=i;j++)
        {
            printf("%d",a[j]); 
        }   
    }else{
        printf(".0");
    }
    printf("\n");
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
