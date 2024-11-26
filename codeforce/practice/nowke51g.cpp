#include<bits/stdc++.h>
using namespace std;
#define fs first
#define sc second
#define all(x) (x).begin(),x.end()
#define dbg(x...) do{cout<<#x<<" -> ";err(x);}while (0)
void err(){cout<<'\n';}
template<class T, class... Ts>
void err(T arg, Ts... args) {
    cout<<arg<< ' ';
    err(args...);
}
typedef long long ll;
const int N=2e5+7;
const int MOD=1e9+7;
//-------------------------------------------
struct h2sh{
    typedef pair<int,int> W;
    #define x first
    #define y second
    const W P=W(1e9+7,1e9+9);
    const W B=W(131,151);
    vector<W> h,p;
    W mul(const W &a,const W &b){
        return W(1ll*a.x*b.x%P.x,1ll*a.y*b.y%P.y);
    }
    W add(const W &a,const W &b){
        return W((a.x+b.x)%P.x,(a.y+b.y)%P.y);
    }
    W sub(const W &a,const W &b){
        return W((a.x-b.x+P.x)%P.x,(a.y-b.y+P.y)%P.y);
    }
    h2sh(string s){
        h.resize(s.size()+1);
        p.resize(s.size()+1,W(1,1));
        for(int i=1;i<=s.size();i++){
            h[i]=add(mul(h[i-1],B),W(s[i-1],s[i-1]));
            p[i]=mul(p[i-1],B);
        }
    }
    W get(int l,int r){
        if(l>r)return W(0,0);
        return sub(h[r],mul(h[l-1],p[r-l+1]));
    }
};
//-------------------------------------------
void solve(){
    int n;
    string s;
    cin>>n>>s;
    ll ans=0;
    h2sh f(s);
    reverse(all(s));
    h2sh g(s);
    for(int i=1;i<=n;i++){
        int l=1,r=i/2,dif=0;
        while(l<=r){
            int mid=l+r>>1;
            
            if(f.get(1,mid)!=g.get(n-i+1,n-i+mid)){
                dif=mid;
                r=mid-1;
            }else l=mid+1;
        }
        if(!dif&&(i&1)){
            ans+=26;
        }else if(!dif){
            ans++;
        }else if(f.get(dif+1,i/2)==g.get(n-i+dif+1,n-i+i/2)){
            ans+=2;
        }
        cout<<"i= "<<i<<", "<<ans<<" "<<dif<<" "<<l<<" "<<r<<"\n";
    }
    cout<<ans<<'\n';
}
int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int T=1;
    // cin>>T;
    while(T--){
        solve();
    }
}
/*


*/