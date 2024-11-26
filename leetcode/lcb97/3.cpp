#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

template <typename _Tp, typename _Fp, typename _Compare = std::less<void>>
bool chmin(_Tp &a, const _Fp &b, _Compare __comp = _Compare()) { return __comp(b, a) ? a = b, true : false; }
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

namespace OY {
    template <typename _Tp>
    struct _TarjanCutEdgeWrap {
        struct _Edge {
            uint32_t a, b;
            _Tp distance;
            _Edge(uint32_t __a, uint32_t __b, _Tp __distance = _Tp()) : a(__a), b(__b), distance(__distance) {}
            const _Tp &getDis() const { return distance; }
        };
    };
    template <>
    struct _TarjanCutEdgeWrap<bool> {
        struct _Edge {
            uint32_t a, b;
            _Edge(uint32_t __a, uint32_t __b) : a(__a), b(__b) {}
            constexpr bool getDis() const { return true; }
        };
    };
    template <typename _Tp = bool>
    struct Tarjan_cut {
        using distance_type = std::conditional_t<std::is_same_v<_Tp, bool>, uint32_t, _Tp>;
        struct _Edge {
            uint32_t index, to;
        };
        std::vector<typename _TarjanCutEdgeWrap<_Tp>::_Edge> m_rawEdges;
        std::vector<_Edge> m_edges;
        std::vector<uint32_t> m_starts, m_dfn, m_low, m_adj, m_stack;
        uint32_t m_vertexNum, m_dfnCount, m_cutCount;
        std::basic_string<uint32_t> m_vbccBuffer, m_edgeVbccBuffer;
        std::vector<std::basic_string_view<uint32_t>> m_vbcc;
        Tarjan_cut(uint32_t __vertexNum, uint32_t __edgeNum) : m_starts(__vertexNum + 1, 0), m_dfn(__vertexNum, -1), m_low(__vertexNum, -1), m_adj(__vertexNum, 0), m_dfnCount(0), m_vertexNum(__vertexNum) { m_rawEdges.reserve(__edgeNum); }
        void addEdge(uint32_t __a, uint32_t __b) { m_rawEdges.push_back({__a, __b}); }
        void addEdge(uint32_t __a, uint32_t __b, _Tp __distance) { m_rawEdges.push_back({__a, __b, __distance}); }
        template <bool _GetVbcc = false>
        void calc() {
            for (auto &edge : m_rawEdges) {
                m_starts[edge.a + 1]++;
                if (edge.a != edge.b) m_starts[edge.b + 1]++;
            }
            std::partial_sum(m_starts.begin(), m_starts.end(), m_starts.begin());
            m_edges.resize(m_starts.back());
            uint32_t cursor[m_vertexNum];
            std::copy(m_starts.begin(), m_starts.begin() + m_vertexNum, cursor);
            for (uint32_t index = 0; index < m_rawEdges.size(); index++) {
                auto &edge = m_rawEdges[index];
                m_edges[cursor[edge.a]++] = _Edge{index, edge.b};
                if (edge.a != edge.b) m_edges[cursor[edge.b]++] = _Edge{index, edge.a};
            }
            if constexpr (_GetVbcc) {
                m_vbccBuffer.reserve(m_edges.size() + m_vertexNum);
                m_vbcc.reserve(m_vertexNum);
                m_stack.reserve(m_vertexNum);
            }
            auto dfs = [this](auto self, uint32_t i, uint32_t fromIndex) -> void {
                m_dfn[i] = m_low[i] = m_dfnCount++;
                uint32_t stackLength = m_stack.size();
                if constexpr (_GetVbcc) m_stack.push_back(i);
                if (~fromIndex) m_adj[i]++;
                for (uint32_t cur = m_starts[i], end = m_starts[i + 1]; cur < end; cur++)
                    if (auto &[index, to] = m_edges[cur]; !~m_dfn[to]) {
                        self(self, to, index);
                        if (m_low[to] < m_dfn[i])
                            chmin(m_low[i], m_low[to]);
                        else
                            m_adj[i]++;
                    } else if (index != fromIndex)
                        chmin(m_low[i], m_dfn[to]);
                if constexpr (_GetVbcc) {
                    if (!~fromIndex) {
                        if (!m_adj[i]) {
                            uint32_t len = m_stack.size() - stackLength;
                            m_vbcc.emplace_back(m_vbccBuffer.data() + m_vbccBuffer.size(), len);
                            m_vbccBuffer.insert(m_vbccBuffer.end(), m_stack.data() + stackLength, m_stack.data() + m_stack.size());
                        }
                        m_stack.resize(stackLength);
                    } else if (uint32_t parent = m_rawEdges[fromIndex].a ^ m_rawEdges[fromIndex].b ^ i; m_low[i] >= m_dfn[parent]) {
                        std::swap(m_stack[stackLength - 1], parent);
                        uint32_t len = m_stack.size() - stackLength + 1;
                        m_vbcc.emplace_back(m_vbccBuffer.data() + m_vbccBuffer.size(), len);
                        m_vbccBuffer.insert(m_vbccBuffer.end(), m_stack.data() + stackLength - 1, m_stack.data() + m_stack.size());
                        std::swap(m_stack[stackLength - 1], parent);
                        m_stack.resize(stackLength);
                    }
                }
            };
            for (uint32_t i = 0; i < m_vertexNum; i++)
                if (!~m_dfn[i]) dfs(dfs, i, -1);
            m_cutCount = std::count_if(m_adj.begin(), m_adj.end(), [](uint32_t x) { return x > 1; });
        }
        std::vector<std::basic_string_view<uint32_t>> getEdgeVBCC() {
            std::vector<std::basic_string_view<uint32_t>> res;
            std::vector<bool> visit(m_vertexNum, false);
            m_edgeVbccBuffer.reserve(m_rawEdges.size());
            m_stack.reserve(m_rawEdges.size());
            res.reserve(m_vertexNum);
            auto dfs = [&](auto self, uint32_t i, uint32_t fromIndex) -> void {
                visit[i] = true;
                uint32_t stackLength = m_stack.size();
                if (~fromIndex) m_stack.push_back(fromIndex);
                for (uint32_t cur = m_starts[i], end = m_starts[i + 1]; cur < end; cur++)
                    if (auto &[index, to] = m_edges[cur]; !visit[to])
                        self(self, to, index);
                    else if (index != fromIndex && m_dfn[to] <= m_dfn[i])
                        m_stack.push_back(index);
                if (!~fromIndex) {
                    if (!m_adj[i]) {
                        uint32_t len = m_stack.size() - stackLength;
                        res.emplace_back(m_edgeVbccBuffer.data() + m_edgeVbccBuffer.size(), len);
                        m_edgeVbccBuffer.insert(m_edgeVbccBuffer.end(), m_stack.data() + stackLength, m_stack.data() + m_stack.size());
                    }
                    m_stack.resize(stackLength);
                } else if (uint32_t parent = m_rawEdges[fromIndex].a ^ m_rawEdges[fromIndex].b ^ i; m_low[i] >= m_dfn[parent]) {
                    uint32_t len = m_stack.size() - stackLength;
                    res.emplace_back(m_edgeVbccBuffer.data() + m_edgeVbccBuffer.size(), len);
                    m_edgeVbccBuffer.insert(m_edgeVbccBuffer.end(), m_stack.data() + stackLength, m_stack.data() + m_stack.size());
                    m_stack.resize(stackLength);
                }
            };
            for (uint32_t i = 0; i < m_vertexNum; i++)
                if (!visit[i]) dfs(dfs, i, -1);
            return res;
        }
        std::pair<std::vector<distance_type>, std::vector<distance_type>> getCactusCyclePos() {
            std::pair<std::vector<distance_type>, std::vector<distance_type>> res;
            res.first.reserve(m_vertexNum);
            res.second.resize(m_vertexNum);
            std::vector<bool> visit(m_vertexNum, false);
            auto dfs = [&](auto self, uint32_t i, uint32_t fromIndex, distance_type d) -> distance_type {
                distance_type last = 0;
                res.second[i] = d, visit[i] = true;
                for (uint32_t cur = m_starts[i], end = m_starts[i + 1]; cur < end; cur++)
                    if (auto &[index, to] = m_edges[cur]; !visit[to])
                        last += self(self, to, index, d + m_rawEdges[index].getDis());
                    else if (index != fromIndex && m_dfn[to] < m_dfn[i])
                        last += d + m_rawEdges[index].getDis() - res.second[to];
                if (!~fromIndex) {
                    if (!m_adj[i]) res.first.push_back(last);
                    return 0;
                } else if (uint32_t parent = m_rawEdges[fromIndex].a ^ m_rawEdges[fromIndex].b ^ i; m_low[i] >= m_dfn[parent]) {
                    res.first.push_back(last);
                    return 0;
                } else
                    return last;
            };
            for (uint32_t i = 0; i < m_vertexNum; i++)
                if (!visit[i]) dfs(dfs, i, -1, 0);
            return res;
        }
        bool isCut(uint32_t __i) const { return m_adj[__i] > 1; }
        std::vector<uint32_t> getCuts() const {
            std::vector<uint32_t> cuts;
            cuts.reserve(m_cutCount);
            for (uint32_t i = 0; i < m_adj.size(); i++)
                if (m_adj[i] > 1) cuts.push_back(i);
            return cuts;
        }
    };
    Tarjan_cut(uint32_t, uint32_t)->Tarjan_cut<bool>;
}


