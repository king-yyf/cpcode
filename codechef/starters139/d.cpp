#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

int main() {
  // your code goes here
  
int t;
cin>>t;
while(t--)
{
    int n;
    cin>>n;
    long long c;
    cin>>c;
    int a[n];
    long long b[n]={0};
    long long sum=0;
    for(int i=0;i<n;i++)
    {cin>>a[i];
    
        sum+=a[i];
    }
    
    for(int i=1;i<n;i++)
    {
        b[i]=a[i]*(sum-a[i]);
    }
    vector<pair<int,int>>v1;
    for(int i=1;i<n;i++)
    {
        v1.push_back({b[i],i});
    }
    sort(v1.begin(),v1.end());
    int p=0;
    long long sum1=sum;
    for(int i=1;i<n;i++)
    {
        if((a[v1[i].second])*sum1<=c)
        {c-=(v1[i].second)*sum1;
            p++;
            sum1-=a[v1[i].second];
        }
    }
    cout<<n-p<<endl;
    
}
  
  
  return 0;
}