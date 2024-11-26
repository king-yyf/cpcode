#include <bits/stdc++.h>
using namespace std;

using ll = long long;


// #pragma GCC target("avx2")

const int B = 160;

vector<vector<ll>> S[B];
vector<vector<ll>> S1[B];

void solve(){
	int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) {
    	cin >> x;
    }

    for(int i=1,t=min(B,n);i<=t;++i){
    	S[i-1].resize(i);
        S1[i-1].resize(i);

    	for(int j=0;j<i;++j){
    		S[i-1][j] = {0};
            S1[i-1][j] = {0};
            int t=1;
    		for(int k=j;k<n;k+=i){
    			S[i-1][j].push_back(S[i-1][j].back()+a[k]*1ll*t);
                S1[i-1][j].push_back(S1[i-1][j].back()+a[k]);
                t++;
    		}
    	}
    }

    for(int _=0;_<q;++_){
    	int s,d,k;
        cin >> s >> d >> k;
        s--;
        if(d>B){
            ll c=0;
            for(int i=s,p=1;p<=k;i+=d,p++){
                c+=a[i]*1ll*p;
            }
            cout<<c<<' ';
        }else{
            auto &s1=S[d-1];
            auto &s2=S1[d-1];
            int l=s/d,r=(s+(k-1)*d)/d,idx=s%d;

            ll c1=s1[idx][r+1]-s1[idx][l],c2=s2[idx][r+1]-s2[idx][l];
            ll c=c1-l*c2;
            cout<<c<<' ';
        }
    }
    cout<<"\n";
    for(int i=0;i<min(n,B);++i){
    	S[i].clear();
    	S1[i].clear();
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
    	solve();
    }
    return 0;
}
