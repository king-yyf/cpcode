#include <bits/stdc++.h>
using namespace std;

int a[200005];
int n;
map<pair<int,int>,pair<int,int>> dp1,dp2;

pair<int,int> r(int i,int j);
pair<int,int> d(int i,int j);

pair<int,int> r(int i,int j){

    if(dp2.find({i,j})!=dp2.end()){
        //it already exists
        return dp2[{i,j}] ;
    }

    if(i==j){
        pair<int,int> d1 ;
        d1.first = 0;
        d1.second = a[i] ;
        dp2[{i,j}] = d1 ;
        return d1 ;
    }

    pair<int,int> d1,d2 ;
    d1.first =  d(i+1,j).first ;
    d1.second = d(i+1,j).second + a[i] ;
  

    d2.first = d(i,j-1).first ;
    d2.second = d(i,j-1).second + a[j] ;

    if(a[i]>a[j]){

        dp2[{i,j}] = d1 ;
        return d1 ;
    } else if(a[i]==a[j]){

         if((d1.first-d1.second)>=(d2.first-d2.second)){

            dp2[{i,j}] = d1 ;
            return d1 ;
        }
  
        dp2[{i,j}] = d2 ;
        return d2 ;
      

    }
  

    dp2[{i,j}] = d2 ;
    return d2 ;

}

pair<int,int> d(int i,int j){

    if(dp1.find({i,j})!=dp1.end()){
        //it already exists
        return dp1[{i,j}] ;
    }

    if(i==j){
        pair<int,int> d1 ;
        d1.first = a[i];
        d1.second = 0 ;
        dp1[{i,j}] = d1 ;
        return d1 ;
    }

    pair<int,int> d1,d2 ;
    d1.first = a[i] + r(i+1,j).first ;
    d1.second = r(i+1,j).second ;
  

    d2.first = a[j] + r(i,j-1).first ;
    d2.second = r(i,j-1).second ;

    if((d1.first-d1.second)>=(d2.first-d2.second)){

        dp1[{i,j}] = d1 ;
        return d1 ;
    }
  

    dp1[{i,j}] = d2 ;
    return d2 ;

}






int main() {
  
    int n;
    cin>>n;
    int i = 1 ;
    while(i<=n){
        cin>>a[i];
        i++;
    }
    pair<int,int> kk = d(1,n);

    cout<<kk.first<<" "<<kk.second ;
  
    return 0 ;
}