#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define MOD 1000000007
ll n,q,a[100005],seg[400005][45],l,r,po[100005];
/*void build(ll node,ll st,ll en)
{
    if(st==en)
    {
        for(ll i=0;i<=42;i++)
        {
            if(a[st]&(1<<i))
            seg[node][i]=1;
        }
    }
    else
    {
        ll mid=(st+en)/2;
        build(2*node,st,mid);
        build(2*node+1,mid+1,en);
        for(ll i=0;i<=42;i++)
        {
            seg[node][i]=seg[2*node]+seg[2*node+1];
        }
    }
}
ll qry(ll node,ll st,ll en,ll l,ll r,ll idx)
{
    if(st>en||st>r||en<l||l>r)
    return 0;
    else if(st>=l&&en<=r)
    return seg[node][idx];
    else
    {
        ll mid=(st+en)/2;
        return qry(2*node,st,mid,l,r,idx)+qry(2*node+1,mid+1,en,l,r,idx);
    }
}*/
void create()
{
    ll i,j;
    for(i=0;i<=42;i++)
    {
        for(j=1;j<=n;j++)
        {
            seg[j][i]=seg[j-1][i];
            if(a[j]&(1LL<<i))
            seg[j][i]++;
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    ll i,j,k;
    cin>>n;
    po[0]=1;
    for(i=1;i<=100002;i++)
    {
        po[i]=2*po[i-1];
        po[i]%=MOD;
    }
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    //build(1,1,n);
    create();
    cin>>q>>j;
    while(q--)
    {
        cin>>l>>r;
        ll cnt1,cnt0,ans=0,ans1=0;
        for(i=0;i<=42;i++)
        {
            cnt1=seg[r][i]-seg[l-1][i];
            cnt0=r-l+1-cnt1;
            ans=cnt1*(cnt0*(cnt0-1))/2;
            ans+=(cnt1*(cnt1-1)*(cnt1-2))/6;
            ans%=MOD;
            ans=ans*po[i];
            ans%=MOD;
            ans1+=ans;
            ans1%=MOD;
        }
        cout<<ans1<<"\n";
    }
    return 0;
}