#include<bits/stdc++.h>
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
 
#define ll long long
 
#define mod 1000000007
 
ll binpow(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
return res;
}
ll power(int x, int y)
{
    ll res = 1;
    while (y > 0) {
    if (y % 2 == 1)
        res = (res * x)%mod;
        y = y >> 1;
        x = ((x%mod) * (x%mod))%mod;
    }
    return res%mod;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,m;
    cin>>n>>m;
    vector<vector<char>>v(n,vector<char>(m,'#'));
    vector<vector<ll>>visM(n,vector<ll>(m,1e9));
    vector<vector<ll>>visP(n,vector<ll>(m,-1));
    queue<pair<ll,ll>>q;
    queue<pair<ll,ll>>qp;
    for(ll i=0;i<n;i++){
        // cout<<"Hey";
        for(ll j=0;j<m;j++){
            cin>>v[i][j];
            if(v[i][j]=='M'){
                visM[i][j] = 0;
                q.push({i,j});
            }
            if(v[i][j]=='A'){
                visP[i][j] = 0;
                qp.push({i,j});
            }
        }
    }
    ll delrow[4] = {0,1,-1,0};
    ll delcol[4] = {1,0,0,-1};
    // cout<<"Hey";
    while(!q.empty()){
        ll row = q.front().first;
        ll col = q.front().second;
        q.pop();
        for(ll i=0;i<4;i++){
            ll n_row = row+delrow[i];
            ll n_col = col+delcol[i];
            if(n_col<m and n_col>=0 and n_row>=0 and n_row<n and v[n_row][n_col]!='#' and visM[n_row][n_col]==1e9){
                visM[n_row][n_col] = visM[row][col]+1;
                q.push({n_row,n_col});
            }
        }
    }
    // string ans ="";
    bool f=0;
    while(!qp.empty()){
        ll row = qp.front().first;
        ll col = qp.front().second;
        // string s = qp.front().second;
        qp.pop();
        if(row==0 or row==n-1 or col==0 or col==m-1){
            // ans = s;
            f=1;
            break;
        }
        for(ll i=0;i<4;i++){
            ll n_row = row+delrow[i];
            ll n_col = col+delcol[i];
            if(n_col<m and n_col>=0 and n_row>=0 and n_row<n and v[n_row][n_col]!='#' and visP[n_row][n_col]==-1 and visP[row][col]+1<visM[n_row][n_col]){
                visP[n_row][n_col] = visP[row][col]+1;
                // if(i==0)
                //     qp.push({{n_row,n_col},s+"R"});
                // else if(i==1)
                //     qp.push({{n_row,n_col},s+"D"});
                // else if(i==2)
                //     qp.push({{n_row,n_col},s+"U"});
                // else if(i==3)
                //     qp.push({{n_row,n_col},s+"L"});
                qp.push({n_row,n_col});
            }
        }
    }
    if(f==0){
        cout<<"NO"<<endl;
    }
    else{
        cout<<"YES"<<endl;
        // cout<<ans.length()<<endl;
        // if(ans.length()>0)
        //     cout<<ans<<endl;
    }
    // for(ll i=0;i<n;i++){
    //     for(ll j=0;j<m;j++){
    //         cout<<visM[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    // bool f=0;
    // for(ll i=0;i<n;i++){
    //     if(v[i][0]=='.' and visM[i][0]>visP[i][0]){
    //         f=1;
    //         break;
    //     }
    //     if(v[i][m-1]=='.' and visM[i][m-1]>visP[i][m-1]){
    //         f=1;
    //         break;
    //     }
    // }
    // if(f){
    //     cout<<"YES"<<endl;
    //     return 0;
    // }
    // for(ll i=0;i<m;i++){
    //     if(v[0][i]=='.' and visM[0][i]>visP[0][i]){
    //         f=1;
    //         break;
    //     }
    //     if(v[n-1][i]=='.' and visM[n-1][i]>visP[n-1][i]){
    //         f=1;
    //         break;
    //     }
    // }
    // if(f){
    //     cout<<"YES"<<endl;
    // }
    // else{
    //     cout<<"NO"<<endl;
    // }
    return 0;
}