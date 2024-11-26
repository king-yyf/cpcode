#include <bits/stdc++.h>
  using namespace std;
  #define  ll long long
  int main() {

      ll n,x;
      cin>>n>>x;
      int res=1e8;
      int mini=1e8;
      for(int i=0;i<n;i++)
      {
          int ele;
          cin>>ele;
          if(abs(ele-x)<mini){
              mini=abs(ele-x);
              res=ele;
          }
      }
    cout<<mini<<endl;
    return 0;

  }