#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<bool> subset_sum(const vector<int> &a,int tgt){
    int n=a.size();
    int amax=0;
    for(int x:a)
        amax=max(amax,x);
    int brk=0,sbrk=0;
    while(brk<n&&sbrk+a[brk]<=tgt){
        sbrk+=a[brk];
        brk++;
    }
    if(brk==n&&sbrk!=tgt)
        return {};
    vector<int> dp(amax*2,-1);
    vector<vector<int>> prv(n,vector<int>(amax*2,-1));
    int offset=tgt-amax+1;
    dp[sbrk-offset]=brk;
    for(int i=brk;i<n;i++){
        vector<int> dp2=dp;
        vector<int> &prv_cur=prv[i];
        for(int j=amax-1;j>=0;j--)
            if(dp2[j+a[i]]<dp2[j]){
                prv_cur[j+a[i]]=-2;
                dp2[j+a[i]]=dp2[j];
            }
        for(int j=amax*2-1;j>=amax;j--)
            for(int k=dp2[j]-1;k>=max(dp[j],0);k--)
                if(dp2[j-a[k]]<k){
                    prv_cur[j-a[k]]=k;
                    dp2[j-a[k]]=k;
                }
        swap(dp,dp2);
    }
    if(dp[amax-1]==-1)
        return {};
    vector<bool> ans(n);
    int i=n-1,j=amax-1;
    while(i>=brk){
        int p=prv[i][j];
        if(p==-2){
            ans[i]=!ans[i];
            j-=a[i];
            i--;
        }else if(p==-1){
            i--;
        }else{
            ans[p]=!ans[p];
            j+=a[p];
        }
    }
    while(i>=0){
        ans[i]=!ans[i];
        i--;
    }
    return ans;
}

int main(){
    int n,a,b;
    cin>>n>>a>>b;
    a+=b; //x
    b=a-b-b;//y
    int sd=0;
    vector<int> d(n);
    for(int &x:d){
        cin>>x;
        sd+=x;
    }
    if(sd<abs(a)||sd<abs(b)||(sd+a)%2!=0||(sd+b)%2!=0){
        cout<<"No\n";
        return 0;
    }
    vector<bool> sol_a=subset_sum(d,(sd+a)/2),sol_b=subset_sum(d,(sd+b)/2);
    if(sol_a.empty()||sol_b.empty()){
        cout<<"No\n";
        return 0;
    }
    cout<<"Yes\n";
}