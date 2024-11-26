#include <bits/stdc++.h>
using namespace std;

using ll = long long;



class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        
    }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    LCA g(5);
    g.add_edge(0,1);g.add_edge(1,2);g.add_edge(1,3);g.add_edge(0,4);
    g.build();
    int d=g.get_dist(2,4);
    for(int i=0;i<=d;++i){
    	cout<<g.get_kth_node_on_path(2,4,i)<<'\n';
    }

    return 0;
}
