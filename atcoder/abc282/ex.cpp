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

long long mergeSort(int l, int r, vector<int>& nums, vector<int>& tmp) {
    if (l >= r) return 0;
    int m = (l + r) / 2;
    long long res = mergeSort(l, m, nums, tmp) + mergeSort(m + 1, r, nums, tmp);
    int i = l, j = m + 1;
    for (int k = l; k <= r; k++) tmp[k] = nums[k];
    for (int k = l; k <= r; k++) {
        if (i == m + 1) nums[k] = tmp[j++];
        else if (j == r + 1 || tmp[i] <= tmp[j]) nums[k] = tmp[i++];
        else {
            nums[k] = tmp[j++];
            res += m - i + 1; //如果是a[i] >= a[j]，tmp[i] <= tmp[j] 改为tmp[i] < tmp[j]
        }
    }
    return res;
}

long long revpairs(vector<int>& nums) {
    vector<int> tmp(nums.size());
    return mergeSort(0, nums.size() - 1, nums, tmp);
}


void solve() {
    int n;
    long long s;
    cin>>n>>s;
    vector<long long> a(n),b(n);
    for(auto&x:a)
    	cin>>x;
    for(auto&x:b)
    	cin>>x;
    vector<int> lmn(n, -1), rmn(n, n);
    stack<int> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && a[sk.top()] > a[i]) {
            rmn[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    sk = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && a[sk.top()] >= a[i]) {
            lmn[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    vector<long long> s(n +1);
    for(int i=0;i<n;++i)
    	s[i+1]=s[i]+b[i];

}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    solve();

    return 0;
}
