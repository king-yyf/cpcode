/***
 created: 2022-12-09-21.58.50
***/

#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define all(we) we.begin(),we.end()
#define test int tt; cin>>tt; for(int cs=1;cs<=tt;cs++)
#define nl '\n'

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    ll n,m,i,j,k,l=0;

    cin>>n>>m;

    ll a[n+4],b[m+4];

    for(i=0;i<n;i++) cin>>a[i];

    for(i=0;i<m;i++) cin>>b[i];


     for(i=1;i<m;i++)
     {
         map<ll,ll>x;

         for(j=i-1;j>=0;j--)
         {
             if(b[i]==b[j]) break;

             if(x[b[j]]==0)
             {
                 l+=a[b[j]-1];
                 x[b[j]]=1;
             }
         }
     }


   cout<<l<<nl;


    return 0;
}




		    			  	 	 				      						