class Solution {
public:
    bool isPossibleToCutPath(vector<vector<int>>& g) {
        int n=sz(g),m=sz(g[0]);
        if(n==1){
            if(m<=2) return 0;
        }
        if(m==1){
            if(n<=2) return 0;
        }
        auto get=[&](int x,int y){
            return x*m+y;
        };
        int e=0;
        f0(n){
            f2(j,m){
                if(g[i][j]==0) continue;
                int x=i+1,y=j;
                if(x>=0&&x<n&&y>=0&&y<m&&g[x][y]==1) e++;//f.addEdge(get(i,j),get(x,y));
                x=i,y=j+1;
                if(x>=0&&x<n&&y>=0&&y<m&&g[x][y]==1) e++;//f.addEdge(get(i,j),get(x,y));
            }
        }
        uint32_t cnt=n*m;
        OY::Tarjan_cut f(cnt,e);
        f0(n){
            f2(j,m){
                if(g[i][j]==0) continue;
                int x=i+1,y=j;
                if(x>=0&&x<n&&y>=0&&y<m&&g[x][y]==1) f.addEdge(get(i,j),get(x,y));
                x=i,y=j+1;
                if(x>=0&&x<n&&y>=0&&y<m&&g[x][y]==1) f.addEdge(get(i,j),get(x,y));
            }
        }
        f.calc<true>();
        auto p=f.getCuts();
       return sz(p)>0;
    }
};


#ifdef sigma-yyf
int main(){
    Solution so;
    vector<int> a{1,2,3,4};
    int k=0;
    // so.maximizeWin(a,k);
    return 0;
}
#endif
