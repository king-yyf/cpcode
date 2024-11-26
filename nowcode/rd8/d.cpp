#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

inline bool check(int x,int y){
    ll res=(ll)x*y,z=(ll)sqrt(res);
    return z*z==res;
}




int solve(int n){
    int u,v;
    vector<int> value(n+1),degrees(n+1),flag(n+1),color(n+1);
    vector<vector<int>> edges(n+1);
    for(int i=1;i<=n;i++){
        cin>>value[i];
    }
    for(int i=1;i<n;i++){
        cin>>u>>v;
        edges[u].push_back(v);
        edges[v].push_back(u);
        degrees[u]++,degrees[v]++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(degrees[i]==1){
            q.push(i);
        }
    }
    int ans=0;
    while(!q.empty()){
        int top=q.front();
        q.pop();
        flag[top]=1;
        for(auto& p:edges[top]){
            if(!flag[p]){
                if(!color[top]&&!color[p]&&check(value[top],value[p])){
                    color[top]=1,color[p]=1;
                    ans+=2;
                }
                if(--degrees[p]==1){
                    q.push(p);
                }
            }
        }
    }
    return ans;
}

//优先考虑叶节点,拓扑排序
int main() {
    int n;
    while(cin>>n){
        cout<<solve(n)<<endl;
    }
}
// 64 位输出请用 printf("%lld")