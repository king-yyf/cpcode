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

int isSorted(int n, int x, vector<int>a) {

    if(is_sorted(a.begin(), a.end())) return 1;
    vector<int > b;
    for(int i=0;i<n;++i){
        if((a[i]&x)==x){
            b.push_back(a[i]);
        }
    }
    int m=b.size();
    sort(b.begin(), b.end());
    int j=0;
    for(int i=0;i<n;++i){
        if((a[i]&x)==x){
           a[i]=b[j++];
        }
    }
    
    return 0;
}

int main() {
    vector<int> a{6};
    cout<<longestSubarray(4,a)<<"\n";
    return 0;
}