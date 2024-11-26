
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 100000 + 5;

int l,r,p;
int f[12][12][110];//f[i][j][k]表示i位数，最高位是j， 各位数之和为k

void init(){
    memset(f,0,sizeof(f));
    //预处理f数组。
    for(int i=0;i<10;i++)f[1][i][i]++;
    for(int i=2;i<12;i++){
        for(int j=0;j<10;j++){
            for(int k=j;k<110;k++){
                for(int x=0;x<10;x++){
                    f[i][j][k]+=f[i-1][x][k-j];
                }
            }
        }
    }
}
int dp(int n){
    if(!n)return 1;
    vector<int> a;//存储切出来的位数。
    while(n)a.push_back(n%10),n/=10;

    reverse(all(a));



    int last=0;//last存储前面数字之和。
    int ans=0;

    for(int i=0;i<sz(a);++i){
        int x=a[i];

        if(i==0) {

            for(int j=1;j<=a[i];++i) {
                
            }

        }else{

        }

    }

    for(int i=a.size()-1;i>=0;i--){
        int x=a[i];
        for(int j=0;j<x;j++){
            //走左边分支。为了凑成模n余0，则接下来的所有位数相加+last模n为0，所以我们来个-last即可。
            ans+=f[i+1][j][2*(i+1)-last];
        }
        last+=x;
        if(!i&&last==)ans++;//判断本身是否符合条件。
    }
    return ans;
}

int main(){
    init();
    ll n;
    cin>>n;

    string s=to_string(n);
    int m=sz(s);
    int ans=0;
    for(int i=1;i<m;++i){
        for(int j=0;j<10;++j) ans+=f[i][j][2*i];
    }
    

    cout<<dp(n)<<"\n";
    return 0;
}
