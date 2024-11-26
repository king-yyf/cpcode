#include<iostream>
#include<string>
#include<vector>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
ll fac(ll a)
{
    ll ans=1;
    for(int i=a;i>=3;i--)
        ans=(ans*i)%mod;
    return ans%mod;
}
void slove()
{
   ll n;
    cin>>n;
    cout<<fac(2*n)<<endl;
}
int main()
{
    slove();
}