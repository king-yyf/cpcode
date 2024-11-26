#include <bits/stdc++.h>
using namespace std;

void solve(int tt) {
    rd(n,k);
    rd(s,t);


    vector<long long> s1(n);
    vector<long long> s2(n);

    int cnt=0;

    f0(n){
    	if(s[i]==t[i]) {
    		cnt++;
    	}else{
    		s1[i]=cnt*(cnt+1ll)/2;
    	}
    }

    f0(n+1)s1[i+1]+=s1[i];

    cnt=0;

    for(int i=n-1;i>=0;--i){
    	if(s[i]==t[i]) {
    		cnt++;
    	}else{
    		s2[i]=cnt*(cnt+1ll)/2;
    	}
    }
    for(int i=n-1;i>0;--i) s2[i-1]+=s2[i];
  
    vector g(n,vector<int>(26));

    f0(n){
    	if(s[i]!=t[i]){
    		int x=s[i]-'a';
    		g[i][x]=1;
    	}
    }

    // for(int i=0;i<n;++i){
    // 	for(int j=0;j<26;++j){
    // 		cout<<g[i][j]<<" \n"[j==25];
    // 	}
    // }

    // if(tt==2){
    // 	wt(s1);
    // 	wt(s2);
    // }

     PrefixSum2D<int> f(g);

     int l=0;
     auto chk=[&](int x, int y){
     	int c=0;
     	f0(26){
     		if(f.sum(x,i,y,i)>0){
     			c++;
     			if(c>k)return 0;
     		}
     	}
     	return 1;
     };
     long long ans=0;
     for(int r=0;r<n;++r){
     	while(l<=r&& !chk(l,r)){
     		l++;
     	}
     	long long x1=0,x2=0;
     	if(l-1>=0)x1=s1[l-1];
     	if(r+1<n) x2=s2[r+1];
     	int cnt=r-l+1;

     	// dbg("cnt=",cnt,'\n');
     	long long c=x1+x2+cnt*(cnt+1ll)/2;
     	ans=max(ans,c);
     }
     cout<<ans<<"\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
