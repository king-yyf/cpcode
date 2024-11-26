#include<bits/stdc++.h>
using namespace std;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

int bct(long long x){return __builtin_popcountll(x);}
int lg2(int x){return x==0?0:31-__builtin_clz(x);} //x>=0, floor(log2(x)) 
long long fbs(function<bool(long long)> f, long long& lb, long long rb) {  // first true binary search
    while(lb<rb) {
        long long mb=(lb+rb)/2;
        f(mb)?rb=mb:lb=mb+1; 
    } 
    return lb;
}
long long lbs(function<bool(long long)> f, long long& lb, long long rb) {  // last true binary search
    while(lb<rb) {
        long long mb=(lb+rb+1)/2;
        f(mb)?lb=mb:rb=mb-1; 
    } 
    return lb;
}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    bool f=1;
    each(a, x) if(f==1) {wt(a); f=0;} else {cout<<' ';wt(a);}
}
const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

class Solution {
public:
    bool chk(string s){
        int c=0;
        each(x,s){
            if(x=='(')c++;
            else c--;
            if(c<0) return 0;
        }
        return c==0;
    }
    int n,m;
    vector<vector<char>> g;
    int o;
    string s;
    int c;
    void dfs(int x,int y){
        s+=g[x][y];
        if(g[x][y]=='(')c++;
        else c--;
        if(x==n-1&&y==m-1){
            if(c==0) o=1;
        }
        if(c<0) return;
        if(x+1<n) dfs(x+1,y);
        if(y+1<m) dfs(x,y+1);
        // cout<<s<<c<<"\n";
        s.pop_back();
        
        if(g[x][y]=='(')c--;
        else c++;
    }
    void printPathTPtoBR(int *mat, int i, int j, int m, int n, int *path, int pi) {
       if (i == m - 1) {
          for (int k = j; k < n; k++)
             path[pi + k - j] = *((mat + i*n) + k);
          for (int l = 0; l < pi + n - j; l++)
             cout << path[l] << " ";
             cout << endl;
          return;
       }
       if (j == n - 1) {
          for (int k = i; k < m; k++)
             path[pi + k - i] = *((mat + k*n) + j);
          for (int l = 0; l < pi + m - i; l++)
             cout << path[l] << " ";
             cout << endl;
          return;
       }
       path[pi] = *((mat + i*n) + j);
       printPathTPtoBR(mat, i+1, j, m, n, path, pi + 1);
       printPathTPtoBR(mat, i, j+1, m, n, path, pi + 1);
    }
    void findPath(int *mat, int m, int n) {
       int *path = new int[m+n];
       printPathTPtoBR(mat, 0, 0, m, n, path, 0);
    }
    bool hasValidPath(vector<vector<char>>& gg) {
        g=gg;
        n=sz(g),m=sz(g[0]);
        if((n+m)%2==0) return 0;
        o=0;s="";
        c=0;
        dfs(0,0);
        return o>0;
    }
};
