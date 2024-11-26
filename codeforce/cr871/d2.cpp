#include <bits/stdc++.h>
using namespace std;

void solve(){
	int n, m;
	cin >> n >> m;

	if(n==m){cout<<"yes\n";return;}
	if (n % 3 || m > n){
		cout<<"no\n";
		return;
	}

	set<int> st;
	st.insert(n);
	while (st.size()){
		int x = *(st.begin());
		st.erase(st.begin());
		if (x == m){
			cout<<"yes\n";
			return;
		}

		if (x % 3==0){
			x /= 3;
			if (x==m ||2*x== m){
				cout<<"yes\n";
				return;
			}
			if (x % 3==0){
				st.insert(x);
				st.insert(2 * x);
			}
		}
	}
	cout<<"no\n";
}

int main()
{
int t;
cin >> t;
while(t--)
solve();
}