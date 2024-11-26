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

const double eps=1e-10;
const double pi=acos(-1.0);

struct Point 
{
    double x,y;
    Point(double x=0,double y=0) : x(x), y(y) {}
};

//点与向量
typedef Point Vector;

Vector operator + (Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y); }

Vector operator - (Point A,Point B) { return Vector(A.x-B.x,A.y-B.y); }

Vector operator * (Vector A,double p) { return Vector(A.x*p,A.y*p); }

Vector operator / (Vector A,double p) { return Vector(A.x/p,A.y/p); }

bool operator < (const Point &a,const Point &b)
{
    return a.x<b.x || (a.x==b.x && a.y<b.y);
}

int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    else return x<0 ? -1 : 1;
}

bool operator == (const Point &a, const Point &b)
{
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}

double Dot(Vector A,Vector B) { return A.x*B.x + A.y*B.y; }

double Length(Vector A) { return sqrt(Dot(A,A)); }

double Angle(Vector A, Vector B) { return acos(Dot(A,B) / Length(A) / Length(B)); } //A和B夹角

double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }  //若A到B逆时针则为正，否则为负

double Area2(Point A,Point B,Point C) { return Cross(B-A,C-A); }    //三角形ABC的面积的两倍(有方向)

//点和直线
struct Line
{//直线定义
    Point v, p;
    Vector dir;
    double ang;
    
    Line() { }  //构造函数  
    Line(const Line& L): p(L.p), dir(L.dir), ang(L.ang) { }  
    Line(Point v, Point p):v(v), p(p){ dir=p-v; ang=atan2(dir.y,dir.x); }
    bool operator < (const Line& L) const //极角排序 
    {  
        return ang < L.ang;  
    } 
    Point point(double t)
    {//返回点P = v + (p - v)*t
        return v + dir*t;
    }
};

typedef vector<Point> Polygon;  

//平行四边形的判定（保证四边形顶点按顺序给出）  
bool isParallelogram(Polygon p) {  
    if (dcmp(Length(p[0]-p[1]) - Length(p[2]-p[3])) || dcmp(Length(p[0]-p[3]) - Length(p[2]-p[1]))) return false;  
    Line a = Line(p[0], p[1]);  
    Line b = Line(p[1], p[2]);  
    Line c = Line(p[3], p[2]);  
    Line d = Line(p[0], p[3]);  
    return dcmp(a.ang - c.ang) == 0 && dcmp(b.ang - d.ang) == 0;  
}  
  
//梯形的判定  
bool isTrapezium(Polygon p) {  
    Line a = Line(p[0], p[1]);  
    Line b = Line(p[1], p[2]);  
    Line c = Line(p[3], p[2]);  
    Line d = Line(p[0], p[3]);  
    return (dcmp(a.ang - c.ang) == 0 && dcmp(b.ang - d.ang)) || (dcmp(a.ang - c.ang) && dcmp(b.ang - d.ang) == 0);  
}  
  
//菱形的判定  
bool isRhombus(Polygon p) {  
    if (!isParallelogram(p)) return false;  
    return dcmp(Length(p[1]-p[0]) - Length(p[2]-p[1])) == 0;  
}  
  
//矩形的判定  
bool isRectangle(Polygon p) {  
    if (!isParallelogram(p)) return false;  
    return dcmp(Length(p[2]-p[0]) - Length(p[3]-p[1])) == 0;  
}  
  
//正方形的判定  
bool isSquare(Polygon p) {  
    return isRectangle(p) && isRhombus(p);  
} 

void solve(int tt) {
    vector<string> a(9);
    rd(a);
    vector<pair<double ,double >> c;
    f0(9){
    	f2(j,9)if(a[i][j]=='#')c.push_back({i,j});
    }
    n=sz(c);
    int t=0;

    auto chk=[&](vector<pair<int,int> > b){
    	map<int,int> mp;
    	for(int i=0;i<4;++i){
    		for(int j=i+1;j<4;++j){
    			int x0=b[i].first,y0=b[i].second,x1=b[j].first,y1=b[j].second;
    			auto dis=(x0-x1)*(x0-x1)+(y0-y1)*(y0-y1);
    			mp[dis]++;
    		}
    	}
    	for(auto&[k,v]:mp)if(v==4)return 1;
    };

    for(int i=0;i<n;++i){
    	for(int j=i+1;j<n;++j){
    		for(int k=j+1;k<n;++k){
    			for(int l=k+1;l<n;++l){
    				Polygon p;
    				p.push_back({c[i].first,c[i].second});
    				p.push_back({c[j].first,c[j].second});
    				p.push_back({c[k].first,c[k].second});
    				p.push_back({c[l].first,c[l].second});
    				bool o=0;

    				if(isSquare(p))o=1;
    				swap(p[1],p[2]);
			       if(isSquare(p))o=1;
			        swap(p[1],p[2]);
			        swap(p[2],p[3]);
			        if(isSquare(p))o=1;
			        if(o)t++;
    			}
    		}
    	}
    }
    cout<<t<<"\n";
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
