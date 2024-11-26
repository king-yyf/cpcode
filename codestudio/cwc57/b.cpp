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
#define yn(cond) if (cond) cout<<"Yes\n"; else cout << "No\n";
#define YN(cond) if (cond) cout<<"YES\n"; else cout << "NO\n";
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}




int clearBit(int num, int i) {
    int mask = ~(1 << i);
    return num & mask;
}

int getmax(int x){
    int mx=0;
    for(int i=0;i<31;++i){
        if((x>>i)&1)mx=i;
    }
    return mx;
}

void get(int y, int &t){
// make t>=y;
    if(t>=y) return;

    int mx=getmax(y);
    int mn=-1,o=0;

    for(int i=mx;i>=0;--i){
        if(!(y>>i)&1){
            o=1;
            mn=i;
            break;
        }
    }
    if(o==0){
        t=(1<<(mx+1))-1;
    }else{
        for(int i=mn;i<=mx;++i) t=t|(1<<i);
    }
}


vector<int> constructArray(int n, int x, int y, int z) {
    vector<int> a(n);

    if(n==2){

        a[0]=y;
        a[1]=x^y;
        return a;
    }

    a[0]=y;

    if(x>z){

        int mx=getmax(x);

        a[n-1]=z;
        x=clearBit(x,mx);

        int t=x^y;

        get(y,t);

        a[n-2]=t;

        for(int i=1;i<n-2;++i)
            a[i]=y;

    } else{

        int t=x^y;

        get(y,t);

        a[n-1]=t;

        for(int i=1;i<n-1;++i)
            a[i]=y;

    }

    return a;
}

int main() {
    int t;
    cin>>t;
    while(t--){
        int n,x,y,z;
        cin>>n>>x>>y>>z;
        auto a=constructArray(n, x, y, z);
        cout<<"\n";
        for (int i = 0; i < n; ++i) {
            cout<<a[i]<<" \n"[i==n-1];    
        }
        cout<<"\n";

    }
    
    return 0;
}
