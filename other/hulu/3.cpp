#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
long long a[N],s[N],q[N];
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	long long n,m,k;
	cin>>n>>m>>k;
	for(int i=0;i<n;++i){
		cin>>a[i];
		s[i+1]=s[i]+a[i];
		q[i+1]=q[i]+(a[i]<0);
	}

	long long ans=0;
	deque<long long> dq;
	for(int i=1;i<=n;++i){
		while(!dq.empty()&&s[dq.back()]>s[i]){
			dq.pop_back();
		}
		dq.push_back(i);
		while(q[i]-q[dq.front()-1]>m) dq.pop_front();
		int l = 0, r = dq.size() - 1, mid;
		while(l<=r){
			mid = (l+r)/2;
			long long t=s[i]-s[dq[mid]];
			if(t<=k){
				ans=max(ans,t);
				r=mid-1;
			}else l=mid+1;
		}
		
	}
	cout<<ans<<"\n";
	return 0;
}
