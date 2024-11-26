// Hydro submission #65d440e05badb635620eabc8@1708409056575
/*
    配合状压的数位DP
    
    f[pos][s].first表示位数为pos,len~pos+1的出现的数的集合为s(用二进制数表示)
            的符合条件的数字的个数
    f[pos][s].second表示位数为pos,len~pos+1的出现的数的集合为s(用二进制数表示)
            的符合条件的数字的和
     
*/
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=1e5+5,mod=1000000007;
inline int rd(){
    int w = 1, s = 0;
    char c = getchar();
    for (; c < '0' || c > '9'; w *= (c == '-') ? -1 : 1, c = getchar());
    for (; c >= '0' && c <= '9'; s = 10 * s + (c - '0'), c = getchar());
    return s * w;
}
int l,r,k;
int mi[20]; 
int num[20];
PII f[20][1<<10]; 
PII add(PII x,PII y){
    return {(x.fi+y.fi)%mod,(x.se+y.se)%mod};
}
PII dfs(int pos,int sum,int s,bool lead,bool limit){      //返回值的第一维记录cnt,第二维记录sum 
        //位，当前有几个数，状态，是否有前导0,是否紧贴上界
    if(!pos){
        if(sum<=k) return {1,0};
        else return {0,0};
    } 
    if(!limit&&(~f[pos][s].fi)) return f[pos][s]; 
    int up=limit?num[pos]:9;
    PII res={0,0};
    for(int i=0;i<=up;i++){
        if(lead&&i==0)  //前导0的话就不能算进sum和s了
            res=add(res,dfs(pos-1,sum,s,true,limit&&i==up));
        else{
            PII tmp=dfs(pos-1 , (s>>i&1)?sum:sum+1 , s|(1<<i) , false , limit&&i==up);
            res=add(res , {tmp.fi,(tmp.se + i*mi[pos-1]%mod*tmp.fi%mod)%mod} ); 
            //注意这里res.se不仅要加上tmp.se，还要加上第pos位的i带来的贡献 
        }
            
    } 
    if(!limit) f[pos][s]=res;
    return res;
}
int solve(int x){
    int len=0;
    while(x) num[++len]=x%10,x/=10;
    for(int i=0;i<=18;i++)  
        for(int j=0;j<=1024;j++)
            f[i][j]={-1,0};
    return dfs(len,0,0,true,true).se;
}
signed main(){
    l=rd(),r=rd(),k=rd();
    mi[0]=1;
    for(int i=1;i<=18;i++) mi[i]=mi[i-1]*10%mod;
    printf("%lld",(solve(r)-solve(l-1)+mod)%mod);
    return 0;
}