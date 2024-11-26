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

template<class Fun> class y_combinator_result {
    Fun _f;
public:
    template<class T> explicit y_combinator_result(T &&fun): _f(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return _f(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_comb(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }
template<typename T, typename F> //i < j,且f(a[i], a[j])为true的数对数目
long long count_pairs(T a, F &&f) {
	T buff(a.size());
	return y_comb([&](auto self, int start, int end) -> long long {
        if (end - start <= 1) return 0;
        int mid = (start + end) / 2, left = start, right = mid, n = 0;
        long long res = self(start, mid) + self(mid, end);
        while (left < mid || right < end)
            if (left < mid && (right == end || f(a[left], a[right]))) {
                buff[n++] = a[left++];
            } else {
                buff[n++] = a[right++], res += left - start;
            }
        copy(buff.begin(), buff.begin() + n, a.begin() + start);
        return res;
    })(0, int(a.size()));
}
 // 顺序对: count_pairs(a, less<int>()); // less_equal<int>()
 // 逆序对: count_pairs(a, greater<int>()); // greater_equal<int>()

long long swapCount(string &s, string &t) {
	int n = s.size();
	map<int,vector<int>> mp;
	for (int i = 0; i < n; ++i) {
		mp[t[i]].push_back(i);
	}
	vector<int> a(n);
	for (int i = n - 1; i >= 0; --i) {
		a[i] = mp[s[i]].back();
		mp[s[i]].pop_back();
	}
	return count_pairs(a,greater<int>());
}

void ac_yyf(int tt) {
    rd(s);
    map<char,int> mp;
    each(x,s)mp[x]++;
    vector<char> c;
    int id=0;
    for(auto&[k,v]:mp){
    	c.push_back(k);
    }
    id=sz(c);

    if(id==1){
    	cout<<s<<"\n";
    	return ;
    }

    vector<int> a;
    f0(id)a.push_back(i);
    long long mx=0;
    string ans;
    do {
    	string t;
    	for(auto&x:a){
    		char ch=c[x];
    		int cnt=mp[ch];
    		// dbg("ch=",ch,"cnt=",cnt,'\n');
    		for(int j=0;j<cnt;++j){
    			t+=ch;
    		}
    	}
    	// dbg(t,s,'\n');
    	// return;
    	auto p=swapCount(t,s);
    	if(p>mx){
    		mx=p;ans=t;
    	}
    }while(next_permutation(all(a)));
    cout<<ans<<"\n";
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
