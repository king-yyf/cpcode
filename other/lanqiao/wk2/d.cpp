#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
struct fast_ios { fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(20); }; } fast_ios_;
#define all(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
#define rev(a) reverse((a).begin(), (a).end())
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
const std::vector<std::pair<int, int>> grid_dxs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int floor_lg(long long x) { return x <= 0 ? -1 : 63 - __builtin_clzll(x); }
template <class T1, class T2> T1 floor_div(T1 num, T2 den) { return (num > 0 ? num / den : -((-num + den - 1) / den)); }
template <class T1, class T2> std::pair<T1, T2> operator+(const std::pair<T1, T2> &l, const std::pair<T1, T2> &r) { return std::make_pair(l.first + r.first, l.second + r.second); }
template <class T1, class T2> std::pair<T1, T2> operator-(const std::pair<T1, T2> &l, const std::pair<T1, T2> &r) { return std::make_pair(l.first - r.first, l.second - r.second); }
template <class T> std::vector<T> sort_unique(std::vector<T> vec) { sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end()); return vec; }
template <class T> int arglb(const std::vector<T> &v, const T &x) { return std::distance(v.begin(), std::lower_bound(v.begin(), v.end(), x)); }
template <class T> int argub(const std::vector<T> &v, const T &x) { return std::distance(v.begin(), std::upper_bound(v.begin(), v.end(), x)); }
template <class IStream, class T> IStream &operator>>(IStream &is, std::vector<T> &vec) { for (auto &v : vec) is >> v; return is; }

template <class OStream, class T> OStream &operator<<(OStream &os, const std::vector<T> &vec);
template <class OStream, class T, size_t sz> OStream &operator<<(OStream &os, const std::array<T, sz> &arr);
template <class OStream, class T, class TH> OStream &operator<<(OStream &os, const std::unordered_set<T, TH> &vec);
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const pair<T, U> &pa);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::deque<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::set<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::multiset<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::unordered_multiset<T> &vec);
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const std::pair<T, U> &pa);
template <class OStream, class TK, class TV> OStream &operator<<(OStream &os, const std::map<TK, TV> &mp);
template <class OStream, class TK, class TV, class TH> OStream &operator<<(OStream &os, const std::unordered_map<TK, TV, TH> &mp);
template <class OStream, class... T> OStream &operator<<(OStream &os, const std::tuple<T...> &tpl);

template <class OStream, class T> OStream &operator<<(OStream &os, const std::vector<T> &vec) { for (auto v : vec) os << v << ' '; os << '\n'; return os; }
template <class OStream, class T, size_t sz> OStream &operator<<(OStream &os, const std::array<T, sz> &arr) { os << '['; for (auto v : arr) os << v << ','; os << ']'; return os; }
template <class... T> std::istream &operator>>(std::istream &is, std::tuple<T...> &tpl) { std::apply([&is](auto &&... args) { ((is >> args), ...);}, tpl); return is; }
template <class OStream, class... T> OStream &operator<<(OStream &os, const std::tuple<T...> &tpl) { os << '('; std::apply([&os](auto &&... args) { ((os << args << ','), ...);}, tpl); return os << ')'; }
template <class OStream, class T, class TH> OStream &operator<<(OStream &os, const std::unordered_set<T, TH> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::deque<T> &vec) { os << "deq["; for (auto v : vec) os << v << ','; os << ']'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::set<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::multiset<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::unordered_multiset<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const std::pair<T, U> &pa) { return os << '(' << pa.first << ',' << pa.second << ')'; }
template <class OStream, class TK, class TV> OStream &operator<<(OStream &os, const std::map<TK, TV> &mp) { os << '{'; for (auto v : mp) os << v.first << "=>" << v.second << ','; os << '}'; return os; }
template <class OStream, class TK, class TV, class TH> OStream &operator<<(OStream &os, const std::unordered_map<TK, TV, TH> &mp) { os << '{'; for (auto v : mp) os << v.first << "=>" << v.second << ','; os << '}'; return os; }
constexpr int N = 2e5 + 5;
constexpr char nl = '\n';
constexpr int MOD9 = 1000000007, MOD3 = 998244353;
int n, m;

long long arith_seq_sum(long long a1, long long d, long long n) {
    return a1 * n + n * (n - 1) * d / 2;
}

int main() {
    int a,b,s,t;
    cin>>a>>b>>s>>t;
    long long c=0;
    // for(int i=1;i<=a;++i)
    // for(int j=1;j<=b;++j){
    // 	int d=i%j;
    // 	if(d>=s&&d<=t){
    // 		c++;
    // 	}
    // }
    // cout<<c<<"\n";
    // c=0;

    // for(int i=7;i<=15;++i){
    // 	cout<<"mod="<<i<<'\n';
    // 	int cnt=0;
    // 	for(int j=1;j<=30;++j){
    // 		for(int k=1;k<=55;++k)
    // 			if(j%k==i)cnt++;
    // 	}
    // 	cout<<"cnt="<<cnt<<nl;
    // }
    // if(a<t)t=a;
    // if(a<s)s=a;
    // int len=t-s+1;

    // long long c1=0,c2=0;
    // for(int i=1;i<=b;++i){
    // 	if(a>s)
    // 	c1+=(a-s)/i;
    // }

    // for(int i=1;i<=b;++i){
    // 	if(a>t)
    // 	c2+=(a-t)/i;
    // }
    // // cout<<c1<<", "<<c2<<"\n";
    // c=(c1+c2)*len/2;

    // cout<<(1%2)<<" "<<(3%2)<<" "<<(1%3)<<" "<<(2%3)<<" \n";
    if(t==0){
    	ll c=0;
    	for(int i=1;i<=b;++i)
    		c+=a/i;
    	cout<<c<<nl;
    	return 0;
    }
    vector<long long> p(t+1);

    p[0]+=a;p[1]-=a;

    for(int i=2;i<=b;++i){
    	int x=a/i,y=a%i;
    	// [1,y] x + 1,  [y+1,i-1] x
    	p[0]+=x;
    	p[1]-=x;
    	p[1]+=x+1;
    	if(y+1<=t)p[y+1]-=x+1;
    	if(y+1<=t)p[y+1]+=x;
    	if(i<=t)p[i]-=x;
    }
    // for(int i=1;i<=b;++i)
    // 	{
    // 		p[0]+=a/i;
    // 		p[1]-=a/i;
    // 	}

    for(int i=1;i<=t;++i){
    	p[i]+=p[i-1];
    	
    }
    
    for(int i=s;i<=t;++i)
    	c+=p[i];

    // for(int i=1;i<=7;++i){
    // 	cout<<"i="<<i<<'\n';
    // 	for(int j=1;j<=9;++j){
    // 		cout<<"j="<<j<<", j%i="<<j%i<<'\n';
    // 	}
    // }

    // for(int i=1;i<=a;++i){

    // }

    cout<<c<<'\n';

}
