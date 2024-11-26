#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.eolymp.com/en/problems/319

#define MAX 100010
int primes[MAX], deg[MAX], pr[100];

void factor(int n, int flag)
{
 int i;
 for(i = 0; pr[i] <= (int)sqrt(1.0*n); i++)
 while (n % pr[i] == 0) n /= pr[i], deg[pr[i]] += flag;
 if (n > 1) deg[n] += flag;
}

void gen_primes(void)
{
 int i, j;
 for(i = 0; i < MAX; i++) primes[i] = 1;
 primes[0] = primes[1] = 0;
 for(i = 2; i <= sqrt(1.0*MAX); i++)
 if (primes[i])
 for(j = i * i; j < MAX; j += i) primes[j] = 0;
 for(j = i = 0; i <= sqrt(1.0*MAX); i++)
 if (primes[i]) pr[j++] = i;
pr[j] = MAX;
}

void Cnk(int n, int k)
{
 int i, res = 1;
 memset(deg,0,sizeof(deg));
 for(i = 1; i <= k; i++)
 factor(n-i+1,1), factor(i,-1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    gen_primes();

    int t; 
    cin >> t;
    while(t--) {
    	int n,k;
    	cin>>n>>k;
    	if(k>n-k)k=n-k;
    	if(n==1||!k){
    		cout<<"1\n";
    		continue;
    	}
    	Cnk(n,k);

    	for(int flag = 0,i = 0; i < MAX; i++)
		 if (deg[i])
		 {
		 if(flag)cout<<" * ";
		 cout<<i; flag = 1;
		 if(deg[i] > 1) cout<<"^"<< deg[i];
		 }
		 cout<<'\n';
		}

    return 0;
}
