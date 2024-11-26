#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
#define f1(e) for(int i=0;i<(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,b,e) for(int i=(b);i<(e);++i)
#define f4(i,b,e,s) for(int i=(b); (s)>0?i<(e):i>(e); i+=(s))
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 10;

class DiscountSystem {
public:
	struct Ac{
		int id,p,d,n,u;
	};
	map<int,int> m1;
	map<int,map<int,int>> mu;
	set<int> s;
	vector<Ac> v; 
    DiscountSystem() {
    	m1.clear();
    	v.clear();
    }
    
    void addActivity(int ad, int pt, int dt, int nb, int ut) {
    	v.push_back({ad,pt,dt,nb,ut});
    }
    
    void removeActivity(int id) {
    	s.insert(id);
    }
    
    int consume(int uid, int c) {
    	int mx=0,id=1010;
    	for(auto&e:v){
    		if(s.count(e.id)) continue;
    		if(c<e.p) continue;
    		if(mu[uid][e.id]>=e.u) continue;
    		if(m1[e.id]>=e.n) continue;
    		if(e.d>mx || (e.d==mx && e.id < id)){
    			mx=e.d;
    			id=e.id;
    		}
    	}
    	if(mx>0){
    		mu[uid][id]+=1;
    		m1[id]++;
    	}
    	return c-mx;
    }
};

/**
 * Your DiscountSystem object will be instantiated and called as such:
 * DiscountSystem* obj = new DiscountSystem();
 * obj->addActivity(actId,priceLimit,discount,number,userLimit);
 * obj->removeActivity(actId);
 * int param_3 = obj->consume(userId,cost);
 */