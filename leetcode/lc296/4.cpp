#ifdef LOCAL
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
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
#define ln "\n";
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) {cout << x << " ";}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void wt(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void wt(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;
struct w {
    int x;  int y;
    bool operator < (const w& o) const {
        return x!=o.x ? x<o.x : y<o.y;
    }
};

class TextEditor {
public:
	list<char> s;
	list<char>::iterator it;
    TextEditor() {
    	s.clear();
    }
    
    void addText(string t) {
    	if(s.empty()){
    		each(x,t)s.push_back(x);
    		it=s.end();
    	}else{
    		if(it==s.end()){
    			each(x,t) s.push_back(x);
    			it=s.end();
    		}else{
    			each(x,t) s.insert(it,x);
    		}
    		
    	}
         auto itt=s.begin();
        cout<<"addText:\n";
        while(itt!=s.end()){
            cout<<*itt<<" ";
            itt++;
        }
        cout<<"\n";
    }
    
    int deleteText(int k) {
    	int c=0;
    	if(it==s.end()){
    		while(k>0&&!s.empty()){
    			s.pop_back();
    			c++;k--;
    		}
    		it=s.end();
    	}else{
    		auto it1=it;
    		while(k>0&&it1!=s.begin()){
    			it1--;
    			c++;
    			k--;
    		}
    		f0(c) s.erase(it1);
    	}

        auto itt=s.begin();
        cout<<"deleteText:\n";
        while(itt!=s.end()){
            cout<<*itt<<" ";
            itt++;
        }
        cout<<"\n";
    	return c;
    }
    
    string cursorLeft(int k) {
    	while(k>0&&it!=s.begin()){
    		k--;
    		it--;
    	}
    	auto it1=it;
    	int t=10,x=0;
        it1--;
        if(it1==s.begin()) return "";
        string s1;
    	while(t>0){
    		t--;
            s1+=*it1;
    		it1--;
            if(it1==s.begin()) break;
    		x++;
    	}
    	rev(s1);
        auto itt=s.begin();
        cout<<"cursorLeft:\n";
        while(itt!=s.end()){
            cout<<*itt<<" ";
            itt++;
        }
        cout<<"\n";
    	return s1;
    }
    
    string cursorRight(int k) {
    	while(k>0&&it!=s.end()){
    		k--;
    		it++;
    	}
    	auto it1=it;
    	int t=10,x=0;
        it1--;
        if(it1==s.begin()) return "";
        string s1;
        while(t>0){
            t--;
            s1+=*it1;
            it1--;
            if(it1==s.begin()) break;
            x++;
        }
        rev(s1);
        auto itt=s.begin();
        cout<<"cursorRight:\n";
        while(itt!=s.end()){
            cout<<*itt<<" ";
            itt++;
        }
        cout<<"\n";
    	return s1;

    }
};

#ifdef LOCAL
int main(){
    
    return 0;
}
#endif


//[null, null, 4, null, "etpractice", "leet", 4, "", "practi"]
