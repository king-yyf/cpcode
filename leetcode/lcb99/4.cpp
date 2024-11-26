#include <bits/stdc++.h>
using namespace std;

using ll = long long;


class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        set<pair<int,int>> s;
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (auto &e : guesses) {
            s.insert({e[0], e[1]});
        }
        
        int cnt = 0, ans = 0;
        function<void(int, int)> dfs = [&](int u, int fa) {
            for (auto &v: g[u]) if (v != fa){
                if (s.count({u, v})) cnt++;
                dfs(v,u);
            }
        };
        dfs(0, -1);

        function<void(int, int)> dfs2 = [&](int u, int fa) {
            if (cnt >= k) ans += 1;
            for (auto &v: g[u]) if (v != fa){
                if (s.count({u, v})) cnt--;
                if (s.count({v, u})) cnt++;
                dfs2(v,u);
                if (s.count({u, v})) cnt++;
                if (s.count({v, u})) cnt--;
            }
        };
        dfs2(0, -1);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    

    return 0;
}
