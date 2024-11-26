#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
typedef int long long llt;
    public:
    int mx_sum = 0;
    int mn_sum = 0;
    llt D[1000][1000];
    int Dig[1000];
    int mod = 1e9+7;
    


    
    //这里只需要用1个量表示状态，pre表示当前位的前一位数字
    //这里不需要lead参数，因为条件与0无关
    llt dfs(int pos,int sum,bool limit){
        if(sum>mx_sum){
            return 0;
        }
        if ( -1 == pos ){
          if(sum<mn_sum){
              return 0;
          }  
        return 1;//能够搜索到这里，说明前面的每一个条件都满足，返回1个
        } 

        //如果没有限制，而且前面已经求出D，则直接返回
        if ( !limit && -1 != D[pos][sum] ) return D[pos][sum];

        int last = limit ? Dig[pos] : 9;
        llt ans = 0;

        //递归搜索
        for(int i=0;i<=last;++i){
            if ( sum+i>mx_sum ) continue;

            ans += dfs(pos-1,sum+i,limit&&(i==Dig[pos]));
            ans%=mod;
        }

        return limit ? ans : D[pos][sum] = ans;
    }

    //求[0,n]满足条件的数有多少个
    llt ddp(string s){
        int n = s.size();
        for(int i = 0;i < n;i++){
            Dig[n-1-i] = s[i]-'0'; 
        }
        return dfs(n-1,0,true);
    }

    
    
    int count(string num1, string num2, int min_sum, int max_sum) {
        memset(D,-1,sizeof(D));
        mn_sum = min_sum;
        mx_sum = max_sum;
        long long ans = ddp(num2)-ddp(num1);
        
        int sum = 0;
        for(auto i:num1){
            sum+=i-'0';
        }
        if(sum>=min_sum&&sum<=max_sum){
            ans++;
        }
        ans = (ans+mod)%mod;
        return ans;
    }
};


int main(){
    string s,t;
    int s1,s2;
    cin>>s>>t>>s1>>s2;
    Solution so;
    int ans=so.count(s,t,s1,s2);
    cout<<ans<<'\n';
    return 0;
}
